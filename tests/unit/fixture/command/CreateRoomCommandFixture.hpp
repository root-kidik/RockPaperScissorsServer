#include <mock/client/UserClientMock.hpp>
#include <mock/storage/RoomStorageMock.hpp>

#include <domain/handler/CreateRoomCommandHandler.hpp>

class CreateRoomCommandFixture : public testing::Test
{
public:
    RoomStorageMock                           room_storage;
    std::shared_ptr<UserClientMock>           connection = std::make_shared<UserClientMock>();
    domain::handler::CreateRoomCommandHandler create_room_command_handler{room_storage};
};
