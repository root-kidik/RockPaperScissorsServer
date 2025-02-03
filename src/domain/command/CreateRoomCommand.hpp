#pragma once

#include <domain/interface/Command.hpp>

namespace rps::domain::interface
{
class RoomStorage;
}

namespace rps::domain::command
{

class CreateRoomCommand final : public interface::Command
{
public:
    CreateRoomCommand(interface::RoomStorage& room_storage);

    void execute(const std::string& data, const std::shared_ptr<interface::UserConnection>& user_connection) override;

private:
    interface::RoomStorage& m_room_storage;
};

} // namespace rps::domain::command
