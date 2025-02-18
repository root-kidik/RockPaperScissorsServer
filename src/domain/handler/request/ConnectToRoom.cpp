#include <sstream>

#include <domain/interface/RoomStorage.hpp>
#include <domain/interface/UserStorage.hpp>

#include <domain/handler/request/ConnectToRoom.hpp>

namespace rps::domain::handler::request
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

    auto& room_ref = room.value().get();

    if (!room_ref.try_add_user(request.user_uuid, user_nickname.value(), connection))
    {
        response.is_ok = false;
        return response;
    }

    std::uint8_t i = 0;
    for (const auto& nickname : room_ref.get_player_nicknames())
        if (nickname != user_nickname && !nickname.empty())
        {
            assert(i < protocol::entity::kMaxPlayersPerRoom && "Too many players inside room already existed");
            response.existed_players[i++] = nickname;
        }

    response.is_ok = true;
    return response;
}

} // namespace rps::domain::handler::request
