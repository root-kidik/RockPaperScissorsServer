#include <fixture/model/RoomTest.hpp>

#include <RockPaperScissorsProtocol/entity/client/request/GameStarted.hpp>
#include <RockPaperScissorsProtocol/entity/client/request/NewPlayerAdded.hpp>

#include <gtest/gtest.h>

using testing::Return;

TEST_F(RoomTest, try_start_game_user_uuid_is_not_owner_uuid)
{
    domain::entity::Uuid user_uuid = "user_uuid";

    EXPECT_FALSE(room.try_start_game(user_uuid));
}

TEST_F(RoomTest, try_start_game_but_already_started)
{
    domain::entity::Uuid user_uuid       = "user_uuid";
    std::string          user_nickname   = "user_nickname";
    auto                 user_connection = std::make_shared<ConnectionMock>();

    EXPECT_TRUE(room.try_add_user(user_uuid, user_nickname, user_connection));

    // send: GameStarted. TODO: separate RandomGenerator
    EXPECT_CALL(*std::dynamic_pointer_cast<ConnectionMock>(user_connection),
                send(testing::_));

    EXPECT_CALL(*timer, start(std::chrono::milliseconds{protocol::entity::kTurnTime}, testing::_, false)).WillOnce(Return());

    EXPECT_TRUE(room.try_start_game(owner_uuid));
    EXPECT_FALSE(room.try_start_game(user_uuid));
}

TEST_F(RoomTest, try_start_game_started)
{
    domain::entity::Uuid user_uuid       = "user_uuid";
    std::string          user_nickname   = "user_nickname";
    auto                 user_connection = std::make_shared<ConnectionMock>();

    EXPECT_TRUE(room.try_add_user(user_uuid, user_nickname, user_connection));

    // send: GameStarted. TODO: separate RandomGenerator
    EXPECT_CALL(*std::dynamic_pointer_cast<ConnectionMock>(user_connection),
                send(testing::_));

    EXPECT_CALL(*timer, start(std::chrono::milliseconds{protocol::entity::kTurnTime}, testing::_, false)).WillOnce(Return());

    EXPECT_TRUE(room.try_start_game(owner_uuid));
}

TEST_F(RoomTest, try_add_user_game_already_started_not_added)
{
    domain::entity::Uuid user_uuid       = "user_uuid";
    std::string          user_nickname   = "user_nickname";
    auto                 user_connection = std::make_shared<ConnectionMock>();

    EXPECT_TRUE(room.try_add_user(user_uuid, user_nickname, user_connection));

    // send: GameStarted. TODO: separate RandomGenerator
    EXPECT_CALL(*std::dynamic_pointer_cast<ConnectionMock>(user_connection),
    send(testing::_));

    EXPECT_CALL(*timer, start(std::chrono::milliseconds{protocol::entity::kTurnTime}, testing::_, false)).WillOnce(Return());

    EXPECT_TRUE(room.try_start_game(owner_uuid));

    domain::entity::Uuid user_uuid_2     = "user_uuid_2";
    std::string          user_nickname_2 = "user_nickname_2";

    EXPECT_FALSE(room.try_add_user(user_uuid, user_nickname, connection));
}

TEST_F(RoomTest, try_add_user_too_many_users)
{
    room.try_add_user(owner_uuid, "owner_nickname", connection);

    for (std::size_t i = 0; i < protocol::entity::kMaxPlayersPerRoom - 1; i++)
    {
        domain::entity::Uuid user_uuid       = "user_uuid" + std::to_string(i);
        std::string          user_nickname   = "user_nickname" + std::to_string(i);
        auto                 user_connection = std::make_shared<ConnectionMock>();

        for (const auto& [player_uuid, player] : room.get_players())
        {
            protocol::entity::client::request::NewPlayerAdded request;
            request.user_nickname = user_nickname;

            EXPECT_CALL(*std::dynamic_pointer_cast<ConnectionMock>(player.connection),
                        send(protocol::util::serialize_message(std::move(request))))
                .WillOnce(Return());
        }

        room.try_add_user(user_uuid, user_nickname, user_connection);
    }

    EXPECT_FALSE(room.try_add_user("seven_user_uuid", "seven_user_nickname", std::make_shared<ConnectionMock>()));
}

