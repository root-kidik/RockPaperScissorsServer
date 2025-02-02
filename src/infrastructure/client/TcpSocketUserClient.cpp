#include <QTcpSocket>

#include <infrastructure/client/TcpSocketUserClient.hpp>

namespace rps::infrastructure::client
{

TcpSocketUserClient::TcpSocketUserClient(QTcpSocket* tcp_socket) : m_tcp_socket{tcp_socket}, m_is_connected{true}
{
}

bool TcpSocketUserClient::is_connected() const
{
    return m_is_connected;
}

void TcpSocketUserClient::send(const std::string& data)
{
    assert(m_is_connected && "TcpSocketUserClient is not connected!");
    m_tcp_socket->write(data.c_str());
}

void TcpSocketUserClient::disconnect()
{
    m_is_connected = false;
}

} // namespace rps::infrastructure::client
