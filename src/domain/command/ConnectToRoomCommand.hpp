#pragma once

#include <domain/interface/Command.hpp>

namespace rps::domain::interface
{
class RoomStorage;
}

namespace rps::domain::command
{

class ConnectToRoomCommand final : public interface::Command
{
public:
    ConnectToRoomCommand(interface::RoomStorage& room_storage);

    void execute(const std::string& data, interface::UserClient& user_client) override;

private:
    interface::RoomStorage& m_room_storage;
};

} // namespace rps::domain::command
