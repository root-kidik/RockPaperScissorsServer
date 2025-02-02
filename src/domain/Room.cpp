#include <domain/Room.hpp>

namespace rps::domain
{

Room::Room(const entity::Uuid& uuid, const entity::Uuid& owner_uuid) : m_uuid{uuid}, m_owner_uuid{owner_uuid}
{
}

bool Room::try_add_player(const entity::Uuid& player_uuid)
{
    if (m_players.size() == 6)
        return false;

    m_players.push_back(player_uuid);

    return true;
}

} // namespace rps::domain
