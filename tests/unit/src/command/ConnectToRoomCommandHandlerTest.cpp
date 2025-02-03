#include <fixture/command/ConnectToRoomCommandFixture.hpp>

#include <gtest/gtest.h>

#include <RockPaperScissorsProtocol/entity/client/ClientCommandType.hpp>

using testing::Return;

TEST_F(ConnectToRoomCommandFixture, room_name_is_empty)
{
    auto connection = std::make_shared<UserClientMock>();

    domain::entity::Uuid user_uuid = "1234";
    std::string          room_name = " ";

    EXPECT_CALL(*connection, send("Error")).WillOnce(Return());

    connect_to_room_command_handler.execute(user_uuid + ' ' + room_name, connection);
}

TEST_F(ConnectToRoomCommandFixture, user_uuid_is_empty)
{
    auto connection = std::make_shared<UserClientMock>();

    domain::entity::Uuid user_uuid = " ";
    std::string          room_name = "user_room";

    EXPECT_CALL(*connection, send("Error")).WillOnce(Return());

    connect_to_room_command_handler.execute(user_uuid + ' ' + room_name, connection);
}

TEST_F(ConnectToRoomCommandFixture, room_exist)
{
    auto connection = std::make_shared<UserClientMock>();

    domain::entity::Uuid user_uuid = "1234";
    std::string          room_name = "user_room";

    std::string user_name = "user";

    domain::entity::Uuid room_uuid  = "5678";
    domain::entity::Uuid owner_uuid = "777";

    domain::entity::Room room{room_uuid, owner_uuid};

    EXPECT_CALL(room_storage, try_find_room(room_name))
        .WillOnce(Return(std::optional<std::reference_wrapper<domain::entity::Room>>{room}));
    EXPECT_CALL(user_storage, try_find_user_nickname(user_uuid)).WillOnce(Return(user_name));
    EXPECT_CALL(*connection, send("Ok")).WillOnce(Return());

    connect_to_room_command_handler.execute(user_uuid + ' ' + room_name, connection);

    EXPECT_TRUE(room.players.size() == 1);
    EXPECT_TRUE(room.players.find(user_uuid) != room.players.end());
}

TEST_F(ConnectToRoomCommandFixture, room_not_exist)
{
    auto connection = std::make_shared<UserClientMock>();

    std::string          user_name = "user";
    domain::entity::Uuid user_uuid = "1234";
    std::string          room_name = "user_room";

    EXPECT_CALL(room_storage, try_find_room(room_name)).WillOnce(Return(std::nullopt));
    EXPECT_CALL(*connection, send("Error")).WillOnce(Return());

    connect_to_room_command_handler.execute(user_uuid + ' ' + room_name, connection);
}

TEST_F(ConnectToRoomCommandFixture, user_uuid_wrong)
{
    auto connection = std::make_shared<UserClientMock>();

    domain::entity::Uuid user_uuid = "1234";
    std::string          room_name = "user_room";

    domain::entity::Uuid room_uuid  = "5678";
    domain::entity::Uuid owner_uuid = "777";

    domain::entity::Room room{room_uuid, owner_uuid};

    EXPECT_CALL(room_storage, try_find_room(room_name))
        .WillOnce(Return(std::optional<std::reference_wrapper<domain::entity::Room>>{room}));
    EXPECT_CALL(user_storage, try_find_user_nickname(user_uuid)).WillOnce(Return(std::nullopt));
    EXPECT_CALL(*connection, send("Error")).WillOnce(Return());

    connect_to_room_command_handler.execute(user_uuid + ' ' + room_name, connection);
}

