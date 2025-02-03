#pragma once

#include <RockPaperScissorsProtocol/interface/CommandHandler.hpp>

namespace rps::domain::interface
{
class RoomStorage;
}

namespace rps::domain::handler
{

class CreateRoomCommandHandler final : public protocol::interface::CommandHandler
{
public:
    CreateRoomCommandHandler(interface::RoomStorage& room_storage);

    void execute(const std::string& data, const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    interface::RoomStorage& m_room_storage;
};

} // namespace rps::domain::handler
