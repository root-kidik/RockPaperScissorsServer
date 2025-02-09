#include <cassert>
#include <sstream>

#include <domain/handler/StartGame.hpp>
#include <domain/interface/RoomStorage.hpp>
#include <domain/interface/UserStorage.hpp>

namespace rps::domain::handler
{

StartGame::StartGame(interface::RoomStorage& room_storage, interface::UserStorage& user_storage) :
m_room_storage{room_storage},
m_user_storage{user_storage}
{
}

protocol::entity::server::StatusResponse StartGame::handle(protocol::entity::server::StartGameRequest&& request,
                                                           const std::shared_ptr<protocol::interface::Connection>& connection)
{
    protocol::entity::server::StatusResponse response;

    if (request.room_name.empty() || request.user_uuid.empty())
    {
        response.is_ok = false;
        return response;
    }

    auto room = m_room_storage.try_find_room(request.room_name);

    if (!room)
    {
        response.is_ok = false;
        return response;
    }

    response.is_ok = room.value().get().try_start_game(request.user_uuid);
    return response;
}

} // namespace rps::domain::handler
