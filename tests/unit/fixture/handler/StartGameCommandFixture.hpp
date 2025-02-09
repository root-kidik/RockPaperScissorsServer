#include <mock/client/ConnectionMock.hpp>
#include <mock/storage/RoomStorageMock.hpp>
#include <mock/storage/UserStorageMock.hpp>
#include <mock/util/TimerMock.hpp>

#include <domain/handler/StartGame.hpp>

class StartGameCommandFixture : public testing::Test
{
public:
    RoomStorageMock                 room_storage;
    UserStorageMock                 user_storage;
    std::shared_ptr<ConnectionMock> connection = std::make_shared<ConnectionMock>();
    domain::handler::StartGame      start_game_command_handler{room_storage, user_storage};
};
