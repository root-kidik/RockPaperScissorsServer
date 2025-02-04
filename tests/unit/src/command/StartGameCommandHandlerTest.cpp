#include <fixture/command/StartGameCommandFixture.hpp>

#include <gtest/gtest.h>

#include <RockPaperScissorsProtocol/entity/client/ClientCommandType.hpp>

using testing::Return;

TEST_F(StartGameCommandFixture, user_uuid_is_empty)
{
    auto connection = std::make_shared<UserClientMock>();

    protocol::entity::server::StartGameRequest request;
    request.user_uuid = "";

    auto response = start_game_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(StartGameCommandFixture, room_name_is_empty)
{
    auto connection = std::make_shared<UserClientMock>();

    protocol::entity::server::StartGameRequest request;
    request.user_uuid = "1234";
    request.room_name = "";

    auto response = start_game_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(StartGameCommandFixture, room_is_not_exist)
{
    auto connection = std::make_shared<UserClientMock>();

    protocol::entity::server::StartGameRequest request;
    request.user_uuid = "1234";
    request.room_name = "some_name";

    EXPECT_CALL(room_storage, try_find_room(request.room_name)).WillOnce(Return(std::nullopt));

    auto response = start_game_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(StartGameCommandFixture, user_uuid_is_not_owner_uuid)
{
    auto connection = std::make_shared<UserClientMock>();

    domain::entity::Room room;
    room.name       = "user_room";
    room.owner_uuid = "5678";

    protocol::entity::server::StartGameRequest request;
    request.user_uuid = "1234";
    request.room_name = room.name;

    EXPECT_CALL(room_storage, try_find_room(request.room_name)).WillOnce(Return(std::optional<std::reference_wrapper<domain::entity::Room>>{room}));

    auto response = start_game_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(StartGameCommandFixture, room_is_exist)
{
    auto connection = std::make_shared<UserClientMock>();

    domain::entity::Room room;
    room.name       = "user_room";
    room.owner_uuid = "5678";

    protocol::entity::server::StartGameRequest request;
    request.user_uuid = room.owner_uuid;
    request.room_name = room.name;

    EXPECT_CALL(room_storage, try_find_room(request.room_name)).WillOnce(Return(std::optional<std::reference_wrapper<domain::entity::Room>>{room}));

    auto response = start_game_command_handler.handle(std::move(request), connection);

    EXPECT_TRUE(response.is_ok);
}
