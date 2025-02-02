#pragma once

#include <unordered_map>

#include <domain/interface/RoomStorage.hpp>
#include <domain/Room.hpp>

namespace rps::domain::interface
{
class UuidGenerator;
}

namespace rps::infrastructure::storage
{

class MemoryRoomStorage final : public domain::interface::RoomStorage
{
public:
    MemoryRoomStorage(const domain::interface::UuidGenerator& uuid_generator);

    std::optional<domain::entity::Uuid> try_add_room(const std::string& name, const domain::entity::Uuid& owner_uuid) override;
    std::optional<domain::Room&> try_find_room(const std::string& name) override;

private:
    const domain::interface::UuidGenerator& m_uuid_generator;

    std::unordered_map<std::string, domain::Room> m_rooms;
};

} // namespace rps::infrastructure::storage
