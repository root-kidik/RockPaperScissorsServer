#include <fixture/command/ConnectToRoomCommandFixture.hpp>

#include <gtest/gtest.h>

#include <RockPaperScissorsProtocol/entity/client/ClientCommandType.hpp>

using testing::Return;

TEST_F(ConnectToRoomCommandFixture, room_name_is_empty)
{
    auto connection = std::make_shared<UserClientMock>();

    protocol::entity::ConnectToRoomRequest request;
    request.user_uuid = "1234";

    auto response = connect_to_room_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(ConnectToRoomCommandFixture, user_uuid_is_empty)
{
    auto connection = std::make_shared<UserClientMock>();

    protocol::entity::ConnectToRoomRequest request;
    request.room_name = "user_room";

    auto response = connect_to_room_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(ConnectToRoomCommandFixture, room_exist)
{
    auto connection = std::make_shared<UserClientMock>();

    domain::entity::Room room;
    room.name       = "user_room";
    room.owner_uuid = "5678";

    protocol::entity::ConnectToRoomRequest request;
    request.room_name = room.name;
    request.user_uuid = "1234";

    EXPECT_CALL(room_storage, try_find_room(request.room_name))
        .WillOnce(Return(std::optional<std::reference_wrapper<domain::entity::Room>>{room}));
    EXPECT_CALL(user_storage, try_find_user_nickname(request.user_uuid)).WillOnce(Return("user"));

    auto response = connect_to_room_command_handler.handle(std::move(request), connection);

    EXPECT_TRUE(response.is_ok);

    EXPECT_TRUE(room.players.size() == 1);
    EXPECT_TRUE(room.players.find(request.user_uuid) != room.players.end());
}

TEST_F(ConnectToRoomCommandFixture, room_not_exist)
{
    auto connection = std::make_shared<UserClientMock>();

    protocol::entity::ConnectToRoomRequest request;
    request.room_name = "user_room";
    request.user_uuid = "1234";

    EXPECT_CALL(room_storage, try_find_room(request.room_name)).WillOnce(Return(std::nullopt));

    auto response = connect_to_room_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(ConnectToRoomCommandFixture, user_uuid_wrong)
{
    auto connection = std::make_shared<UserClientMock>();

    domain::entity::Room room;
    room.name       = "user_room";
    room.owner_uuid = "5678";

    protocol::entity::ConnectToRoomRequest request;
    request.room_name = room.name;
    request.user_uuid = "1234";

    EXPECT_CALL(room_storage, try_find_room(request.room_name))
        .WillOnce(Return(std::optional<std::reference_wrapper<domain::entity::Room>>{room}));
    EXPECT_CALL(user_storage, try_find_user_nickname(request.user_uuid)).WillOnce(Return(std::nullopt));

    auto response = connect_to_room_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(ConnectToRoomCommandFixture, user_is_added_then_notifed_after_new_user_added)
{
    domain::entity::Room room;
    room.name       = "room_name";
    room.owner_uuid = "owner_uuid";

    domain::entity::User first_user{"first_uuid", "first_name", std::make_shared<UserClientMock>()};
    {
        EXPECT_CALL(room_storage, try_find_room(room.name))
            .WillOnce(Return(std::optional<std::reference_wrapper<domain::entity::Room>>{room}));
        EXPECT_CALL(user_storage, try_find_user_nickname(first_user.uuid)).WillOnce(Return(first_user.nickname));

        protocol::entity::ConnectToRoomRequest request;
        request.room_name = room.name;
        request.user_uuid = first_user.uuid;

        auto response = connect_to_room_command_handler.handle(std::move(request), first_user.connection);

        EXPECT_TRUE(response.is_ok);

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
        }

        // first user notified
        {
            EXPECT_CALL(user_storage, try_find_user(first_user.uuid))
                .WillOnce(Return(std::optional<std::reference_wrapper<const domain::entity::User>>{first_user}));

            std::string message = std::to_string(static_cast<protocol::entity::CommandRepresentation>(
                                      protocol::entity::ClientCommandType::NewPlayerAdded)) +
                                  ' ' + second_user.nickname;

            EXPECT_CALL(*std::dynamic_pointer_cast<UserClientMock>(first_user.connection), send(message)).WillOnce(Return());
        }

        protocol::entity::ConnectToRoomRequest request;
        request.room_name = room.name;
        request.user_uuid = second_user.uuid;

        auto response = connect_to_room_command_handler.handle(std::move(request), second_user.connection);

        EXPECT_TRUE(response.is_ok);

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

        protocol::entity::ConnectToRoomRequest request;
        request.room_name = room.name;
        request.user_uuid = owner_user.uuid;

        auto response = connect_to_room_command_handler.handle(std::move(request), owner_user.connection);

        EXPECT_TRUE(response.is_ok);

        EXPECT_TRUE(room.players.find(owner_user.uuid) != room.players.end());
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

        // owner notified
        {
            EXPECT_CALL(user_storage, try_find_user(owner_user.uuid))
                .WillOnce(Return(std::optional<std::reference_wrapper<const domain::entity::User>>{owner_user}));

            std::string message = std::to_string(static_cast<protocol::entity::CommandRepresentation>(
                                      protocol::entity::ClientCommandType::NewPlayerAdded)) +
                                  ' ' + user.nickname;

            EXPECT_CALL(*std::dynamic_pointer_cast<UserClientMock>(owner_user.connection), send(message)).WillOnce(Return());
        }

        // other users notified
        for (auto& existed_user : users)
        {
            EXPECT_CALL(user_storage, try_find_user(existed_user.uuid))
                .WillOnce(Return(std::optional<std::reference_wrapper<const domain::entity::User>>{existed_user}));

            std::string message = std::to_string(static_cast<protocol::entity::CommandRepresentation>(
                                      protocol::entity::ClientCommandType::NewPlayerAdded)) +
                                  ' ' + user.nickname;

            EXPECT_CALL(*std::dynamic_pointer_cast<UserClientMock>(existed_user.connection), send(message)).WillOnce(Return());
        }

        protocol::entity::ConnectToRoomRequest request;
        request.room_name = room.name;
        request.user_uuid = user.uuid;

        auto response = connect_to_room_command_handler.handle(std::move(request), user.connection);

        EXPECT_TRUE(response.is_ok);

        EXPECT_TRUE(room.players.size() == i + 2);
        EXPECT_TRUE(room.players.find(user.uuid) != room.players.end());

        users.push_back(std::move(user));
    }

    domain::entity::User seven_user{"seven_uuid", "seven_name", std::make_shared<UserClientMock>()};
    {
        EXPECT_CALL(room_storage, try_find_room(room.name))
            .WillOnce(Return(std::optional<std::reference_wrapper<domain::entity::Room>>{room}));

        protocol::entity::ConnectToRoomRequest request;
        request.room_name = room.name;
        request.user_uuid = seven_user.uuid;

        auto response = connect_to_room_command_handler.handle(std::move(request), seven_user.connection);

        EXPECT_FALSE(response.is_ok);

        EXPECT_TRUE(room.players.find(seven_user.uuid) == room.players.end());
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

        // other users notified
        for (auto& existed_user : users)
        {
            EXPECT_CALL(user_storage, try_find_user(existed_user.uuid))
                .WillOnce(Return(std::optional<std::reference_wrapper<const domain::entity::User>>{existed_user}));

            std::string message = std::to_string(static_cast<protocol::entity::CommandRepresentation>(
                                      protocol::entity::ClientCommandType::NewPlayerAdded)) +
                                  ' ' + user.nickname;

            EXPECT_CALL(*std::dynamic_pointer_cast<UserClientMock>(existed_user.connection), send(message)).WillOnce(Return());
        }

        protocol::entity::ConnectToRoomRequest request;
        request.room_name = room.name;
        request.user_uuid = user.uuid;

        auto response = connect_to_room_command_handler.handle(std::move(request), user.connection);

        EXPECT_TRUE(response.is_ok);

        EXPECT_TRUE(room.players.size() == i + 1);
        EXPECT_TRUE(room.players.find(user.uuid) != room.players.end());

        users.push_back(std::move(user));
    }

    domain::entity::User seven_user{"six_uuid", "six_name", std::make_shared<UserClientMock>()};
    {
        EXPECT_CALL(room_storage, try_find_room(room.name))
            .WillOnce(Return(std::optional<std::reference_wrapper<domain::entity::Room>>{room}));

        protocol::entity::ConnectToRoomRequest request;
        request.room_name = room.name;
        request.user_uuid = seven_user.uuid;

        auto response = connect_to_room_command_handler.handle(std::move(request), seven_user.connection);

        EXPECT_FALSE(response.is_ok);

        EXPECT_TRUE(room.players.find(seven_user.uuid) == room.players.end());
    }
}
