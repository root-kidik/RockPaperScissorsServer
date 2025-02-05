#pragma once

#include <RockPaperScissorsProtocol/interface/Connection.hpp>

class QTcpSocket;

namespace rps::infrastructure::client
{

class TcpSocketConnection final : public protocol::interface::Connection
{
public:
    TcpSocketConnection(QTcpSocket* tcp_socket);

    bool is_connected() const override;
    void send(const std::string& data) override;

    void disconnect();

private:
    QTcpSocket* m_tcp_socket;
};

} // namespace rps::infrastructure::client
