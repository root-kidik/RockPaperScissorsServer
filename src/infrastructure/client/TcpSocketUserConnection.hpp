#pragma once

#include <domain/interface/UserConnection.hpp>

class QTcpSocket;

namespace rps::infrastructure::client
{

class TcpSocketUserConnection final : public domain::interface::UserConnection
{
public:
    TcpSocketUserConnection(QTcpSocket* tcp_socket);

    bool is_connected() const override;
    void send(const std::string& data) override;

    void disconnect();

private:
    QTcpSocket* m_tcp_socket;
    bool        m_is_connected;
};

} // namespace rps::infrastructure::client
