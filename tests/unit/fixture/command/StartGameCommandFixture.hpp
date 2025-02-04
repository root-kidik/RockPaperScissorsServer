#include <mock/client/UserClientMock.hpp>
#include <mock/storage/RoomStorageMock.hpp>
#include <mock/storage/UserStorageMock.hpp>

#include <domain/handler/StartGameCommandHandler.hpp>

#include <RockPaperScissorsProtocol/entity/GameStartedCommandSender.hpp>

class StartGameCommandFixture : public testing::Test
{
public:
    RoomStorageMock                            room_storage;
    UserStorageMock                            user_storage;
    protocol::entity::GameStartedCommandSender sender;
    domain::handler::StartGameCommandHandler   start_game_command_handler{room_storage, user_storage, sender};
};
