#pragma once

#include <domain/CommandExecutor.hpp>
#include <domain/command/RegisterCommand.hpp>
#include <domain/command/CreateRoomCommand.hpp>

namespace rps::domain::interface
{
class UserClient;
class UserStorage;
class RoomStorage;
} // namespace rps::domain::interface

namespace rps::domain
{

class Server
{
public:
    Server(interface::UserStorage& user_storage, interface::RoomStorage& room_storage);

    void on_command(entity::CommandType command_type, const std::string& data, interface::UserClient& client);

private:
    interface::UserStorage& m_user_storage;
    interface::RoomStorage& m_room_storage;

    command::RegisterCommand m_register_command;
    command::CreateRoomCommand m_create_room_command;

    CommandExecutor m_command_executor;
};

} // namespace rps::domain
