#pragma once

#include <memory>

#include <domain/entity/Uuid.hpp>
#include <domain/interface/UserConnection.hpp>

namespace rps::domain::entity
{

struct User
{
    Uuid        uuid;
    std::string nickname;

    std::shared_ptr<interface::UserConnection> connection;
};

} // namespace rps::domain::entity
