#pragma once

#include <chrono>
#include <cstdint>
#include <memory>
#include <optional>
#include <unordered_set>
#include <vector>

#include <domain/entity/Uuid.hpp>
#include <domain/interface/Pipeline.hpp>
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

    struct RoundContext
    {
        Player&             player;
        const entity::Uuid& player_uuid;

        bool is_rock_raised{};
        bool is_paper_raised{};
        bool is_scissors_raised{};
    };

    using RoundPipeline = interface::Pipeline<RoundContext>;

    Room(const std::string&                       name,
         const entity::Uuid&                      owner_uuid,
         const std::shared_ptr<interface::Timer>& timer,
         protocol::entity::CommandSender&         command_sender,
         const std::shared_ptr<RoundPipeline>&    round_pipeline);

    bool try_add_user(const entity::Uuid&                                     user_uuid,
                      const std::string&                                      user_nickname,
                      const std::shared_ptr<protocol::interface::Connection>& connection) override;

    bool try_start_game(const entity::Uuid& user_uuid) override;

    const std::unordered_map<entity::Uuid, Player>& get_players();

private:
    std::string  m_name;
    entity::Uuid m_owner_uuid;

    bool m_is_game_started{};

    std::shared_ptr<interface::Timer> m_timer;

    std::unordered_map<entity::Uuid, Player> m_players;
    std::vector<protocol::entity::Card>      m_cards;

    protocol::entity::CommandSender& m_command_sender;

    std::shared_ptr<RoundPipeline>                           m_round_pipeline;
    std::unordered_map<entity::Uuid, protocol::entity::Card> play_table;
};

} // namespace rps::domain::model
