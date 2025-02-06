#pragma once

#include <RockPaperScissorsProtocol/interface/NominateCardCommandHandlerBase.hpp>

namespace rps::domain::interface
{
class RoomStorage;
} // namespace rps::domain::interface

namespace rps::domain::handler
{

class NominateCardCommandHandler final : public protocol::interface::NominateCardCommandHandlerBase
{
public:
    NominateCardCommandHandler(interface::RoomStorage& room_storage);

    protocol::entity::server::StatusResponse handle(protocol::entity::server::NominateCardRequest&& request,
                                                    const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    interface::RoomStorage& m_room_storage;
};

} // namespace rps::domain::handler
