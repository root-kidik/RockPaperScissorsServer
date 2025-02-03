#include <fixture/command/CreateRoomCommandFixture.hpp>

#include <gtest/gtest.h>

using testing::Return;

TEST_F(CreateRoomCommandFixture, name_is_empty)
{
    std::string  name = " ";
    entity::Uuid owner_uuid = "1234";

    EXPECT_CALL(*user_client, send("Error")).WillOnce(Return());

    create_command_room.execute(name + ' ' + owner_uuid, user_client);
}

TEST_F(CreateRoomCommandFixture, owner_uuid_is_empty)
{
    std::string  name = "user";
    entity::Uuid owner_uuid = " ";

    EXPECT_CALL(*user_client, send("Error")).WillOnce(Return());

    create_command_room.execute(name + ' ' + owner_uuid, user_client);
}

TEST_F(CreateRoomCommandFixture, room_exist)
{
    std::string  name = "user";
    entity::Uuid owner_uuid = "1234";

    EXPECT_CALL(room_storage, try_add_room(name, owner_uuid)).WillOnce(Return(true));
    EXPECT_CALL(*user_client, send("Ok")).WillOnce(Return());

    create_command_room.execute(name + ' ' + owner_uuid, user_client);
}

TEST_F(CreateRoomCommandFixture, room_not_exist)
{
    std::string  name = "user";
    entity::Uuid owner_uuid = "1234";

    EXPECT_CALL(room_storage, try_add_room(name, owner_uuid)).WillOnce(Return(false));
    EXPECT_CALL(*user_client, send("Error")).WillOnce(Return());

    create_command_room.execute(name + ' ' + owner_uuid, user_client);
}
