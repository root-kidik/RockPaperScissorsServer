#pragma once

#include <RockPaperScissorsProtocol/interface/CommandHandler.hpp>

namespace rps::domain::interface
{
class RoomStorage;
}

namespace rps::domain::handler
{

class CreateRoomCommandHandler final : public protocol::interface::CreateRoomCommandHandlerBase
{
public:
    CreateRoomCommandHandler(interface::RoomStorage& room_storage);

    protocol::entity::StatusResponse handle(protocol::entity::CreateRoomRequest&& request,
                                            const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    interface::RoomStorage& m_room_storage;
};

} // namespace rps::domain::handler
