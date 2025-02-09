#include <cassert>

#include <domain/model/Room.hpp>
#include <domain/model/round_pipe/ComputePlayerWinner.hpp>
#include <domain/model/round_pipe/DealMissingCards.hpp>
#include <domain/model/round_pipe/ForceNominatePlayerCard.hpp>
#include <domain/model/round_pipe/RaisePlayerCard.hpp>
#include <domain/util/Util.hpp>

#include <RockPaperScissorsProtocol/entity/CommandSender.hpp>
#include <RockPaperScissorsProtocol/entity/client/request/GameStartedRequest.hpp>
#include <RockPaperScissorsProtocol/entity/client/request/NewPlayerAddedRequest.hpp>

namespace rps::domain::model
{

Room::Room(const std::string&                       name,
           const entity::Uuid&                      owner_uuid,
           const std::shared_ptr<interface::Timer>& timer,
           protocol::entity::CommandSender&         command_sender) :
m_name{name},
m_owner_uuid{owner_uuid},
m_timer{timer},
m_command_sender{command_sender}
{
    m_round_pipeline.add<round_pipe::ForceNominatePlayerCard>(m_command_sender);
    m_round_pipeline.add<round_pipe::RaisePlayerCard>(m_command_sender);
    m_round_pipeline.add<round_pipe::ComputePlayerWinner>(m_command_sender);
    m_round_pipeline.add<round_pipe::DealMissingCards>(m_command_sender, m_cards);
}

bool Room::try_add_user(const entity::Uuid&                                     user_uuid,
                        const std::string&                                      user_nickname,
                        const std::shared_ptr<protocol::interface::Connection>& connection)
{
    if (m_is_game_started || m_players.find(user_uuid) != m_players.end() ||
        m_players.size() == interface::Room::kMaxPlayers ||
        (m_players.size() == model::Room::kMaxPlayers - 1 && user_uuid != m_owner_uuid &&
         m_players.find(m_owner_uuid) == m_players.end()))
        return false;

    for (auto& [player_uuid, player] : m_players)
    {
        protocol::entity::client::NewPlayerAddedRequest new_request;
        new_request.user_nickname = user_nickname;

        m_command_sender.send(std::move(new_request), player.connection);
    }

    m_players.emplace(user_uuid, model::Room::Player{user_nickname, std::nullopt, {}, connection, 0});

    return true;
}

bool Room::try_start_game(const entity::Uuid& user_uuid)
{
    if (user_uuid != m_owner_uuid || m_is_game_started)
        return false;

    m_cards = util::gen_cards();

    for (auto& [player_uuid, player] : m_players)
    {
        protocol::entity::client::GameStartedRequest new_request;

        for (std::size_t i = 0; i < protocol::entity::kMaxCardsPerPlayer; i++)
        {
            assert(!m_cards.empty() && "Deck empty, something went wrong");

            auto card            = m_cards.back();
            new_request.cards[i] = card;
            player.cards.push_back(card);
            m_cards.pop_back();
        }

        m_command_sender.send(std::move(new_request), player.connection);
    }

    m_is_game_started = true;

    m_timer->start(
        interface::Room::kTurnTime,
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

const std::unordered_map<entity::Uuid, Room::Player>& Room::get_players()
{
    return m_players;
}

} // namespace rps::domain::model
