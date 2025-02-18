#include <mock/client/ConnectionMock.hpp>
#include <mock/storage/RoomStorageMock.hpp>
#include <mock/storage/UserStorageMock.hpp>

#include <RockPaperScissorsProtocol/entity/MessageSender.hpp>

#include <domain/handler/request/ConnectToRoom.hpp>

class ConnectToRoomTest : public testing::Test
{
public:
    RoomStorageMock                         room_storage;
    UserStorageMock                         user_storage;
    std::shared_ptr<ConnectionMock>         connection = std::make_shared<ConnectionMock>();
    domain::handler::request::ConnectToRoom connect_to_room_command_handler{room_storage, user_storage};
};
