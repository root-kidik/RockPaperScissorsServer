#include <mock/client/ConnectionMock.hpp>
#include <mock/storage/RoomStorageMock.hpp>
#include <mock/storage/UserStorageMock.hpp>

#include <domain/handler/ConnectToRoomCommandHandler.hpp>

#include <RockPaperScissorsProtocol/entity/CommandSender.hpp>

class ConnectToRoomCommandFixture : public testing::Test
{
public:
    RoomStorageMock                              room_storage;
    UserStorageMock                              user_storage;
    std::shared_ptr<ConnectionMock>              connection = std::make_shared<ConnectionMock>();
    domain::handler::ConnectToRoomCommandHandler connect_to_room_command_handler{room_storage, user_storage};
};
