#include <QTcpSocket>

#ifndef NDEBUG
#include <iostream>
#endif

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
    if (!m_tcp_socket || m_tcp_socket->state() != QAbstractSocket::ConnectedState)
        return;

    data += '\n';

#ifndef NDEBUG
    std::cout << "send: " << data;
#endif

    m_tcp_socket->write(data.c_str());
}

void TcpSocketConnection::disconnect()
{
    m_tcp_socket = nullptr;
}

} // namespace rps::infrastructure::client
