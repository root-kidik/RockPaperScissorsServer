#include "MemoryUserStorage.hpp"

#include <domain/interface/UuidGenerator.hpp>

#include <infrastructure/storage/MemoryUserStorage.hpp>

namespace rps::infrastructure::storage
{

MemoryUserStorage::MemoryUserStorage(const domain::interface::UuidGenerator& uuid_generator) :
m_uuid_generator{uuid_generator}
{
}

std::optional<std::string> MemoryUserStorage::try_add_user(const std::string& nickname,
                                                           const std::shared_ptr<protocol::interface::Connection>& connection)
{
    if (m_users.find(nickname) != m_users.end())
        return std::nullopt;

    const auto uuid = m_uuid_generator.generate();

    m_nickname_to_uuid.emplace(nickname, uuid);
    m_uuid_to_nickname.emplace(uuid, nickname);
    m_users.emplace(uuid, domain::entity::User{uuid, nickname, connection});

    return uuid;
}

std::optional<std::string> MemoryUserStorage::try_find_user_uuid(const std::string& nickname) const
{
    const auto it = m_nickname_to_uuid.find(nickname);

    if (it == m_nickname_to_uuid.end())
        return std::nullopt;

    return it->second;
}

std::optional<std::string> MemoryUserStorage::try_find_user_nickname(const std::string& uuid) const
{
    auto it = m_uuid_to_nickname.find(uuid);

    if (it == m_uuid_to_nickname.end())
        return std::nullopt;

    return it->second;
}

std::optional<std::reference_wrapper<const domain::entity::User>> MemoryUserStorage::try_find_user(const std::string& uuid) const
{
    auto it = m_users.find(uuid);

    if (it == m_users.end())
        return std::nullopt;

    return it->second;
}

} // namespace rps::infrastructure::storage
