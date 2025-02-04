#include <fixture/command/StartGameCommandFixture.hpp>

#include <gtest/gtest.h>

#include <RockPaperScissorsProtocol/entity/client/ClientCommandType.hpp>

using testing::Return;

TEST_F(StartGameCommandFixture, user_uuid_is_empty)
{
    protocol::entity::server::StartGameRequest request;
    request.user_uuid = "";

    auto response = start_game_command_handler.handle(std::move(request), std::make_shared<UserClientMock>());

    EXPECT_FALSE(response.is_ok);
}

TEST_F(StartGameCommandFixture, room_name_is_empty)
{
    protocol::entity::server::StartGameRequest request;
    request.user_uuid = "1234";
    request.room_name = "";

    auto response = start_game_command_handler.handle(std::move(request), std::make_shared<UserClientMock>());

    EXPECT_FALSE(response.is_ok);
}

TEST_F(StartGameCommandFixture, room_is_not_exist)
{
    protocol::entity::server::StartGameRequest request;
    request.user_uuid = "1234";
    request.room_name = "some_name";

    EXPECT_CALL(room_storage, try_find_room(request.room_name)).WillOnce(Return(std::nullopt));

    auto response = start_game_command_handler.handle(std::move(request), std::make_shared<UserClientMock>());

    EXPECT_FALSE(response.is_ok);
}

TEST_F(StartGameCommandFixture, user_uuid_is_not_owner_uuid)
{
    domain::entity::Room room;
    room.name       = "user_room";
    room.owner_uuid = "5678";

    protocol::entity::server::StartGameRequest request;
    request.user_uuid = "1234";
    request.room_name = room.name;

    EXPECT_CALL(room_storage, try_find_room(request.room_name))
        .WillOnce(Return(std::optional<std::reference_wrapper<domain::entity::Room>>{room}));

    auto response = start_game_command_handler.handle(std::move(request), std::make_shared<UserClientMock>());

    EXPECT_FALSE(response.is_ok);
}

TEST_F(StartGameCommandFixture, room_is_exist)
{
    domain::entity::Room room;
    room.name       = "user_room";
    room.owner_uuid = "5678";

    protocol::entity::server::StartGameRequest request;
    request.user_uuid = room.owner_uuid;
    request.room_name = room.name;

    EXPECT_CALL(room_storage, try_find_room(request.room_name))
        .WillOnce(Return(std::optional<std::reference_wrapper<domain::entity::Room>>{room}));

    auto response = start_game_command_handler.handle(std::move(request), std::make_shared<UserClientMock>());

    EXPECT_TRUE(response.is_ok);
}

TEST_F(StartGameCommandFixture, user_notified)
{
    domain::entity::Room room;
    room.name       = "user_room";
    room.owner_uuid = "5678";

    domain::entity::User user{"first_uuid", "first_name", std::make_shared<UserClientMock>()};

    room.players.emplace(user.uuid);

    // user notifed
    {
        EXPECT_CALL(user_storage, try_find_user(user.uuid))
            .WillOnce(Return(std::optional<std::reference_wrapper<const domain::entity::User>>{user}));

        std::string message = std::to_string(static_cast<protocol::entity::CommandRepresentation>(
                                  protocol::entity::client::ClientCommandType::GameStarted)) +
                              ' ' + room.name;

        EXPECT_CALL(*std::dynamic_pointer_cast<UserClientMock>(user.connection), send(message)).WillOnce(Return());
    }

    protocol::entity::server::StartGameRequest request;
    request.user_uuid = room.owner_uuid;
    request.room_name = room.name;

    EXPECT_CALL(room_storage, try_find_room(request.room_name))
        .WillOnce(Return(std::optional<std::reference_wrapper<domain::entity::Room>>{room}));

    auto response = start_game_command_handler.handle(std::move(request), std::make_shared<UserClientMock>());

    EXPECT_TRUE(response.is_ok);
}
