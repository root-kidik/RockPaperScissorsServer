#include <domain/Room.hpp>
#include <domain/entity/ClientCommandType.hpp>
#include <domain/interface/UserClient.hpp>

namespace rps::domain
{

Room::Room(const entity::Uuid& uuid, const entity::Uuid& owner_uuid) : m_uuid{uuid}, m_owner_uuid{owner_uuid}
{
}

bool Room::try_add_player(const entity::Uuid&                           player_uuid,
                          const std::string&                            nickname,
                          const std::shared_ptr<interface::UserClient>& client)
{
    if (m_players.size() == 6)
        return false;

    m_players.emplace(player_uuid, Player{nickname, client});

    return true;
}

} // namespace rps::domain
