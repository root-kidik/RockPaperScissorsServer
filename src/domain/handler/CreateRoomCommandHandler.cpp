#include <sstream>

#include <domain/handler/CreateRoomCommandHandler.hpp>
#include <domain/interface/RoomStorage.hpp>

#include <RockPaperScissorsProtocol/interface/Connection.hpp>
#include <RockPaperScissorsProtocol/utils/Utils.hpp>

namespace rps::domain::handler
{

CreateRoomCommandHandler::CreateRoomCommandHandler(interface::RoomStorage& room_storage) : m_room_storage{room_storage}
{
}

protocol::entity::server::StatusResponse CreateRoomCommandHandler::handle(
    protocol::entity::server::CreateRoomRequest&&           request,
    const std::shared_ptr<protocol::interface::Connection>& connection)
{
    protocol::entity::server::StatusResponse response;

    if (request.room_name.empty() || request.user_uuid.empty())
    {
        response.is_ok = false;
        return response;
    }

    if (!m_room_storage.try_add_room(request.room_name, request.user_uuid))
    {
        response.is_ok = false;
        return response;
    }

    response.is_ok = true;
    return response;
}

} // namespace rps::domain::handler
