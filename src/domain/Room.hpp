#pragma once

#include <vector>

#include <domain/entity/Uuid.hpp>

namespace rps::domain
{

class Room
{
public:
    Room(const entity::Uuid& uuid, const entity::Uuid& owner_uuid);

    bool try_add_player(const entity::Uuid& player_uuid);

private:
    entity::Uuid m_uuid;
    entity::Uuid m_owner_uuid;

    std::vector<entity::Uuid> m_players;
};

} // namespace rps::domain
