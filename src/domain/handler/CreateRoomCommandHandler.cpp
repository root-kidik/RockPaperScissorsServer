#include <sstream>

#include <domain/handler/CreateRoomCommandHandler.hpp>
#include <domain/interface/RoomStorage.hpp>
#include <domain/interface/UserConnection.hpp>

#include <RockPaperScissorsProtocol/entity/server/CreateRoomCommand.hpp>
#include <RockPaperScissorsProtocol/utils/Utils.hpp>

namespace rps::domain::handler
{

CreateRoomCommandHandler::CreateRoomCommandHandler(interface::RoomStorage& room_storage) : m_room_storage{room_storage}
{
}

void CreateRoomCommandHandler::execute(const std::string& data, const std::shared_ptr<interface::UserConnection>& user_connection)
{
    auto command = protocol::utils::deserialize<protocol::entity::CreateRoomCommand>(data);

    if (command.room_name.empty() || command.user_uuid.empty())
    {
        user_connection->send("Error");
        return;
    }

    if (auto status = m_room_storage.try_add_room(command.room_name, command.user_uuid))
        user_connection->send("Ok");
    else
        user_connection->send("Error");
}

} // namespace rps::domain::handler
