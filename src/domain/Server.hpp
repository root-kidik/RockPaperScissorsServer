#pragma once

#include <memory>

#include <domain/CommandExecutor.hpp>
#include <domain/handler/ConnectToRoomCommandHandler.hpp>
#include <domain/handler/CreateRoomCommandHandler.hpp>
#include <domain/handler/RegisterCommandHandler.hpp>

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

    handler::RegisterCommandHandler      m_register_command_handler;
    handler::CreateRoomCommandHandler    m_create_room_command_handler;
    handler::ConnectToRoomCommandHandler m_connect_to_room_command_handler;

    CommandExecutor m_command_executor;
};

} // namespace rps::domain
