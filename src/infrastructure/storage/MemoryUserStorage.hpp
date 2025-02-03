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

    std::optional<domain::entity::Uuid> try_add_user(
        const std::string&                                        nickname,
        const std::shared_ptr<domain::interface::UserConnection>& connection) override;

    std::optional<domain::entity::Uuid> try_find_user_uuid(const std::string& nickname) const override;

    std::optional<std::string> try_find_user_nickname(const domain::entity::Uuid& uuid) const override;

    std::optional<std::reference_wrapper<const domain::entity::User>> try_find_user(const domain::entity::Uuid& uuid) const;

private:
    const domain::interface::UuidGenerator& m_uuid_generator;

    // boost::bimap I miss you
    std::unordered_map<std::string, domain::entity::Uuid> m_nickname_to_uuid;
    std::unordered_map<domain::entity::Uuid, std::string> m_uuid_to_nickname;

    std::unordered_map<domain::entity::Uuid, domain::entity::User> m_users;
};

} // namespace rps::infrastructure::storage
