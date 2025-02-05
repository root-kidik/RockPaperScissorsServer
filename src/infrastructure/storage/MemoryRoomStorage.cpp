#include <domain/interface/UuidGenerator.hpp>

#include <infrastructure/storage/MemoryRoomStorage.hpp>
#include <infrastructure/util/QtTimer.hpp>
#include <infrastructure/util/Util.hpp>

#include <RockPaperScissorsProtocol/entity/Card.hpp>

namespace rps::infrastructure::storage
{

MemoryRoomStorage::MemoryRoomStorage(const domain::interface::UuidGenerator& uuid_generator) :
m_uuid_generator{uuid_generator}
{
}

bool MemoryRoomStorage::try_add_room(const std::string& name, const domain::entity::Uuid& owner_uuid)
{
    if (m_rooms.find(name) != m_rooms.end())
        return false;


    m_rooms.emplace(name,
                    domain::entity::Room{name, owner_uuid, false, std::make_shared<util::QtTimer>(), {}, util::gen_cards()});

    return true;
}

std::optional<std::reference_wrapper<domain::entity::Room>> MemoryRoomStorage::try_find_room(const std::string& name)
{
    auto it = m_rooms.find(name);

    if (it == m_rooms.end())
        return std::nullopt;

    return it->second;
}

} // namespace rps::infrastructure::storage
