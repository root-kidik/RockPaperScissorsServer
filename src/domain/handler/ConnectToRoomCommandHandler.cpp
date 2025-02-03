#include <sstream>

#include <domain/handler/ConnectToRoomCommandHandler.hpp>
#include <domain/interface/RoomStorage.hpp>
#include <domain/interface/UserStorage.hpp>

#include <RockPaperScissorsProtocol/entity/client/ClientCommandType.hpp>
#include <RockPaperScissorsProtocol/entity/server/ConnectToRoomCommand.hpp>
#include <RockPaperScissorsProtocol/utils/Utils.hpp>

namespace rps::domain::handler
{

ConnectToRoomCommandHandler::ConnectToRoomCommandHandler(interface::RoomStorage& room_storage,
                                                         interface::UserStorage& user_storage) :
m_room_storage{room_storage},
m_user_storage{user_storage}
{
}

void ConnectToRoomCommandHandler::execute(const std::string&                                      data,
                                          const std::shared_ptr<protocol::interface::Connection>& connection)
{
    auto command = protocol::utils::deserialize<protocol::entity::ConnectToRoomCommand>(data);

    if (command.user_uuid.empty() || command.room_name.empty())
    {
        connection->send("Error");
        return;
    }

    auto room = m_room_storage.try_find_room(command.room_name);
    if (!room)
    {
        connection->send("Error");
        return;
    }

    auto& room_ref = room.value().get();

    if (room_ref.players.size() == 6 || (room_ref.players.size() == 5 && command.user_uuid != room_ref.owner_uuid &&
                                         room_ref.players.find(room_ref.owner_uuid) == room_ref.players.end()))
    {
        connection->send("Error");
        return;
    }

    auto user_nickname = m_user_storage.try_find_user_nickname(command.user_uuid);
    if (!user_nickname)
    {
        connection->send("Error");
        return;
    }

    std::string message = std::to_string(static_cast<std::uint32_t>(protocol::entity::ClientCommandType::NewPlayerAdded)) +
                          ' ' + user_nickname.value();

    for (auto& player_uuid : room_ref.players)
        if (auto player = m_user_storage.try_find_user(player_uuid))
            player.value().get().connection->send(message);

    room_ref.players.emplace(command.user_uuid);

    connection->send("Ok");
}

} // namespace rps::domain::handler
