#include <sstream>

#include <domain/handler/ConnectToRoom.hpp>
#include <domain/interface/RoomStorage.hpp>
#include <domain/interface/UserStorage.hpp>

namespace rps::domain::handler
{

ConnectToRoom::ConnectToRoom(interface::RoomStorage& room_storage, interface::UserStorage& user_storage) :
m_room_storage{room_storage},
m_user_storage{user_storage}
{
}

ConnectToRoom::Response ConnectToRoom::handle(Request&&                                               request,
                                              const std::shared_ptr<protocol::interface::Connection>& connection)
{
    Response response;

    if (request.user_uuid.empty() || request.room_name.empty())
    {
        response.is_ok = false;
        return response;
    }

    auto user_nickname = m_user_storage.try_find_user_nickname(request.user_uuid);
    if (!user_nickname)
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

    response.is_ok = room.value().get().try_add_user(request.user_uuid, user_nickname.value(), connection);
    return response;
}

} // namespace rps::domain::handler
