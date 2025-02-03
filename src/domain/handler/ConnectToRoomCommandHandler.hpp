#pragma once

#include <RockPaperScissorsProtocol/interface/CommandHandler.hpp>

namespace rps::domain::interface
{
class RoomStorage;
class UserStorage;
} // namespace rps::domain::interface

namespace rps::domain::handler
{

class ConnectToRoomCommandHandler final : public protocol::interface::CommandHandler
{
public:
    ConnectToRoomCommandHandler(interface::RoomStorage& room_storage, interface::UserStorage& user_storage);

    void execute(const std::string& data, const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    interface::RoomStorage& m_room_storage;
    interface::UserStorage& m_user_storage;
};

} // namespace rps::domain::handler
