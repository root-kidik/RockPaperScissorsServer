#pragma once

#include <memory>

#include <RockPaperScissorsProtocol/interface/server/handler/StartGame.hpp>

namespace rps::domain::interface
{
class RoomStorage;
class UserStorage;
} // namespace rps::domain::interface

namespace rps::domain::handler
{

class StartGame final : public protocol::interface::server::handler::StartGame
{
public:
    StartGame(interface::RoomStorage& room_storage, interface::UserStorage& user_storage);

    protocol::entity::server::StatusResponse handle(protocol::entity::server::StartGameRequest&& request,
                                                    const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    interface::UserStorage& m_user_storage;
    interface::RoomStorage& m_room_storage;
};

} // namespace rps::domain::handler
