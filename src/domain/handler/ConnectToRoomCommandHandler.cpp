#include <sstream>

#include <domain/handler/ConnectToRoomCommandHandler.hpp>
#include <domain/interface/RoomStorage.hpp>
#include <domain/interface/UserStorage.hpp>

#include <RockPaperScissorsProtocol/entity/client/ClientCommandType.hpp>
#include <RockPaperScissorsProtocol/utils/Utils.hpp>

namespace rps::domain::handler
{

ConnectToRoomCommandHandler::ConnectToRoomCommandHandler(interface::RoomStorage& room_storage,
                                                         interface::UserStorage& user_storage,
                                                         protocol::entity::NewPlayerAddedCommandSender& command_sender) :
m_room_storage{room_storage},
m_user_storage{user_storage},
m_command_sender{command_sender}
{
}

protocol::entity::server::StatusResponse ConnectToRoomCommandHandler::handle(
    protocol::entity::server::ConnectToRoomRequest&&        request,
    const std::shared_ptr<protocol::interface::Connection>& connection)
{
    protocol::entity::server::StatusResponse response;

    if (request.user_uuid.empty() || request.room_name.empty())
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

    auto& room_ref = room.value().get();

    if (room_ref.is_game_started || room_ref.players.size() == entity::Room::kMaxPlayers ||
        (room_ref.players.size() == entity::Room::kMaxPlayers - 1 && request.user_uuid != room_ref.owner_uuid &&
         room_ref.players.find(room_ref.owner_uuid) == room_ref.players.end()))
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

    for (auto& player_uuid : room_ref.players)
        if (auto player = m_user_storage.try_find_user(player_uuid))
        {
            protocol::entity::client::NewPlayerAddedRequest new_request;
            new_request.user_nickname = user_nickname.value();

            m_command_sender.send(std::move(new_request), player.value().get().connection);
        }

    room_ref.players.emplace(request.user_uuid);

    response.is_ok = true;
    return response;
}

} // namespace rps::domain::handler
