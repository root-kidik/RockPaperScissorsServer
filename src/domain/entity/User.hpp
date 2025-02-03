#pragma once

#include <memory>

#include <domain/entity/Uuid.hpp>

#include <RockPaperScissorsProtocol/interface/Connection.hpp>

namespace rps::domain::entity
{

struct User
{
    Uuid        uuid;
    std::string nickname;

    std::shared_ptr<protocol::interface::Connection> connection;
};

} // namespace rps::domain::entity
