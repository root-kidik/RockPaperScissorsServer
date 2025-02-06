#include <cassert>

#include <domain/model/Room.hpp>
#include <domain/util/Util.hpp>

#include <RockPaperScissorsProtocol/entity/CommandSender.hpp>
#include <RockPaperScissorsProtocol/entity/client/request/CardForcedNominatedRequest.hpp>
#include <RockPaperScissorsProtocol/entity/client/request/CardRaisedRequest.hpp>
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

    m_timer->start(interface::Room::kTurnTime, [this]() { compute_and_notify_winner(); }, false);

    return true;
}

const std::unordered_map<entity::Uuid, Room::Player>& Room::get_players()
{
    return m_players;
}

void Room::compute_and_notify_winner()
{
    std::unordered_map<entity::Uuid, protocol::entity::Card> play_table;

    for (auto& [uuid, player] : m_players)
    {
        if (player.cards.empty())
            continue;

        if (!player.nominated_card)
            force_nominate_card(player);

        raise_player_card(uuid, player, play_table);
    }

    compute_winner(play_table);
}

void Room::force_nominate_card(Player& player)
{
    player.nominated_card = player.cards.back();

    protocol::entity::client::CardForcedNominatedRequest request;
    request.card = player.cards.back();

    m_command_sender.send(std::move(request), player.connection);
}

void Room::raise_player_card(const entity::Uuid&                                       uuid,
                             Player&                                                   player,
                             std::unordered_map<entity::Uuid, protocol::entity::Card>& play_table)
{
    assert(player.nominated_card && "Card must be nominated, something went wrong");

    auto card        = player.nominated_card.value();
    play_table[uuid] = card;

    auto it = std::find(player.cards.begin(), player.cards.end(), card);

    assert(it != player.cards.end() && "Nominated card must be exists");

    player.cards.erase(it);

    protocol::entity::client::CardRaisedRequest request;
    request.card = player.nominated_card.value();

    m_command_sender.send(std::move(request), player.connection);
}

void Room::compute_winner(std::unordered_map<entity::Uuid, protocol::entity::Card>& play_table)
{
    bool has_rock{}, has_paper{}, has_scissors{};

    for (const auto& [uuid, card] : play_table)
        if (card == protocol::entity::Card::Rock)
            has_rock = true;
        else if (card == protocol::entity::Card::Paper)
            has_paper = true;
        else if (card == protocol::entity::Card::Scissors)
            has_scissors = true;

    if (has_rock && has_paper && has_scissors)
    {
        // No Winner

        return;
    }

    if (has_rock && has_paper)
    {
        // Paper winners

        return;
    }

    if (has_rock && has_scissors)
    {
        // Rock winners

        return;
    }

    if (has_scissors && has_paper)
    {
        // Scissors winners

        return;
    }
}

} // namespace rps::domain::model
