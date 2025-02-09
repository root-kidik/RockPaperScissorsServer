#include <fixture/handler/StartGameCommandFixture.hpp>
#include <mock/model/RoomMock.hpp>

#include <domain/model/Room.hpp>

#include <gtest/gtest.h>

#include <RockPaperScissorsProtocol/entity/client/ClientMessageType.hpp>

using testing::Return;

TEST_F(StartGameCommandFixture, user_uuid_and_name_are_empty)
{
    protocol::entity::server::request::StartGame request;

    auto response = start_game_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(StartGameCommandFixture, user_uuid_is_empty)
{
    protocol::entity::server::request::StartGame request;
    request.user_uuid = "";
    request.room_name = "room_name";

    auto response = start_game_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(StartGameCommandFixture, room_name_is_empty)
{
    protocol::entity::server::request::StartGame request;
    request.user_uuid = "1234";
    request.room_name = "";

    auto response = start_game_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(StartGameCommandFixture, room_is_not_exist)
{
    protocol::entity::server::request::StartGame request;
    request.user_uuid = "1234";
    request.room_name = "some_name";

    EXPECT_CALL(room_storage, try_find_room(request.room_name)).WillOnce(Return(std::nullopt));

    auto response = start_game_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(StartGameCommandFixture, user_uuid_is_not_owner_uuid)
{
    protocol::entity::server::request::StartGame request;
    request.room_name = "room_name";
    request.user_uuid = "user_uuid";

    RoomMock room;

    EXPECT_CALL(room_storage, try_find_room(request.room_name))
        .WillOnce(Return(std::optional<std::reference_wrapper<domain::interface::Room>>{room}));

    EXPECT_CALL(room, try_start_game(request.user_uuid)).WillOnce(Return(false));

    auto response = start_game_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(StartGameCommandFixture, room_is_exist)
{
    protocol::entity::server::request::StartGame request;
    request.room_name = "room_name";
    request.user_uuid = "user_uuid";

    RoomMock room;

    EXPECT_CALL(room_storage, try_find_room(request.room_name))
        .WillOnce(Return(std::optional<std::reference_wrapper<domain::interface::Room>>{room}));

    EXPECT_CALL(room, try_start_game(request.user_uuid)).WillOnce(Return(true));

    auto response = start_game_command_handler.handle(std::move(request), connection);

    EXPECT_TRUE(response.is_ok);
}