TEST_F(RoomTest, try_add_user_wait_owner)
{
    for (std::size_t i = 0; i < protocol::entity::kMaxPlayersPerRoom - 1; i++)
    {
        domain::entity::Uuid user_uuid       = "user_uuid" + std::to_string(i);
        std::string          user_nickname   = "user_nickname" + std::to_string(i);
        auto                 user_connection = std::make_shared<ConnectionMock>();

        for (const auto& [player_uuid, player] : room.get_players())
        {
            protocol::entity::client::request::NewPlayerAdded request;
            request.user_nickname = user_nickname;

            EXPECT_CALL(*std::dynamic_pointer_cast<ConnectionMock>(player.connection),
                        send(protocol::util::serialize_message(std::move(request))))
                .WillOnce(Return());
        }

        room.try_add_user(user_uuid, user_nickname, user_connection);
    }

    EXPECT_FALSE(room.try_add_user("six_user_uuid", "six_user_nickname", std::make_shared<ConnectionMock>()));

    std::string owner_nickname = "owner_nickname";

    for (const auto& [player_uuid, player] : room.get_players())
    {
        protocol::entity::client::request::NewPlayerAdded request;
        request.user_nickname = owner_nickname;

        EXPECT_CALL(*std::dynamic_pointer_cast<ConnectionMock>(player.connection),
                    send(protocol::util::serialize_message(std::move(request))))
            .WillOnce(Return());
    }

    EXPECT_TRUE(room.try_add_user(owner_uuid, owner_nickname, connection));
}

TEST_F(RoomTest, try_add_user_added)
{
    domain::entity::Uuid user_uuid     = "user_uuid";
    std::string          user_nickname = "user_nickname";

    EXPECT_TRUE(room.try_add_user(user_uuid, user_nickname, connection));
}

TEST_F(RoomTest, try_add_same_user_twice)
{
    domain::entity::Uuid user_uuid     = "user_uuid";
    std::string          user_nickname = "user_nickname";

    EXPECT_TRUE(room.try_add_user(user_uuid, user_nickname, connection));
    EXPECT_FALSE(room.try_add_user(user_uuid, user_nickname, connection));
}

TEST_F(RoomTest, try_start_game_with_six_users)
{
    room.try_add_user(owner_uuid, "owner_nickname", connection);

    for (std::size_t i = 0; i < protocol::entity::kMaxPlayersPerRoom - 1; i++)
    {
        domain::entity::Uuid user_uuid       = "user_uuid" + std::to_string(i);
        std::string          user_nickname   = "user_nickname" + std::to_string(i);
        auto                 user_connection = std::make_shared<ConnectionMock>();

        for (const auto& [player_uuid, player] : room.get_players())
        {
            protocol::entity::client::request::NewPlayerAdded request;
            request.user_nickname = user_nickname;

            EXPECT_CALL(*std::dynamic_pointer_cast<ConnectionMock>(player.connection),
                        send(protocol::util::serialize_message(std::move(request))))
                .WillOnce(Return());
        }

        room.try_add_user(user_uuid, user_nickname, user_connection);
    }

    for (auto& [uuid, player] : room.get_players())
        EXPECT_CALL(*std::dynamic_pointer_cast<ConnectionMock>(player.connection), send(testing::_)).WillOnce(Return());

    EXPECT_CALL(*timer, start(std::chrono::milliseconds{protocol::entity::kTurnTime}, testing::_, false)).WillOnce(Return());

    EXPECT_TRUE(room.try_start_game(owner_uuid));
}

TEST_F(RoomTest, try_nominate_user_card_but_no_such_user)
{
    domain::entity::Uuid user_uuid = "user_uuid";

    auto nominated_card = protocol::entity::Card::Rock;

    EXPECT_FALSE(room.try_nominate_user_card(user_uuid, nominated_card));
}

TEST_F(RoomTest, try_nominate_user_card_but_no_such_card)
{
    domain::entity::Uuid user_uuid     = "user_uuid";
    std::string          user_nickname = "user_nickname";

    EXPECT_TRUE(room.try_add_user(user_uuid, user_nickname, connection));

    auto nominated_card = protocol::entity::Card::Rock;

    EXPECT_FALSE(room.try_nominate_user_card(user_uuid, nominated_card));
}

TEST_F(RoomTest, try_nominate_user_card_success)
{
    domain::entity::Uuid user_uuid     = "user_uuid";
    std::string          user_nickname = "user_nickname";

    EXPECT_TRUE(room.try_add_user(user_uuid, user_nickname, connection));

    EXPECT_CALL(*connection, send(testing::_)).WillOnce(Return());
    EXPECT_CALL(*timer, start(std::chrono::milliseconds{protocol::entity::kTurnTime}, testing::_, false)).WillOnce(Return());

    EXPECT_TRUE(room.try_start_game(owner_uuid));

    auto nominated_card = room.get_players().at(user_uuid).cards.back();

    EXPECT_TRUE(room.try_nominate_user_card(user_uuid, nominated_card));
}
