#pragma once

#include <memory>
#include <vector>

#include <domain/entity/Uuid.hpp>

#include <RockPaperScissorsProtocol/entity/Card.hpp>
#include <RockPaperScissorsProtocol/interface/Connection.hpp>

namespace rps::domain::entity
{

struct User
{
    Uuid        uuid;
    std::string nickname;

    std::shared_ptr<protocol::interface::Connection> connection;
    std::vector<protocol::entity::Card>              cards;
};

} // namespace rps::domain::entity
