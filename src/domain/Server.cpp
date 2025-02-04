#include <domain/Server.hpp>

namespace rps::domain
{

Server::Server(interface::UserStorage& user_storage, interface::RoomStorage& room_storage) :
m_user_storage{user_storage},
m_room_storage{room_storage},
m_register_command_handler{m_user_storage},
m_create_room_command_handler{m_room_storage},
m_connect_to_room_command_handler{m_room_storage, m_user_storage, m_new_player_added_command_sender}
{
    m_command_executor.register_command(protocol::entity::server::ServerCommandType::Register, m_register_command_handler);
    m_command_executor.register_command(protocol::entity::server::ServerCommandType::CreateRoom,
                                        m_create_room_command_handler);
    m_command_executor.register_command(protocol::entity::server::ServerCommandType::ConnectToRoom,
                                        m_connect_to_room_command_handler);
}

void Server::on_command(protocol::entity::server::ServerCommandType             command_type,
                        std::string&&                                           data,
                        const std::shared_ptr<protocol::interface::Connection>& client)
{
    m_command_executor.execute_command(command_type, std::move(data), client);
}

} // namespace rps::domain
