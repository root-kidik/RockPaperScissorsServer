#include <sstream>

#include <domain/handler/ConnectToRoomCommandHandler.hpp>
#include <domain/handler/CreateRoomCommandHandler.hpp>
#include <domain/handler/RegisterCommandHandler.hpp>
#include <domain/handler/StartGameCommandHandler.hpp>

#include <infrastructure/Server.hpp>
#include <infrastructure/client/TcpSocketUserConnection.hpp>
#include <infrastructure/utils/QtTimer.hpp>

namespace rps::infrastructure
{

Server::Server() : m_memory_user_storage{m_uuid_generator}, m_memory_room_storage{m_uuid_generator}
{
    m_command_executor.register_command<domain::handler::RegisterCommandHandler>(m_memory_user_storage);
    m_command_executor.register_command<domain::handler::CreateRoomCommandHandler>(m_memory_room_storage);
    m_command_executor.register_command<domain::handler::ConnectToRoomCommandHandler>(m_memory_room_storage,
                                                                                      m_memory_user_storage,
                                                                                      m_new_player_added_command_sender);
    m_command_executor.register_command<domain::handler::StartGameCommandHandler>(m_memory_room_storage,
                                                                                  m_memory_user_storage,
                                                                                  m_game_started_command_sender,
                                                                                  std::make_shared<utils::QtTimer>());

    connect(this,
            &QTcpServer::newConnection,
            this,
            [this]()
            {
                auto* client_socket = nextPendingConnection();

                auto client_wrapper = std::make_shared<client::TcpSocketUserConnection>(client_socket);

                connect(client_socket,
                        &QTcpSocket::disconnected,
                        this,
                        [client_wrapper]() { client_wrapper->disconnect(); });

                connect(client_socket, &QTcpSocket::disconnected, client_socket, &QTcpSocket::deleteLater);

                connect(client_socket,
                        &QTcpSocket::readyRead,
                        this,
                        [client_socket, client_wrapper, this]()
                        { m_command_executor.execute_command(client_socket->readAll().toStdString(), client_wrapper); });
            });
}

} // namespace rps::infrastructure
