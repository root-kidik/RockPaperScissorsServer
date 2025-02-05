#pragma once

#include <memory>

#include <RockPaperScissorsProtocol/entity/GameStartedCommandSender.hpp>
#include <RockPaperScissorsProtocol/interface/StartGameCommandHandlerBase.hpp>

namespace rps::domain::interface
{
class RoomStorage;
class UserStorage;
class Timer;
} // namespace rps::domain::interface

namespace rps::domain::handler
{

class StartGameCommandHandler final : public protocol::interface::StartGameCommandHandlerBase
{
public:
    StartGameCommandHandler(interface::RoomStorage&                     room_storage,
                            interface::UserStorage&                     user_storage,
                            protocol::entity::GameStartedCommandSender& command_sender);

    protocol::entity::server::StatusResponse handle(protocol::entity::server::StartGameRequest&& request,
                                                    const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    interface::UserStorage& m_user_storage;
    interface::RoomStorage& m_room_storage;

    protocol::entity::GameStartedCommandSender& m_command_sender;

    std::shared_ptr<interface::Timer> m_timer;
};

} // namespace rps::domain::handler
