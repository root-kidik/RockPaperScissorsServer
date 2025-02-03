#include <fixture/command/CreateRoomCommandFixture.hpp>

#include <gtest/gtest.h>

using testing::Return;

TEST_F(CreateRoomCommandFixture, name_is_empty)
{
    std::string          name       = " ";
    domain::entity::Uuid owner_uuid = "1234";

    EXPECT_CALL(*connection, send("Error")).WillOnce(Return());

    create_room_command_handler.execute(name + ' ' + owner_uuid, connection);
}

TEST_F(CreateRoomCommandFixture, owner_uuid_is_empty)
{
    std::string          name       = "user";
    domain::entity::Uuid owner_uuid = " ";

    EXPECT_CALL(*connection, send("Error")).WillOnce(Return());

    create_room_command_handler.execute(name + ' ' + owner_uuid, connection);
}

TEST_F(CreateRoomCommandFixture, room_exist)
{
    std::string          name       = "user";
    domain::entity::Uuid owner_uuid = "1234";

    EXPECT_CALL(room_storage, try_add_room(name, owner_uuid)).WillOnce(Return(true));
    EXPECT_CALL(*connection, send("Ok")).WillOnce(Return());

    create_room_command_handler.execute(name + ' ' + owner_uuid, connection);
}

TEST_F(CreateRoomCommandFixture, room_not_exist)
{
    std::string          name       = "user";
    domain::entity::Uuid owner_uuid = "1234";

    EXPECT_CALL(room_storage, try_add_room(name, owner_uuid)).WillOnce(Return(false));
    EXPECT_CALL(*connection, send("Error")).WillOnce(Return());

    create_room_command_handler.execute(name + ' ' + owner_uuid, connection);
}
