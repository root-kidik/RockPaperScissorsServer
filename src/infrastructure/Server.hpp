#pragma once

#include <QTcpServer>
#include <QTcpSocket>

#include <RockPaperScissorsProtocol/entity/NewPlayerAddedCommandSender.hpp>
#include <RockPaperScissorsProtocol/entity/GameStartedCommandSender.hpp>
#include <RockPaperScissorsProtocol/entity/server/ServerCommandExecutor.hpp>

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

    protocol::entity::NewPlayerAddedCommandSender m_new_player_added_command_sender;
    protocol::entity::GameStartedCommandSender    m_game_started_command_sender;

    protocol::entity::server::ServerCommandExecutor m_command_executor;
};

} // namespace rps::infrastructure
