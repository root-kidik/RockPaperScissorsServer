#include <domain/Server.hpp>

namespace rps::domain
{

Server::Server(interface::UserStorage& user_storage, interface::RoomStorage& room_storage) :
m_user_storage{user_storage},
m_room_storage{room_storage},
m_register_command_handler{m_user_storage},
m_create_room_command_handler{m_room_storage},
m_connect_to_room_command_handler{m_room_storage, m_user_storage}
{
    m_command_executor.register_command(protocol::entity::ServerCommandType::Register, m_register_command_handler);
    m_command_executor.register_command(protocol::entity::ServerCommandType::CreateRoom, m_create_room_command_handler);
    m_command_executor.register_command(protocol::entity::ServerCommandType::ConnectToRoom, m_connect_to_room_command_handler);
}

void Server::on_command(protocol::entity::ServerCommandType                     command_type,
                        const std::string&                                      data,
                        const std::shared_ptr<protocol::interface::Connection>& client)
{
    m_command_executor.execute_command(command_type, data, client);
}

} // namespace rps::domain
