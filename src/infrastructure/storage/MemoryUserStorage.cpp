#include "MemoryUserStorage.hpp"

#include <domain/interface/UuidGenerator.hpp>

#include <infrastructure/storage/MemoryUserStorage.hpp>

namespace rps::infrastructure::storage
{

MemoryUserStorage::MemoryUserStorage(const domain::interface::UuidGenerator& uuid_generator) :
m_uuid_generator{uuid_generator}
{
}

std::optional<domain::entity::Uuid> MemoryUserStorage::try_add_user(const std::string& nickname)
{
    if (m_users.find(nickname) != m_users.end())
        return std::nullopt;

    const auto uuid = m_uuid_generator.generate();

    m_users[nickname]        = uuid;
    m_uuid_to_nickname[uuid] = nickname;

    return uuid;
}

std::optional<domain::entity::Uuid> MemoryUserStorage::try_find_user_uuid(const std::string& nickname) const
{
    const auto it = m_users.find(nickname);

    if (it == m_users.end())
        return std::nullopt;

    return it->second;
}

std::optional<std::string> MemoryUserStorage::try_find_user_nickname(const domain::entity::Uuid& uuid) const
{
    auto it = m_uuid_to_nickname.find(uuid);

    if (it == m_uuid_to_nickname.end())
        return std::nullopt;

    return it->second;
}

} // namespace rps::infrastructure::storage
