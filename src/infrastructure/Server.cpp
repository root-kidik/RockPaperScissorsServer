#include <sstream>

#include <infrastructure/Server.hpp>
#include <infrastructure/client/TcpSocketUserClient.hpp>

namespace rps::infrastructure
{

Server::Server() :
m_memory_user_storage{m_uuid_generator},
m_memory_room_storage{m_uuid_generator},
m_server{m_memory_user_storage, m_memory_room_storage}
{
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

                            std::uint32_t command_type;
                            iss >> command_type;

                            if (command_type < static_cast<std::uint32_t>(domain::entity::ServerCommandType::Begin) + 1 ||
                                command_type > static_cast<std::uint32_t>(domain::entity::ServerCommandType::End) - 1)
                            {
                                client_socket->write("No such command");
                                return;
                            }

                            std::string data;
                            std::getline(iss, data);

                            if (!data.empty() && std::isspace(data.front()))
                                data.erase(0, 1);

                            auto client_wrapper = std::make_shared<client::TcpSocketUserClient>(client_socket);
                            connect(client_socket,
                                    &QTcpSocket::disconnected,
                                    this,
                                    [client_wrapper]() { client_wrapper->disconnect(); });

                            m_server.on_command(static_cast<domain::entity::ServerCommandType>(command_type),
                                                data,
                                                client_wrapper);
                        });

                connect(client_socket, &QTcpSocket::disconnected, client_socket, &QTcpSocket::deleteLater);
            });
}

} // namespace rps::infrastructure
