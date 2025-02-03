#pragma once

#include <memory>

#include <domain/CommandExecutor.hpp>
#include <domain/command/ConnectToRoomCommandHandler.hpp>
#include <domain/command/CreateRoomCommandHandler.hpp>
#include <domain/command/RegisterCommandHandler.hpp>

namespace rps::domain::interface
{
class UserConnection;
class UserStorage;
class RoomStorage;
} // namespace rps::domain::interface

namespace rps::domain
{

class Server
{
public:
    Server(interface::UserStorage& user_storage, interface::RoomStorage& room_storage);

    void on_command(protocol::entity::ServerCommandType               command_type,
                    const std::string&                                data,
                    const std::shared_ptr<interface::UserConnection>& client);

private:
    interface::UserStorage& m_user_storage;
    interface::RoomStorage& m_room_storage;

    command::RegisterCommandHandler      m_register_command_handler;
    command::CreateRoomCommandHandler    m_create_room_command_handler;
    command::ConnectToRoomCommandHandler m_connect_to_room_command_handler;

    CommandExecutor m_command_executor;
};

} // namespace rps::domain
