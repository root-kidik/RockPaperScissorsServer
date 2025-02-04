#pragma once

#include <memory>

#include <domain/handler/ConnectToRoomCommandHandler.hpp>
#include <domain/handler/CreateRoomCommandHandler.hpp>
#include <domain/handler/RegisterCommandHandler.hpp>

#include <RockPaperScissorsProtocol/entity/server/ServerCommandExecutor.hpp>

namespace rps::domain::interface
{
class UserStorage;
class RoomStorage;
} // namespace rps::domain::interface

namespace rps::domain
{

class Server
{
public:
    Server(interface::UserStorage& user_storage, interface::RoomStorage& room_storage);

    void on_command(protocol::entity::server::ServerCommandType             command_type,
                    std::string&&                                           data,
                    const std::shared_ptr<protocol::interface::Connection>& client);

private:
    interface::UserStorage& m_user_storage;
    interface::RoomStorage& m_room_storage;

    handler::RegisterCommandHandler      m_register_command_handler;
    handler::CreateRoomCommandHandler    m_create_room_command_handler;
    handler::ConnectToRoomCommandHandler m_connect_to_room_command_handler;

    protocol::entity::server::ServerCommandExecutor m_command_executor;
};

} // namespace rps::domain
