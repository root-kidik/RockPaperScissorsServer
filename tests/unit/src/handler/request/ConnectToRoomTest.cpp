#include <fixture/handler/request/ConnectToRoomTest.hpp>
#include <mock/model/RoomMock.hpp>

#include <RockPaperScissorsProtocol/entity/client/ClientMessageType.hpp>

#include <gtest/gtest.h>

using testing::Return;

TEST_F(ConnectToRoomTest, room_name_user_uuid_are_empty)
{
    protocol::entity::server::request::ConnectToRoom request;

    auto response = connect_to_room_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(ConnectToRoomTest, room_name_is_empty)
{
    protocol::entity::server::request::ConnectToRoom request;
    request.user_uuid = "user_uuid";

    auto response = connect_to_room_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(ConnectToRoomTest, user_uuid_is_empty)
{
    protocol::entity::server::request::ConnectToRoom request;
    request.room_name = "user_room";

    auto response = connect_to_room_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(ConnectToRoomTest, user_uuid_wrong)
{
    protocol::entity::server::request::ConnectToRoom request;
    request.room_name = "room_name";
    request.user_uuid = "user_uuid";

    EXPECT_CALL(user_storage, try_find_user_nickname(request.user_uuid)).WillOnce(Return(std::nullopt));

    auto response = connect_to_room_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(ConnectToRoomTest, room_not_exist)
{
    protocol::entity::server::request::ConnectToRoom request;
    request.room_name = "user_room";
    request.user_uuid = "user_uuid";

    std::string user_nickname = "user_nickname";

    EXPECT_CALL(user_storage, try_find_user_nickname(request.user_uuid)).WillOnce(Return(user_nickname));
    EXPECT_CALL(room_storage, try_find_room(request.room_name)).WillOnce(Return(std::nullopt));

    auto response = connect_to_room_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(ConnectToRoomTest, can_not_add_user)
{
    RoomMock room;

    protocol::entity::server::request::ConnectToRoom request;
    request.room_name = "user_room";
    request.user_uuid = "user_uuid";

    std::string user_nickname = "user_nickname";

    EXPECT_CALL(user_storage, try_find_user_nickname(request.user_uuid)).WillOnce(Return(user_nickname));
    EXPECT_CALL(room_storage, try_find_room(request.room_name))
        .WillOnce(Return(std::optional<std::reference_wrapper<domain::interface::Room>>{room}));
    EXPECT_CALL(room,
                try_add_user(request.user_uuid,
                             user_nickname,
                             std::static_pointer_cast<protocol::interface::Connection>(connection)))
        .WillOnce(Return(false));

    auto response = connect_to_room_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(ConnectToRoomTest, room_exist)
{
    RoomMock room;

    protocol::entity::server::request::ConnectToRoom request;
    request.room_name = "user_room";
    request.user_uuid = "user_uuid";

    std::string user_nickname = "user_nickname";

    EXPECT_CALL(user_storage, try_find_user_nickname(request.user_uuid)).WillOnce(Return(user_nickname));
    EXPECT_CALL(room_storage, try_find_room(request.room_name))
        .WillOnce(Return(std::optional<std::reference_wrapper<domain::interface::Room>>{room}));
    EXPECT_CALL(room,
                try_add_user(request.user_uuid,
                             user_nickname,
                             std::static_pointer_cast<protocol::interface::Connection>(connection)))
        .WillOnce(Return(true));
    EXPECT_CALL(room, get_player_nicknames()).WillOnce(Return(std::array<std::string, protocol::entity::kMaxPlayersPerRoom>{}));

    auto response = connect_to_room_command_handler.handle(std::move(request), connection);

    EXPECT_TRUE(response.is_ok);
}
