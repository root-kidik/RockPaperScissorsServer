#include <mock/client/UserClientMock.hpp>
#include <mock/storage/RoomStorageMock.hpp>

#include <domain/command/CreateRoomCommand.hpp>

class CreateRoomCommandFixture : public testing::Test
{
public:
    RoomStorageMock                 room_storage;
    std::shared_ptr<UserClientMock> user_connection = std::make_shared<UserClientMock>();
    domain::command::CreateRoomCommand      create_command_room{room_storage};
};
