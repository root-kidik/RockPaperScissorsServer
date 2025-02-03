#include <QTcpSocket>

#include <infrastructure/client/TcpSocketUserConnection.hpp>

namespace rps::infrastructure::client
{

TcpSocketUserConnection::TcpSocketUserConnection(QTcpSocket* tcp_socket) :
m_tcp_socket{tcp_socket},
m_is_connected{true}
{
}

bool TcpSocketUserConnection::is_connected() const
{
    return m_is_connected;
}

void TcpSocketUserConnection::send(const std::string& data)
{
    assert(m_is_connected && "TcpSocketUserConnection is not connected!");
    m_tcp_socket->write(data.c_str());
}

void TcpSocketUserConnection::disconnect()
{
    m_is_connected = false;
}

} // namespace rps::infrastructure::client
