#include <fixture/command/ConnectToRoomCommandFixture.hpp>

#include <gtest/gtest.h>

using testing::Return;

TEST_F(ConnectToRoomCommandFixture, room_name_is_empty)
{
    entity::Uuid user_uuid = "1234";
    std::string  room_name = " ";

    EXPECT_CALL(*user_client, send("Error")).WillOnce(Return());

    create_command_room.execute(user_uuid + ' ' + room_name, user_client);
}

TEST_F(ConnectToRoomCommandFixture, user_uuid_is_empty)
{
    entity::Uuid user_uuid = " ";
    std::string  room_name = "user_room";
    
    EXPECT_CALL(*user_client, send("Error")).WillOnce(Return());

    create_command_room.execute(user_uuid + ' ' + room_name, user_client);
}

TEST_F(ConnectToRoomCommandFixture, room_exist)
{
    entity::Uuid user_uuid = "1234";
    std::string  room_name = "user_room";

    std::string  user_name = "user";

    entity::Uuid room_uuid  = "5678";
    entity::Uuid owner_uuid = "777";

    Room room{room_uuid, owner_uuid};

    EXPECT_CALL(room_storage, try_find_room(room_name)).WillOnce(Return(std::optional<std::reference_wrapper<Room>>{room}));
    EXPECT_CALL(user_storage, try_find_user_nickname(user_uuid)).WillOnce(Return(user_name));
    EXPECT_CALL(*user_client, send("Ok")).WillOnce(Return());

    create_command_room.execute(user_uuid + ' ' + room_name, user_client);
}

TEST_F(ConnectToRoomCommandFixture, room_not_exist)
{
    std::string  user_name = "user";
    entity::Uuid user_uuid = "1234";
    std::string  room_name = "user_room";

    EXPECT_CALL(room_storage, try_find_room(room_name)).WillOnce(Return(std::nullopt));
    EXPECT_CALL(*user_client, send("Error")).WillOnce(Return());

    create_command_room.execute(user_uuid + ' ' + room_name, user_client);
}

TEST_F(ConnectToRoomCommandFixture, user_uuid_wrong)
{
    entity::Uuid user_uuid = "1234";
    std::string  room_name = "user_room";

    entity::Uuid room_uuid  = "5678";
    entity::Uuid owner_uuid = "777";

    Room room{room_uuid, owner_uuid};

    EXPECT_CALL(room_storage, try_find_room(room_name)).WillOnce(Return(std::optional<std::reference_wrapper<Room>>{room}));
    EXPECT_CALL(user_storage, try_find_user_nickname(user_uuid)).WillOnce(Return(std::nullopt));
    EXPECT_CALL(*user_client, send("Error")).WillOnce(Return());

    create_command_room.execute(user_uuid + ' ' + room_name, user_client);
}
