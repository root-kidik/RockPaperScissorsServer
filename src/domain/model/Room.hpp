#pragma once

#include <chrono>
#include <cstdint>
#include <memory>
#include <optional>
#include <unordered_set>
#include <vector>

#include <domain/entity/Uuid.hpp>
#include <domain/interface/Room.hpp>
#include <domain/interface/Timer.hpp>

#include <RockPaperScissorsProtocol/entity/Card.hpp>
#include <RockPaperScissorsProtocol/entity/CommandSender.hpp>
#include <RockPaperScissorsProtocol/interface/Connection.hpp>

namespace rps::domain::model
{

class Room : public interface::Room
{
public:
    struct Player
    {
        std::string                                      nickname;
        std::optional<protocol::entity::Card>            nominated_card;
        std::vector<protocol::entity::Card>              cards;
        std::shared_ptr<protocol::interface::Connection> connection;
        std::size_t                                      wins_count{};
    };

    Room(const std::string&                       name,
         const entity::Uuid&                      owner_uuid,
         const std::shared_ptr<interface::Timer>& timer,
         protocol::entity::CommandSender&         command_sender);

    bool try_add_user(const entity::Uuid&                                     user_uuid,
                      const std::string&                                      user_nickname,
                      const std::shared_ptr<protocol::interface::Connection>& connection) override;

    bool try_start_game(const entity::Uuid& user_uuid) override;

    const std::unordered_map<entity::Uuid, Player>& get_players();

private:
    void compute_and_notify_winner();
    void force_nominate_card(Player& player);
    void raise_player_card(const entity::Uuid& uuid, Player& player, std::unordered_map<entity::Uuid, protocol::entity::Card>& play_table);
    void compute_winner(std::unordered_map<entity::Uuid, protocol::entity::Card>& play_table);

    std::string  m_name;
    entity::Uuid m_owner_uuid;

    bool m_is_game_started{};

    std::shared_ptr<interface::Timer> m_timer;

    std::unordered_map<entity::Uuid, Player> m_players;
    std::vector<protocol::entity::Card>      m_cards;

    protocol::entity::CommandSender& m_command_sender;
};

} // namespace rps::domain::model
