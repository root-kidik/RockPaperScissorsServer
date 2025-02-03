#pragma once

#include <QTcpServer>
#include <QTcpSocket>

#include <domain/Server.hpp>

#include <infrastructure/generator/UuidGenerator.hpp>
#include <infrastructure/storage/MemoryRoomStorage.hpp>
#include <infrastructure/storage/MemoryUserStorage.hpp>

#include <RockPaperScissorsProtocol/interface/Connection.hpp>

namespace rps::infrastructure
{

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server();

private:
    generator::UuidGenerator   m_uuid_generator;
    storage::MemoryUserStorage m_memory_user_storage;
    storage::MemoryRoomStorage m_memory_room_storage;

    domain::Server m_server;
};

} // namespace rps::infrastructure
