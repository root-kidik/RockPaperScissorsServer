#pragma once

#include <chrono>
#include <cstdint>
#include <memory>
#include <unordered_set>
#include <vector>

#include <domain/entity/Uuid.hpp>

#include <RockPaperScissorsProtocol/interface/Connection.hpp>

namespace rps::domain::entity
{

struct Room
{
    static constexpr std::uint8_t         kMaxPlayers{6};
    static constexpr std::chrono::seconds kTurnTime{10};

    std::string  name;
    entity::Uuid owner_uuid;

    bool is_game_started{};

    std::unordered_set<entity::Uuid> players;
};

} // namespace rps::domain::entity
