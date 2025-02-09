#include <mock/client/ConnectionMock.hpp>
#include <mock/storage/RoomStorageMock.hpp>

#include <domain/handler/CreateRoom.hpp>

class CreateRoomCommandFixture : public testing::Test
{
public:
    RoomStorageMock                 room_storage;
    std::shared_ptr<ConnectionMock> connection = std::make_shared<ConnectionMock>();
    domain::handler::CreateRoom     create_room_command_handler{room_storage};
};
