#pragma once

#include <RockPaperScissorsProtocol/interface/server/handler/NominateCard.hpp>

namespace rps::domain::interface
{
class RoomStorage;
} // namespace rps::domain::interface

namespace rps::domain::handler
{

class NominateCard final : public protocol::interface::server::handler::NominateCard
{
public:
    NominateCard(interface::RoomStorage& room_storage);

    protocol::entity::server::response::Status handle(protocol::entity::server::request::NominateCard&& request,
                                                      const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    interface::RoomStorage& m_room_storage;
};

} // namespace rps::domain::handler
