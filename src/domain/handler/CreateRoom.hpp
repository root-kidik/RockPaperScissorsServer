#pragma once

#include <RockPaperScissorsProtocol/interface/server/handler/request/CreateRoom.hpp>

namespace rps::domain::interface
{
class RoomStorage;
} // namespace rps::domain::interface

namespace rps::domain::handler
{

class CreateRoom final : public protocol::interface::server::handler::request::CreateRoom
{
public:
    CreateRoom(interface::RoomStorage& room_storage);

    Response handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    interface::RoomStorage& m_room_storage;
};

} // namespace rps::domain::handler
