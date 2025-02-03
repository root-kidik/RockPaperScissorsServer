#include <sstream>

#include <domain/command/CreateRoomCommand.hpp>
#include <domain/interface/RoomStorage.hpp>
#include <domain/interface/UserConnection.hpp>

namespace rps::domain::command
{

CreateRoomCommand::CreateRoomCommand(interface::RoomStorage& room_storage) : m_room_storage{room_storage}
{
}

void CreateRoomCommand::execute(const std::string& data, const std::shared_ptr<interface::UserConnection>& user_connection)
{
    std::istringstream iss{data};

    std::string  name;
    entity::Uuid owner_uuid;

    iss >> name;

    if (name.empty())
    {
        user_connection->send("Error");
        return;
    }

    iss >> owner_uuid;

    if (owner_uuid.empty())
    {
        user_connection->send("Error");
        return;
    }

    if (auto status = m_room_storage.try_add_room(name, owner_uuid))
        user_connection->send("Ok");
    else
        user_connection->send("Error");
}

} // namespace rps::domain::command
