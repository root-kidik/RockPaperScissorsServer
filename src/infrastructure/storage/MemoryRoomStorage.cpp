#include <domain/interface/UuidGenerator.hpp>

#include <infrastructure/storage/MemoryRoomStorage.hpp>

namespace rps::infrastructure::storage
{

MemoryRoomStorage::MemoryRoomStorage(const domain::interface::UuidGenerator& uuid_generator) :
m_uuid_generator{uuid_generator}
{
}

std::optional<domain::entity::Uuid> MemoryRoomStorage::try_add_room(const std::string& name, const domain::entity::Uuid& owner_uuid)
{
    if (m_rooms.find(name) != m_rooms.end())
        return std::nullopt;

    const auto uuid = m_uuid_generator.generate();

    m_rooms.emplace(name, domain::Room{uuid, owner_uuid});

    return uuid;
}

std::optional<std::reference_wrapper<domain::Room>> MemoryRoomStorage::try_find_room(const std::string& name)
{
    auto it = m_rooms.find(name);

    if (it == m_rooms.end())
        return std::nullopt;

    return it->second;
}

} // namespace rps::infrastructure::storage
