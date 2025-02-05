#pragma once

#include <chrono>
#include <cstdint>
#include <memory>
#include <optional>
#include <unordered_set>
#include <vector>

#include <domain/entity/Uuid.hpp>
#include <domain/interface/Timer.hpp>

#include <RockPaperScissorsProtocol/entity/Card.hpp>
#include <RockPaperScissorsProtocol/interface/Connection.hpp>

namespace rps::domain::entity
{

struct Room
{
    static constexpr std::uint8_t         kMaxPlayers{6};
    static constexpr std::chrono::seconds kTurnTime{10};

    struct Player
    {
        std::string                                      nickname;
        std::optional<protocol::entity::Card>            nominated_card;
        std::vector<protocol::entity::Card>              cards;
        std::shared_ptr<protocol::interface::Connection> connection;
        std::size_t                                      wins_count;
    };

    std::string  name;
    entity::Uuid owner_uuid;

    bool is_game_started{};

    std::shared_ptr<interface::Timer> timer;

    std::unordered_map<entity::Uuid, Player> players;
    std::vector<protocol::entity::Card>      cards;
};

} // namespace rps::domain::entity