TEST_F(ConnectToRoomCommandFixture, user_is_added_then_notifed_after_new_user_added)
{
    domain::entity::Room room{"room_name", "owner_uuid"};

    domain::entity::User first_user{"first_uuid", "first_name", std::make_shared<UserClientMock>()};
    {
        EXPECT_CALL(room_storage, try_find_room(room.name))
            .WillOnce(Return(std::optional<std::reference_wrapper<domain::entity::Room>>{room}));
        EXPECT_CALL(user_storage, try_find_user_nickname(first_user.uuid)).WillOnce(Return(first_user.nickname));
        EXPECT_CALL(*std::dynamic_pointer_cast<UserClientMock>(first_user.connection), send("Ok")).WillOnce(Return());

        connect_to_room_command_handler.execute(first_user.uuid + ' ' + room.name, first_user.connection);

        EXPECT_TRUE(room.players.size() == 1);
        EXPECT_TRUE(room.players.find(first_user.uuid) != room.players.end());
    }

    domain::entity::User second_user{"second_uuid", "second_name", std::make_shared<UserClientMock>()};
    {
        // second user connect
        {
            EXPECT_CALL(room_storage, try_find_room(room.name))
                .WillOnce(Return(std::optional<std::reference_wrapper<domain::entity::Room>>{room}));
            EXPECT_CALL(user_storage, try_find_user_nickname(second_user.uuid)).WillOnce(Return(second_user.nickname));
            EXPECT_CALL(*std::dynamic_pointer_cast<UserClientMock>(second_user.connection), send("Ok")).WillOnce(Return());
        }

        // first user notified
        {
            EXPECT_CALL(user_storage, try_find_user(first_user.uuid))
                .WillOnce(Return(std::optional<std::reference_wrapper<const domain::entity::User>>{first_user}));

            std::string message = std::to_string(
                                      static_cast<std::uint32_t>(protocol::entity::ClientCommandType::NewPlayerAdded)) +
                                  ' ' + second_user.nickname;

            EXPECT_CALL(*std::dynamic_pointer_cast<UserClientMock>(first_user.connection), send(message)).WillOnce(Return());
        }

        connect_to_room_command_handler.execute(second_user.uuid + ' ' + room.name, second_user.connection);

        EXPECT_TRUE(room.players.size() == 2);
        EXPECT_TRUE(room.players.find(first_user.uuid) != room.players.end());
        EXPECT_TRUE(room.players.find(second_user.uuid) != room.players.end());
    }
}

TEST_F(ConnectToRoomCommandFixture, player_number_7_is_not_added)
{
    std::string          owner_uuid = "owner_uuid";
    domain::entity::Room room{"room_name", owner_uuid};

    domain::entity::User owner_user{owner_uuid, "owner_name", std::make_shared<UserClientMock>()};
    {
        EXPECT_CALL(room_storage, try_find_room(room.name))
            .WillOnce(Return(std::optional<std::reference_wrapper<domain::entity::Room>>{room}));
        EXPECT_CALL(user_storage, try_find_user_nickname(owner_user.uuid)).WillOnce(Return(owner_user.nickname));
        EXPECT_CALL(*std::dynamic_pointer_cast<UserClientMock>(owner_user.connection), send("Ok")).WillOnce(Return());

        connect_to_room_command_handler.execute(owner_user.uuid + ' ' + room.name, owner_user.connection);
    }

    std::vector<domain::entity::User> users;
    for (std::size_t i = 0; i < 5; i++)
    {
        domain::entity::User user{"first_uuid" + std::to_string(i),
                                  "first_name" + std::to_string(i),
                                  std::make_shared<UserClientMock>()};

        EXPECT_CALL(room_storage, try_find_room(room.name))
            .WillOnce(Return(std::optional<std::reference_wrapper<domain::entity::Room>>{room}));
        EXPECT_CALL(user_storage, try_find_user_nickname(user.uuid)).WillOnce(Return(user.nickname));
        EXPECT_CALL(*std::dynamic_pointer_cast<UserClientMock>(user.connection), send("Ok")).WillOnce(Return());

        // owner notified
        {
            EXPECT_CALL(user_storage, try_find_user(owner_user.uuid))
                .WillOnce(Return(std::optional<std::reference_wrapper<const domain::entity::User>>{owner_user}));

            std::string message = std::to_string(
                                      static_cast<std::uint32_t>(protocol::entity::ClientCommandType::NewPlayerAdded)) +
                                  ' ' + user.nickname;

            EXPECT_CALL(*std::dynamic_pointer_cast<UserClientMock>(owner_user.connection), send(message)).WillOnce(Return());
        }

        for (auto& existed_user : users)
        {
            EXPECT_CALL(user_storage, try_find_user(existed_user.uuid))
                .WillOnce(Return(std::optional<std::reference_wrapper<const domain::entity::User>>{existed_user}));

            std::string message = std::to_string(
                                      static_cast<std::uint32_t>(protocol::entity::ClientCommandType::NewPlayerAdded)) +
                                  ' ' + user.nickname;

            EXPECT_CALL(*std::dynamic_pointer_cast<UserClientMock>(existed_user.connection), send(message)).WillOnce(Return());
        }

        connect_to_room_command_handler.execute(user.uuid + ' ' + room.name, user.connection);

        EXPECT_TRUE(room.players.size() == i + 2);
        EXPECT_TRUE(room.players.find(user.uuid) != room.players.end());

        users.push_back(std::move(user));
    }

    domain::entity::User seven_user{"seven_uuid", "seven_name", std::make_shared<UserClientMock>()};
    {
        EXPECT_CALL(room_storage, try_find_room(room.name))
            .WillOnce(Return(std::optional<std::reference_wrapper<domain::entity::Room>>{room}));
        EXPECT_CALL(*std::dynamic_pointer_cast<UserClientMock>(seven_user.connection), send("Error")).WillOnce(Return());

        connect_to_room_command_handler.execute(seven_user.uuid + ' ' + room.name, seven_user.connection);
    }
}

