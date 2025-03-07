#include <RockPaperScissorsProtocol/entity/Card.hpp>

#include <infrastructure/storage/MemoryRoomStorage.hpp>

#include <infrastructure/util/QtTimer.hpp>

#include <domain/interface/UuidGenerator.hpp>

namespace rps::infrastructure::storage
{

MemoryRoomStorage::MemoryRoomStorage(const domain::interface::UuidGenerator& uuid_generator,
                                     protocol::entity::MessageSender&        command_sender) :
m_uuid_generator{uuid_generator},
m_message_sender{command_sender}
{
}

bool MemoryRoomStorage::try_add_room(const std::string& name, const domain::entity::Uuid& owner_uuid)
{
    if (m_rooms.find(name) != m_rooms.end())
        return false;

    m_rooms.emplace(name, domain::model::Room{name, owner_uuid, std::make_shared<util::QtTimer>(), m_message_sender});

    return true;
}

std::optional<std::reference_wrapper<domain::interface::Room>> MemoryRoomStorage::try_find_room(const std::string& name)
{
    auto it = m_rooms.find(name);

    if (it == m_rooms.end())
        return std::nullopt;

    return it->second;
}

} // namespace rps::infrastructure::storage
