#pragma once

#include <unordered_map>

#include <domain/entity/Room.hpp>
#include <domain/interface/RoomStorage.hpp>

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

    bool try_add_room(const std::string& name, const std::string& owner_uuid) override;
    std::optional<std::reference_wrapper<domain::entity::Room>> try_find_room(const std::string& name) override;

private:
    const domain::interface::UuidGenerator& m_uuid_generator;

    std::unordered_map<std::string, domain::entity::Room> m_rooms;
};

} // namespace rps::infrastructure::storage
