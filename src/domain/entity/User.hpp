#pragma once

#include <memory>

#include <RockPaperScissorsProtocol/interface/Connection.hpp>

namespace rps::domain::entity
{

struct User
{
    std::string uuid;
    std::string nickname;

    std::shared_ptr<protocol::interface::Connection> connection;
};

} // namespace rps::domain::entity
