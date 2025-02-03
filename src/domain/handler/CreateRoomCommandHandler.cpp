#include <sstream>

#include <domain/handler/CreateRoomCommandHandler.hpp>
#include <domain/interface/RoomStorage.hpp>

#include <RockPaperScissorsProtocol/entity/server/CreateRoomCommand.hpp>
#include <RockPaperScissorsProtocol/interface/Connection.hpp>
#include <RockPaperScissorsProtocol/utils/Utils.hpp>

namespace rps::domain::handler
{

CreateRoomCommandHandler::CreateRoomCommandHandler(interface::RoomStorage& room_storage) : m_room_storage{room_storage}
{
}

void CreateRoomCommandHandler::execute(const std::string&                                      data,
                                       const std::shared_ptr<protocol::interface::Connection>& connection)
{
    auto command = protocol::utils::deserialize<protocol::entity::CreateRoomCommand>(data);

    if (command.room_name.empty() || command.user_uuid.empty())
    {
        connection->send("Error");
        return;
    }

    if (auto status = m_room_storage.try_add_room(command.room_name, command.user_uuid))
        connection->send("Ok");
    else
        connection->send("Error");
}

} // namespace rps::domain::handler
