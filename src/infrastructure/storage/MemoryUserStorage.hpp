#pragma once

#include <unordered_map>

#include <domain/interface/UserStorage.hpp>

namespace rps::domain::interface
{
class UuidGenerator;
}

namespace rps::infrastructure::storage
{

class MemoryUserStorage final : public domain::interface::UserStorage
{
public:
    MemoryUserStorage(const domain::interface::UuidGenerator& uuid_generator);

    std::optional<std::string> try_add_user(const std::string& nickname,
                                            const std::shared_ptr<protocol::interface::Connection>& connection) override;

    std::optional<std::string> try_find_user_uuid(const std::string& nickname) const override;

    std::optional<std::string> try_find_user_nickname(const std::string& uuid) const override;

    std::optional<std::reference_wrapper<const domain::entity::User>> try_find_user(const std::string& uuid) const;

private:
    const domain::interface::UuidGenerator& m_uuid_generator;

    // boost::bimap I miss you
    std::unordered_map<std::string, std::string> m_nickname_to_uuid;
    std::unordered_map<std::string, std::string> m_uuid_to_nickname;

    std::unordered_map<std::string, domain::entity::User> m_users;
};

} // namespace rps::infrastructure::storage