TEST_F(ConnectToRoomCommandFixture, player_numer_6_is_not_added_because_owner_is_not_yes_added_and_owner_is_added)
{
    domain::entity::Room room{"room_name", "owner_uuid"};

    std::vector<domain::entity::User> users;
    for (std::size_t i = 0; i < 5; i++)
    {
        domain::entity::User user{"first_uuid" + std::to_string(i),
                                  "first_name" + std::to_string(i),
                                  std::make_shared<UserClientMock>()};

        EXPECT_CALL(room_storage, try_find_room(room.name))
            .WillOnce(Return(std::optional<std::reference_wrapper<domain::entity::Room>>{room}));
        EXPECT_CALL(user_storage, try_find_user_nickname(user.uuid)).WillOnce(Return(user.nickname));
        EXPECT_CALL(*std::dynamic_pointer_cast<UserClientMock>(user.connection), send("Ok")).WillOnce(Return());

        for (auto& existed_user : users)
        {
            EXPECT_CALL(user_storage, try_find_user(existed_user.uuid))
                .WillOnce(Return(std::optional<std::reference_wrapper<const domain::entity::User>>{existed_user}));

            std::string message = std::to_string(
                                      static_cast<std::uint32_t>(protocol::entity::ClientCommandType::NewPlayerAdded)) +
                                  ' ' + user.nickname;

            EXPECT_CALL(*std::dynamic_pointer_cast<UserClientMock>(existed_user.connection), send(message)).WillOnce(Return());
        }

        connect_to_room_command_handler.execute(user.uuid + ' ' + room.name, user.connection);

        EXPECT_TRUE(room.players.size() == i + 1);
        EXPECT_TRUE(room.players.find(user.uuid) != room.players.end());

        users.push_back(std::move(user));
    }

    domain::entity::User seven_user{"six_uuid", "six_name", std::make_shared<UserClientMock>()};
    {
        EXPECT_CALL(room_storage, try_find_room(room.name))
            .WillOnce(Return(std::optional<std::reference_wrapper<domain::entity::Room>>{room}));
        EXPECT_CALL(*std::dynamic_pointer_cast<UserClientMock>(seven_user.connection), send("Error")).WillOnce(Return());

        connect_to_room_command_handler.execute(seven_user.uuid + ' ' + room.name, seven_user.connection);
    }
}
