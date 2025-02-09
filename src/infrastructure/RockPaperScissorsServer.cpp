#include <domain/handler/ConnectToRoom.hpp>
#include <domain/handler/CreateRoom.hpp>
#include <domain/handler/Register.hpp>
#include <domain/handler/StartGame.hpp>

#include <infrastructure/RockPaperScissorsServer.hpp>
#include <infrastructure/client/TcpSocketConnection.hpp>

namespace rps::infrastructure
{

RockPaperScissorsServer::RockPaperScissorsServer(int argc, char* argv[]) :
m_app{argc, argv},
m_memory_user_storage{m_uuid_generator},
m_memory_room_storage{m_uuid_generator, m_message_sender}
{
    m_message_executor.register_request_handler<domain::handler::Register>(m_memory_user_storage);
    m_message_executor.register_request_handler<domain::handler::CreateRoom>(m_memory_room_storage);
    m_message_executor.register_request_handler<domain::handler::ConnectToRoom>(m_memory_room_storage, m_memory_user_storage);
    m_message_executor.register_request_handler<domain::handler::StartGame>(m_memory_room_storage, m_memory_user_storage);

    connect(this,
            &QTcpServer::newConnection,
            this,
            [this]()
            {
                auto* connection = nextPendingConnection();

                auto connection_wrapper = std::make_shared<client::TcpSocketConnection>(connection);

                connect(connection,
                        &QTcpSocket::disconnected,
                        this,
                        [connection_wrapper]() { connection_wrapper->disconnect(); });

                connect(connection,
                        &QTcpSocket::readyRead,
                        this,
                        [connection, connection_wrapper, this]()
                        { m_message_executor.execute_message(connection->readAll().toStdString(), connection_wrapper); });
            });

    auto is_started = listen(QHostAddress::Any, 1234);
    assert(is_started && "Server not started");
}

int RockPaperScissorsServer::run()
{
    return m_app.exec();
}

} // namespace rps::infrastructure
