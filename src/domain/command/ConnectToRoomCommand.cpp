#include <sstream>

#include <domain/command/ConnectToRoomCommand.hpp>
#include <domain/interface/RoomStorage.hpp>
#include <domain/interface/UserClient.hpp>
#include <domain/interface/UserStorage.hpp>

namespace rps::domain::command
{

ConnectToRoomCommand::ConnectToRoomCommand(interface::RoomStorage& room_storage, interface::UserStorage& user_storage) :
m_room_storage{room_storage},
m_user_storage{user_storage}
{
}

void ConnectToRoomCommand::execute(const std::string& data, const std::shared_ptr<interface::UserClient>& user_client)
{
    std::istringstream iss{data};

    entity::Uuid user_uuid;
    std::string  room_name;

    iss >> user_uuid >> room_name;

    auto room = m_room_storage.try_find_room(room_name);
    if (!room)
    {
        user_client->send("Error");
        return;
    }

    auto user_nickname = m_user_storage.try_find_user_nickname(user_uuid);
    if (!user_nickname)
    {
        user_client->send("Error");
        return;
    }

    if (!room.value().get().try_add_player(user_uuid, user_nickname.value(), user_client))
    {
        user_client->send("Error");
        return;
    }

    user_client->send("Ok");
}

} // namespace rps::domain::command
