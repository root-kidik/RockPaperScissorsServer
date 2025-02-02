#pragma once

#include <domain/interface/Command.hpp>

namespace rps::domain::interface
{
class RoomStorage;
class UserStorage;
} // namespace rps::domain::interface

namespace rps::domain::command
{

class ConnectToRoomCommand final : public interface::Command
{
public:
    ConnectToRoomCommand(interface::RoomStorage& room_storage, interface::UserStorage& user_storage);

    void execute(const std::string& data, const std::shared_ptr<interface::UserClient>& user_client) override;

private:
    interface::RoomStorage& m_room_storage;
    interface::UserStorage& m_user_storage;
};

} // namespace rps::domain::command
