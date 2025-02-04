#include <sstream>

#include <domain/handler/ConnectToRoomCommandHandler.hpp>
#include <domain/handler/CreateRoomCommandHandler.hpp>
#include <domain/handler/RegisterCommandHandler.hpp>
#include <domain/handler/StartGameCommandHandler.hpp>

#include <infrastructure/Server.hpp>
#include <infrastructure/client/TcpSocketUserConnection.hpp>

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
                                                                                  m_game_started_command_sender);

    connect(this,
            &QTcpServer::newConnection,
            this,
            [this]()
            {
                auto* client_socket = nextPendingConnection();

                connect(client_socket,
                        &QTcpSocket::readyRead,
                        this,
                        [client_socket, this]()
                        {
                            std::istringstream iss{client_socket->readAll().toStdString()};

                            protocol::entity::CommandRepresentation command_type;
                            iss >> command_type;

                            if (command_type < static_cast<protocol::entity::CommandRepresentation>(
                                                   protocol::entity::server::ServerCommandType::Begin) +
                                                   1 ||
                                command_type > static_cast<protocol::entity::CommandRepresentation>(
                                                   protocol::entity::server::ServerCommandType::End) -
                                                   1)
                                return;

                            std::string data;
                            std::getline(iss, data);

                            if (!data.empty() && std::isspace(data.front()))
                                data.erase(0, 1);

                            auto client_wrapper = std::make_shared<client::TcpSocketUserConnection>(client_socket);
                            connect(client_socket,
                                    &QTcpSocket::disconnected,
                                    this,
                                    [client_wrapper]() { client_wrapper->disconnect(); });


                            m_command_executor.execute_command(static_cast<protocol::entity::server::ServerCommandType>(
                                                                   command_type),
                                                               std::move(data),
                                                               client_wrapper);
                        });

                connect(client_socket, &QTcpSocket::disconnected, client_socket, &QTcpSocket::deleteLater);
            });
}

} // namespace rps::infrastructure
