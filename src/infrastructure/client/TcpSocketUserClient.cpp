#include <QTcpSocket>

#include <infrastructure/client/TcpSocketUserClient.hpp>

namespace rps::infrastructure::client
{

TcpSocketUserClient::TcpSocketUserClient(QTcpSocket* tcp_socket) : m_tcp_socket{tcp_socket}
{
}

void TcpSocketUserClient::send(const std::string& data)
{
    m_tcp_socket->write(data.c_str());
}

} // namespace rps::infrastructure::client
