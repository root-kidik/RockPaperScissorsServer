#include <mock/client/UserClientMock.hpp>
#include <mock/storage/RoomStorageMock.hpp>

#include <domain/command/CreateRoomCommandHandler.hpp>

class CreateRoomCommandFixture : public testing::Test
{
public:
    RoomStorageMock                           room_storage;
    std::shared_ptr<UserClientMock>           user_connection = std::make_shared<UserClientMock>();
    domain::command::CreateRoomCommandHandler create_room_command_handler{room_storage};
};
