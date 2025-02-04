#pragma once

#include <RockPaperScissorsProtocol/entity/NewPlayerAddedCommandSender.hpp>
#include <RockPaperScissorsProtocol/interface/ConnectToRoomCommandHandlerBase.hpp>

namespace rps::domain::interface
{
class RoomStorage;
class UserStorage;
} // namespace rps::domain::interface

namespace rps::domain::handler
{

class ConnectToRoomCommandHandler final : public protocol::interface::ConnectToRoomCommandHandlerBase
{
public:
    ConnectToRoomCommandHandler(interface::RoomStorage&                        room_storage,
                                interface::UserStorage&                        user_storage,
                                protocol::entity::NewPlayerAddedCommandSender& command_sender);

    protocol::entity::server::StatusResponse handle(protocol::entity::server::ConnectToRoomRequest&& request,
                                                    const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    interface::RoomStorage& m_room_storage;
    interface::UserStorage& m_user_storage;

    protocol::entity::NewPlayerAddedCommandSender& m_command_sender;
};

} // namespace rps::domain::handler
