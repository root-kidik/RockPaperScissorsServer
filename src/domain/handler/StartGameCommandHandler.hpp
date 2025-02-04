#pragma once

#include <RockPaperScissorsProtocol/entity/GameStartedCommandSender.hpp>
#include <RockPaperScissorsProtocol/interface/StartGameCommandHandlerBase.hpp>

namespace rps::domain::interface
{
class RoomStorage;
class UserStorage;
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
};

} // namespace rps::domain::handler
