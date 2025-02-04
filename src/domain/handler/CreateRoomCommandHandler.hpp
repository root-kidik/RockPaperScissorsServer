#pragma once

#include <RockPaperScissorsProtocol/interface/CreateRoomCommandHandlerBase.hpp>

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

    protocol::entity::server::StatusResponse handle(protocol::entity::server::CreateRoomRequest&& request,
                                                    const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    interface::RoomStorage& m_room_storage;
};

} // namespace rps::domain::handler
