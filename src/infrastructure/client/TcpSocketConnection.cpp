#include <QTcpSocket>

#include <infrastructure/client/TcpSocketConnection.hpp>

namespace rps::infrastructure::client
{

TcpSocketConnection::TcpSocketConnection(QTcpSocket* tcp_socket) : m_tcp_socket{tcp_socket}
{
}

bool TcpSocketConnection::is_connected() const
{
    return m_tcp_socket;
}

void TcpSocketConnection::send(std::string&& data)
{
    if (!m_tcp_socket)
        return;

    m_tcp_socket->write(data.c_str());
    m_tcp_socket->waitForBytesWritten();
}

void TcpSocketConnection::disconnect()
{
    delete m_tcp_socket;
    m_tcp_socket = nullptr;
}

} // namespace rps::infrastructure::client
