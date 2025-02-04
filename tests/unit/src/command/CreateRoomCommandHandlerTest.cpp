#include <fixture/command/CreateRoomCommandFixture.hpp>

#include <gtest/gtest.h>

using testing::Return;

TEST_F(CreateRoomCommandFixture, name_is_empty)
{
    protocol::entity::server::CreateRoomRequest request;
    request.room_name = "";
    request.user_uuid = "1234";

    auto response = create_room_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(CreateRoomCommandFixture, owner_uuid_is_empty)
{
    protocol::entity::server::CreateRoomRequest request;
    request.room_name = "";
    request.user_uuid = "1234";

    auto response = create_room_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(CreateRoomCommandFixture, room_exist)
{
    protocol::entity::server::CreateRoomRequest request;
    request.room_name = "user";
    request.user_uuid = "1234";

    EXPECT_CALL(room_storage, try_add_room(request.room_name, request.user_uuid)).WillOnce(Return(true));

    auto response = create_room_command_handler.handle(std::move(request), connection);

    EXPECT_TRUE(response.is_ok);
}

TEST_F(CreateRoomCommandFixture, room_not_exist)
{
    protocol::entity::server::CreateRoomRequest request;
    request.room_name = "user";
    request.user_uuid = "1234";

    EXPECT_CALL(room_storage, try_add_room(request.room_name, request.user_uuid)).WillOnce(Return(false));

    auto response = create_room_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}
