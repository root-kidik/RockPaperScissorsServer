#include <mock/client/UserClientMock.hpp>
#include <mock/storage/RoomStorageMock.hpp>
#include <mock/storage/UserStorageMock.hpp>
#include <mock/utils/TimerMock.hpp>

#include <domain/handler/StartGameCommandHandler.hpp>

#include <RockPaperScissorsProtocol/entity/GameStartedCommandSender.hpp>

class StartGameCommandFixture : public testing::Test
{
public:
    RoomStorageMock                            room_storage;
    UserStorageMock                            user_storage;
    protocol::entity::GameStartedCommandSender sender;
    std::shared_ptr<TimerMock>                 timer_mock = std::make_shared<TimerMock>();
    domain::handler::StartGameCommandHandler start_game_command_handler{room_storage, user_storage, sender, timer_mock};
};
