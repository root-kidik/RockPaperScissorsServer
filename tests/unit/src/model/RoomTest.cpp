#include <fixture/model/RoomFixture.hpp>

#include <gtest/gtest.h>

#include <RockPaperScissorsProtocol/entity/client/request/NewPlayerAddedRequest.hpp>

using testing::Return;

TEST_F(RoomFixture, try_start_game_user_uuid_is_not_owner_uuid)
{
    domain::entity::Uuid user_uuid = "user_uuid";

    EXPECT_FALSE(room.try_start_game(user_uuid));
}

TEST_F(RoomFixture, try_start_game_but_already_started)
{
    domain::entity::Uuid user_uuid = "user_uuid";

    EXPECT_CALL(*timer, start(std::chrono::milliseconds{domain::interface::Room::kTurnTime}, testing::_, false))
        .WillOnce(Return());

    EXPECT_TRUE(room.try_start_game(owner_uuid));
    EXPECT_FALSE(room.try_start_game(user_uuid));
}

TEST_F(RoomFixture, try_start_game_started)
{
    EXPECT_CALL(*timer, start(std::chrono::milliseconds{domain::interface::Room::kTurnTime}, testing::_, false))
        .WillOnce(Return());

    EXPECT_TRUE(room.try_start_game(owner_uuid));
}

TEST_F(RoomFixture, try_add_user_game_already_started_not_added)
{
    domain::entity::Uuid user_uuid     = "user_uuid";
    std::string          user_nickname = "user_nickname";

    EXPECT_CALL(*timer, start(std::chrono::milliseconds{domain::interface::Room::kTurnTime}, testing::_, false))
        .WillOnce(Return());

    EXPECT_TRUE(room.try_start_game(owner_uuid));
    EXPECT_FALSE(room.try_add_user(user_uuid, user_nickname, connection));
}

TEST_F(RoomFixture, try_add_user_too_many_users)
{
    room.try_add_user(owner_uuid, "owner_nickname", connection);

    for (std::size_t i = 0; i < domain::interface::Room::kMaxPlayers - 1; i++)
    {
        domain::entity::Uuid user_uuid       = "user_uuid" + std::to_string(i);
        std::string          user_nickname   = "user_nickname" + std::to_string(i);
        auto                 user_connection = std::make_shared<ConnectionMock>();

        for (const auto& [player_uuid, player] : room.get_players())
        {
            std::string message = std::to_string(static_cast<protocol::entity::CommandRepresentation>(
                                      protocol::entity::client::ClientCommandType::NewPlayerAdded)) +
                                  ' ' + user_nickname;
            EXPECT_CALL(*std::dynamic_pointer_cast<ConnectionMock>(player.connection), send(message)).WillOnce(Return());
        }

        room.try_add_user(user_uuid, user_nickname, user_connection);
    }

    EXPECT_FALSE(room.try_add_user("seven_user_uuid", "seven_user_nickname", std::make_shared<ConnectionMock>()));
}

TEST_F(RoomFixture, try_add_user_wait_owner)
{
    for (std::size_t i = 0; i < domain::interface::Room::kMaxPlayers - 1; i++)
    {
        domain::entity::Uuid user_uuid       = "user_uuid" + std::to_string(i);
        std::string          user_nickname   = "user_nickname" + std::to_string(i);
        auto                 user_connection = std::make_shared<ConnectionMock>();

        for (const auto& [player_uuid, player] : room.get_players())
        {
            std::string message = std::to_string(static_cast<protocol::entity::CommandRepresentation>(
                                      protocol::entity::client::ClientCommandType::NewPlayerAdded)) +
                                  ' ' + user_nickname;
            EXPECT_CALL(*std::dynamic_pointer_cast<ConnectionMock>(player.connection), send(message)).WillOnce(Return());
        }

        room.try_add_user(user_uuid, user_nickname, user_connection);
    }

    EXPECT_FALSE(room.try_add_user("six_user_uuid", "six_user_nickname", std::make_shared<ConnectionMock>()));

    std::string owner_nickname = "owner_nickname";

    for (const auto& [player_uuid, player] : room.get_players())
    {
        std::string message = std::to_string(static_cast<protocol::entity::CommandRepresentation>(
                                  protocol::entity::client::ClientCommandType::NewPlayerAdded)) +
                              ' ' + owner_nickname;
        EXPECT_CALL(*std::dynamic_pointer_cast<ConnectionMock>(player.connection), send(message)).WillOnce(Return());
    }

    EXPECT_TRUE(room.try_add_user(owner_uuid, owner_nickname, connection));
}

TEST_F(RoomFixture, try_add_user_added)
{
    domain::entity::Uuid user_uuid     = "user_uuid";
    std::string          user_nickname = "user_nickname";

    EXPECT_TRUE(room.try_add_user(user_uuid, user_nickname, connection));
}

TEST_F(RoomFixture, try_add_same_user_twice)
{
    domain::entity::Uuid user_uuid     = "user_uuid";
    std::string          user_nickname = "user_nickname";

    EXPECT_TRUE(room.try_add_user(user_uuid, user_nickname, connection));
    EXPECT_FALSE(room.try_add_user(user_uuid, user_nickname, connection));
}

TEST_F(RoomFixture, try_start_game_with_six_users)
{
    room.try_add_user(owner_uuid, "owner_nickname", connection);

    for (std::size_t i = 0; i < domain::interface::Room::kMaxPlayers - 1; i++)
    {
        domain::entity::Uuid user_uuid       = "user_uuid" + std::to_string(i);
        std::string          user_nickname   = "user_nickname" + std::to_string(i);
        auto                 user_connection = std::make_shared<ConnectionMock>();

        for (const auto& [player_uuid, player] : room.get_players())
        {
            std::string message = std::to_string(static_cast<protocol::entity::CommandRepresentation>(
                                      protocol::entity::client::ClientCommandType::NewPlayerAdded)) +
                                  ' ' + user_nickname;
            EXPECT_CALL(*std::dynamic_pointer_cast<ConnectionMock>(player.connection), send(message)).WillOnce(Return());
        }

        room.try_add_user(user_uuid, user_nickname, user_connection);
    }

    for (auto& [uuid, player] : room.get_players())
        EXPECT_CALL(*std::dynamic_pointer_cast<ConnectionMock>(player.connection), send(testing::_)).WillOnce(Return());

    EXPECT_CALL(*timer, start(std::chrono::milliseconds{domain::interface::Room::kTurnTime}, testing::_, false))
        .WillOnce(Return());

    EXPECT_TRUE(room.try_start_game(owner_uuid));
}