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

    m_users[nickname] = uuid;

    return uuid;
}

std::optional<domain::entity::Uuid> MemoryUserStorage::try_find_user_uuid(const std::string& nickname) const
{
    const auto it = m_users.find(nickname);

    if (it == m_users.end())
        return std::nullopt;

    return it->second;
}

} // namespace rps::infrastructure::storage
