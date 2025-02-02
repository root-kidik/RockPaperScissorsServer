#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include <domain/entity/Uuid.hpp>
#include <domain/interface/UserClient.hpp>

namespace rps::domain
{

class Room
{
public:
    Room(const entity::Uuid& uuid, const entity::Uuid& owner_uuid);

    bool try_add_player(const entity::Uuid&                           player_uuid,
                        const std::string&                            nickname,
                        const std::shared_ptr<interface::UserClient>& client);

private:
    struct Player
    {
        std::string                            nickname;
        std::shared_ptr<interface::UserClient> client;
    };

    entity::Uuid m_uuid;
    entity::Uuid m_owner_uuid;

    std::unordered_map<entity::Uuid, Player> m_players;
};

} // namespace rps::domain
