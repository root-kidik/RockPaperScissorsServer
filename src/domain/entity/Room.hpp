#pragma once

#include <memory>
#include <unordered_set>
#include <vector>

#include <domain/entity/Uuid.hpp>

#include <RockPaperScissorsProtocol/interface/Connection.hpp>

namespace rps::domain::entity
{

struct Room
{
    std::string  name;
    entity::Uuid owner_uuid;

    std::unordered_set<entity::Uuid> players;
};

} // namespace rps::domain::entity
