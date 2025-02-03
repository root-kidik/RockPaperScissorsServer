#include <domain/Server.hpp>
#include <domain/interface/UserConnection.hpp>

namespace rps::domain
{

Server::Server(interface::UserStorage& user_storage, interface::RoomStorage& room_storage) :
m_user_storage{user_storage},
m_room_storage{room_storage},
m_register_command{m_user_storage},
m_create_room_command{m_room_storage},
m_connect_to_room_command{m_room_storage, m_user_storage}
{
    m_command_executor.register_command(entity::ServerCommandType::Register, m_register_command);
    m_command_executor.register_command(entity::ServerCommandType::CreateRoom, m_create_room_command);
    m_command_executor.register_command(entity::ServerCommandType::ConnectToRoom, m_connect_to_room_command);
}

void Server::on_command(entity::ServerCommandType                     command_type,
                        const std::string&                            data,
                        const std::shared_ptr<interface::UserConnection>& client)
{
    m_command_executor.execute_command(command_type, data, std::move(client));
}

} // namespace rps::domain
