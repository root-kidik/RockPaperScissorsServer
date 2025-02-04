#pragma once

#include <memory>
#include <optional>

#include <domain/entity/User.hpp>

#include <RockPaperScissorsProtocol/interface/Connection.hpp>

namespace rps::domain::interface
{

class UserStorage
{
public:
    virtual ~UserStorage() = default;

    virtual std::optional<std::string> try_add_user(const std::string& nickname,
                                                    const std::shared_ptr<protocol::interface::Connection>& connection) = 0;

    virtual std::optional<std::string> try_find_user_uuid(const std::string& nickname) const = 0;
    virtual std::optional<std::string> try_find_user_nickname(const std::string& uuid) const = 0;

    virtual std::optional<std::reference_wrapper<const entity::User>> try_find_user(const std::string& uuid) const = 0;
};

} // namespace rps::domain::interface
