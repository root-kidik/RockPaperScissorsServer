#pragma once

#include <unordered_map>

#include <domain/interface/RoomStorage.hpp>
#include <domain/model/Room.hpp>

#include <RockPaperScissorsProtocol/entity/CommandSender.hpp>

namespace rps::domain::interface
{
class UuidGenerator;
}

namespace rps::infrastructure::storage
{

class MemoryRoomStorage final : public domain::interface::RoomStorage
{
public:
    MemoryRoomStorage(const domain::interface::UuidGenerator& uuid_generator,
                      protocol::entity::CommandSender&        command_sender);

    bool try_add_room(const std::string& name, const domain::entity::Uuid& owner_uuid) override;
    std::optional<std::reference_wrapper<domain::interface::Room>> try_find_room(const std::string& name) override;

private:
    const domain::interface::UuidGenerator& m_uuid_generator;
    protocol::entity::CommandSender&        m_command_sender;

    std::unordered_map<std::string, domain::model::Room> m_rooms;
};

} // namespace rps::infrastructure::storage
