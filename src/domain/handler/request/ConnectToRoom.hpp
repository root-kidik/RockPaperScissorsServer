#pragma once

#include <RockPaperScissorsProtocol/interface/server/handler/request/ConnectToRoom.hpp>

namespace rps::domain::interface
{
class RoomStorage;
class UserStorage;
} // namespace rps::domain::interface

namespace rps::domain::handler::request
{

class ConnectToRoom final : public protocol::interface::server::handler::request::ConnectToRoom
{
public:
    ConnectToRoom(interface::RoomStorage& room_storage, interface::UserStorage& user_storage);

    Response handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    interface::RoomStorage& m_room_storage;
    interface::UserStorage& m_user_storage;
};

} // namespace rps::domain::handler::request
