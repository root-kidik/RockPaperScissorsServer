#pragma once

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
    static constexpr std::uint8_t kMaxPlayers = 6;

    std::string  name;
    entity::Uuid owner_uuid;

    std::unordered_set<entity::Uuid> players;
};

} // namespace rps::domain::entity
