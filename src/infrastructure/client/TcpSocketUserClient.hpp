#pragma once

#include <domain/interface/UserClient.hpp>

class QTcpSocket;

namespace rps::infrastructure::client
{

class TcpSocketUserClient final : public domain::interface::UserClient
{
public:
    TcpSocketUserClient(QTcpSocket* tcp_socket);

    void send(const std::string& data) override;

private:
    QTcpSocket* m_tcp_socket;
};

} // namespace rps::infrastructure::client
