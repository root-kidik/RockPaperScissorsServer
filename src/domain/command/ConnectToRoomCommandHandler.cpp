#include <sstream>

#include <domain/command/ConnectToRoomCommandHandler.hpp>
#include <domain/interface/RoomStorage.hpp>
#include <domain/interface/UserConnection.hpp>
#include <domain/interface/UserStorage.hpp>

#include <RockPaperScissorsProtocol/entity/client/ClientCommandType.hpp>

namespace rps::domain::command
{

ConnectToRoomCommandHandler::ConnectToRoomCommandHandler(interface::RoomStorage& room_storage,
                                                         interface::UserStorage& user_storage) :
m_room_storage{room_storage},
m_user_storage{user_storage}
{
}

void ConnectToRoomCommandHandler::execute(const std::string&                                data,
                                          const std::shared_ptr<interface::UserConnection>& user_connection)
{
    std::istringstream iss{data};

    entity::Uuid user_uuid;
    std::string  room_name;

    iss >> user_uuid;
    if (user_uuid.empty())
    {
        user_connection->send("Error");
        return;
    }

    iss >> room_name;
    if (room_name.empty())
    {
        user_connection->send("Error");
        return;
    }

    auto room = m_room_storage.try_find_room(room_name);
    if (!room)
    {
        user_connection->send("Error");
        return;
    }

    auto& room_ref = room.value().get();

    if (room_ref.players.size() == 6 || (room_ref.players.size() == 5 && user_uuid != room_ref.owner_uuid &&
                                         room_ref.players.find(room_ref.owner_uuid) == room_ref.players.end()))
    {
        user_connection->send("Error");
        return;
    }

    auto user_nickname = m_user_storage.try_find_user_nickname(user_uuid);
    if (!user_nickname)
    {
        user_connection->send("Error");
        return;
    }

    std::string message = std::to_string(static_cast<std::uint32_t>(protocol::entity::ClientCommandType::NewPlayerAdded)) +
                          ' ' + user_nickname.value();

    for (auto& player_uuid : room_ref.players)
        if (auto player = m_user_storage.try_find_user(player_uuid))
            player.value().get().connection->send(message);

    room_ref.players.emplace(user_uuid);

    user_connection->send("Ok");
}

} // namespace rps::domain::command
