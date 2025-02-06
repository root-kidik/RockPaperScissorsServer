#pragma once

#include <domain/entity/Uuid.hpp>

namespace rps::domain::entity
{

struct User
{
    Uuid        uuid;
    std::string nickname;
};

} // namespace rps::domain::entity
