#include <fixture/handler/request/CreateRoomTest.hpp>

#include <gtest/gtest.h>

using testing::Return;

TEST_F(CreateRoomTest, room_name_and_user_uuid_are_empty)
{
    protocol::entity::server::request::CreateRoom request;

    auto response = create_room_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(CreateRoomTest, name_is_empty)
{
    protocol::entity::server::request::CreateRoom request;
    request.room_name = "";
    request.user_uuid = "user_uuid";

    auto response = create_room_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(CreateRoomTest, owner_uuid_is_empty)
{
    protocol::entity::server::request::CreateRoom request;
    request.room_name = "room_name";
    request.user_uuid = "";

    auto response = create_room_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(CreateRoomTest, room_not_exist)
{
    protocol::entity::server::request::CreateRoom request;
    request.room_name = "user";
    request.user_uuid = "1234";

    EXPECT_CALL(room_storage, try_add_room(request.room_name, request.user_uuid)).WillOnce(Return(false));

    auto response = create_room_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(CreateRoomTest, room_exist)
{
    protocol::entity::server::request::CreateRoom request;
    request.room_name = "user";
    request.user_uuid = "1234";

    EXPECT_CALL(room_storage, try_add_room(request.room_name, request.user_uuid)).WillOnce(Return(true));

    auto response = create_room_command_handler.handle(std::move(request), connection);

    EXPECT_TRUE(response.is_ok);
}
