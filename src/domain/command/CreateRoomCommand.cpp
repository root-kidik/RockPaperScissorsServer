#include <sstream>

#include <domain/command/CreateRoomCommand.hpp>
#include <domain/interface/RoomStorage.hpp>
#include <domain/interface/UserClient.hpp>

namespace rps::domain::command
{

CreateRoomCommand::CreateRoomCommand(interface::RoomStorage& room_storage) : m_room_storage{room_storage}
{
}

void CreateRoomCommand::execute(const std::string& data, interface::UserClient& user_client)
{
    std::istringstream iss{data};

    std::string name;
    entity::Uuid owner_uuid;

    iss >> name >> owner_uuid;

    if (auto uuid = m_room_storage.try_add_room(name, owner_uuid))
        user_client.send(uuid.value());
    else
        user_client.send("Error");
}

} // namespace rps::domain::command
