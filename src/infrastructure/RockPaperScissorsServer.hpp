#pragma once

#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>

#include <infrastructure/generator/UuidGenerator.hpp>
#include <infrastructure/storage/MemoryRoomStorage.hpp>
#include <infrastructure/storage/MemoryUserStorage.hpp>

#include <RockPaperScissorsProtocol/entity/MessageSender.hpp>
#include <RockPaperScissorsProtocol/entity/server/ServerMessageExecutor.hpp>
#include <RockPaperScissorsProtocol/interface/Connection.hpp>

namespace rps::infrastructure
{

class RockPaperScissorsServer : public QTcpServer
{
    Q_OBJECT

public:
    RockPaperScissorsServer(int argc, char* argv[]);

    int run();

private:
    QCoreApplication m_app;

    generator::UuidGenerator        m_uuid_generator;
    protocol::entity::MessageSender m_command_sender;

    storage::MemoryUserStorage m_memory_user_storage;
    storage::MemoryRoomStorage m_memory_room_storage;

    protocol::entity::server::ServerMessageExecutor m_message_executor;
};

} // namespace rps::infrastructure
