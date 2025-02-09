#pragma once

#include <RockPaperScissorsProtocol/interface/server/handler/request/NominateCard.hpp>

namespace rps::domain::interface
{
class RoomStorage;
} // namespace rps::domain::interface

namespace rps::domain::handler::request
{

class NominateCard final : public protocol::interface::server::handler::request::NominateCard
{
public:
    NominateCard(interface::RoomStorage& room_storage);

    Response handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    interface::RoomStorage& m_room_storage;
};

} // namespace rps::domain::handler::request
