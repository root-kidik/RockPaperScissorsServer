#include <sstream>

#include <domain/handler/CreateRoom.hpp>
#include <domain/interface/RoomStorage.hpp>

namespace rps::domain::handler
{

CreateRoom::CreateRoom(interface::RoomStorage& room_storage) : m_room_storage{room_storage}
{
}

protocol::entity::server::response::Status CreateRoom::handle(protocol::entity::server::request::CreateRoom&& request,
                                                              const std::shared_ptr<protocol::interface::Connection>& connection)
{
    protocol::entity::server::response::Status response;

    if (request.room_name.empty() || request.user_uuid.empty())
    {
        response.is_ok = false;
        return response;
    }

    response.is_ok = m_room_storage.try_add_room(request.room_name, request.user_uuid);
    return response;
}

} // namespace rps::domain::handler
