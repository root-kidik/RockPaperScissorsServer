#pragma once

#include <domain/interface/CommandHandler.hpp>

namespace rps::domain::interface
{
class RoomStorage;
}

namespace rps::domain::command
{

class CreateRoomCommandHandler final : public interface::CommandHandler
{
public:
    CreateRoomCommandHandler(interface::RoomStorage& room_storage);

    void execute(const std::string& data, const std::shared_ptr<interface::UserConnection>& user_connection) override;

private:
    interface::RoomStorage& m_room_storage;
};

} // namespace rps::domain::command
