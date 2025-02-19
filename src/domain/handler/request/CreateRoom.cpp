#include <sstream>

#include <domain/interface/RoomStorage.hpp>

#include <domain/handler/request/CreateRoom.hpp>

namespace rps::domain::handler::request
{

CreateRoom::CreateRoom(interface::RoomStorage& room_storage) : m_room_storage{room_storage}
{
}

CreateRoom::Response CreateRoom::handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection)
{
    Response response;

    if (request.room_name.empty() || request.user_uuid.empty())
    {
        response.is_ok = false;
        return response;
    }

    response.is_ok = m_room_storage.try_add_room(request.room_name, request.user_uuid);
    return response;
}

} // namespace rps::domain::handler::request
