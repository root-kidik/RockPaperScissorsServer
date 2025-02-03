#include <mock/client/UserClientMock.hpp>
#include <mock/storage/RoomStorageMock.hpp>
#include <mock/storage/UserStorageMock.hpp>

#include <domain/command/ConnectToRoomCommand.hpp>

class ConnectToRoomCommandFixture : public testing::Test
{
public:
    RoomStorageMock               room_storage;
    UserStorageMock               user_storage;
    domain::command::ConnectToRoomCommand create_command_room{room_storage, user_storage};
};
