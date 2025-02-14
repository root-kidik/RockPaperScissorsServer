#include <cassert>

#include <domain/model/Room.hpp>
#include <domain/model/round_pipe/ComputePlayerWinner.hpp>
#include <domain/model/round_pipe/DealMissingCards.hpp>
#include <domain/model/round_pipe/ForceNominatePlayerCard.hpp>
#include <domain/model/round_pipe/RaisePlayerCard.hpp>
#include <domain/util/Util.hpp>

#include <RockPaperScissorsProtocol/entity/MessageSender.hpp>
#include <RockPaperScissorsProtocol/entity/client/request/GameStarted.hpp>
#include <RockPaperScissorsProtocol/entity/client/request/NewPlayerAdded.hpp>

namespace rps::domain::model
{

Room::Room(const std::string&                       name,
           const entity::Uuid&                      owner_uuid,
           const std::shared_ptr<interface::Timer>& timer,
           protocol::entity::MessageSender&         command_sender) :
m_name{name},
m_owner_uuid{owner_uuid},
m_timer{timer},
m_message_sender{command_sender},
m_cards{util::gen_cards()}
{
    m_round_pipeline.add<round_pipe::ForceNominatePlayerCard>(m_message_sender);
    m_round_pipeline.add<round_pipe::RaisePlayerCard>(m_message_sender);
    m_round_pipeline.add<round_pipe::ComputePlayerWinner>(m_message_sender);
    m_round_pipeline.add<round_pipe::DealMissingCards>(m_message_sender, m_cards);
}

bool Room::try_add_user(const entity::Uuid&                                     user_uuid,
                        const std::string&                                      user_nickname,
                        const std::shared_ptr<protocol::interface::Connection>& connection)
{

    if (m_is_game_started || m_players.find(user_uuid) != m_players.end() ||
        m_players.size() == protocol::entity::kMaxPlayersPerRoom ||
        (m_players.size() == protocol::entity::kMaxPlayersPerRoom - 1 && user_uuid != m_owner_uuid &&
         m_players.find(m_owner_uuid) == m_players.end()))
        return false;

    for (auto& [player_uuid, player] : m_players)
    {
        protocol::entity::client::request::NewPlayerAdded new_request;
        new_request.user_nickname = user_nickname;

        m_message_sender.send(std::move(new_request), player.connection);
    }

    m_players.emplace(user_uuid, model::Room::Player{user_nickname, std::nullopt, {}, connection, 0});

    return true;
}

bool Room::try_start_game(const entity::Uuid& user_uuid)
{
    if (user_uuid != m_owner_uuid || m_is_game_started)
        return false;

    for (auto& [player_uuid, player] : m_players)
    {
        protocol::entity::client::request::GameStarted new_request;

        for (std::size_t i = 0; i < protocol::entity::kMaxCardsPerPlayer; i++)
        {
            assert(!m_cards.empty() && "Deck empty, something went wrong");

            auto card            = m_cards.back();
            new_request.cards[i] = card;
            player.cards.push_back(card);
            m_cards.pop_back();
        }

        m_message_sender.send(std::move(new_request), player.connection);
    }

    m_is_game_started = true;

    m_timer->start(
        protocol::entity::kTurnTime,
        [this]()
        {
            for (auto& [uuid, player] : m_players)
            {
                if (player.cards.empty())
                    continue;

                RoundContext context{player, uuid};
                m_round_pipeline.run(context);
            }
        },
        false);

    return true;
}

bool Room::try_nominate_user_card(const entity::Uuid& user_uuid, protocol::entity::Card card)
{
    auto user_it = m_players.find(user_uuid);
    if (user_it == m_players.end())
        return false;

    auto& player = user_it->second;

    auto card_it = std::find(player.cards.begin(), player.cards.end(), card);
    if (card_it == player.cards.end())
        return false;

    player.nominated_card = card;

    return true;
}

std::array<std::string, protocol::entity::kMaxPlayersPerRoom> Room::get_player_nicknames() const
{
    std::array<std::string, protocol::entity::kMaxPlayersPerRoom> nicknames;

    std::uint8_t i = 0;
    for (const auto& [uuid, player] : m_players)
    {
        assert(i < protocol::entity::kMaxPlayersPerRoom && "Too many players inside room");
        nicknames[i++] = player.nickname;
    }

    return nicknames;
}

const std::unordered_map<entity::Uuid, Room::Player>& Room::get_players()
{
    return m_players;
}

} // namespace rps::domain::model
