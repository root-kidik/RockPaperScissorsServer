#include <sstream>

#include <domain/command/ConnectToRoomCommand.hpp>
#include <domain/interface/RoomStorage.hpp>
#include <domain/interface/UserClient.hpp>

namespace rps::domain::command
{

ConnectToRoomCommand::ConnectToRoomCommand(interface::RoomStorage& room_storage) : m_room_storage{room_storage}
{
}

void ConnectToRoomCommand::execute(const std::string& data, interface::UserClient& user_client)
{
    std::istringstream iss{data};

    entity::Uuid user_uuid;
    std::string  room_name;

    iss >> user_uuid >> room_name;

    auto room = m_room_storage.try_find_room(room_name);
    if (!room)
    {
        user_client.send("Error");
        return;
    }

    if (!room.value().try_add_player(user_uuid))
    {
        user_client.send("Error");
        return;
    }

    user_client.send("Ok");
}

} // namespace rps::domain::command
