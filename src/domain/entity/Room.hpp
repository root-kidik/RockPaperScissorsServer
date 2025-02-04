#pragma once

#include <memory>
#include <unordered_set>
#include <vector>

#include <RockPaperScissorsProtocol/interface/Connection.hpp>

namespace rps::domain::entity
{

struct Room
{
    std::string name;
    std::string owner_uuid;

    std::unordered_set<std::string> players;
};

} // namespace rps::domain::entity
