#include <mock/client/ConnectionMock.hpp>
#include <mock/storage/RoomStorageMock.hpp>

#include <domain/handler/request/CreateRoom.hpp>

class CreateRoomTest : public testing::Test
{
public:
    RoomStorageMock                      room_storage;
    std::shared_ptr<ConnectionMock>      connection = std::make_shared<ConnectionMock>();
    domain::handler::request::CreateRoom create_room_command_handler{room_storage};
};
