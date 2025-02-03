#pragma once

#include <memory>
#include <optional>

#include <domain/entity/User.hpp>
#include <domain/entity/Uuid.hpp>
#include <domain/interface/UserConnection.hpp>

namespace rps::domain::interface
{

class UserStorage
{
public:
    virtual ~UserStorage() = default;

    virtual std::optional<entity::Uuid> try_add_user(const std::string&                                nickname,
                                                     const std::shared_ptr<interface::UserConnection>& connection) = 0;

    virtual std::optional<entity::Uuid> try_find_user_uuid(const std::string& nickname) const  = 0;
    virtual std::optional<std::string>  try_find_user_nickname(const entity::Uuid& uuid) const = 0;

    virtual std::optional<std::reference_wrapper<const entity::User>> try_find_user(const entity::Uuid& uuid) const = 0;
};

} // namespace rps::domain::interface
