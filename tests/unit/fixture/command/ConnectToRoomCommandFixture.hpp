#include <mock/client/UserClientMock.hpp>
#include <mock/storage/RoomStorageMock.hpp>
#include <mock/storage/UserStorageMock.hpp>

#include <domain/command/ConnectToRoomCommandHandler.hpp>

class ConnectToRoomCommandFixture : public testing::Test
{
public:
    RoomStorageMock                              room_storage;
    UserStorageMock                              user_storage;
    domain::command::ConnectToRoomCommandHandler connect_to_room_command_handler{room_storage, user_storage};
};
