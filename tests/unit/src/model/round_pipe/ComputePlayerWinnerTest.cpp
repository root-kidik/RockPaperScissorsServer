#include <fixture/model/round_pipe/ComputePlayerWinnerTest.hpp>

#include <RockPaperScissorsProtocol/entity/client/request/RoundInfo.hpp>

#include <gtest/gtest.h>

using testing::Return;

TEST_F(ComputePlayerWinnerTest, run_with_rock_all_losed)
{
    player.nominated_card = protocol::entity::Card::Rock;

    protocol::entity::client::request::RoundInfo request;
    request.is_winned = false;

    EXPECT_CALL(*connection, send(protocol::util::serialize_message(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 0);

    EXPECT_FALSE(player.nominated_card);
}

TEST_F(ComputePlayerWinnerTest, run_with_paper_all_losed)
{
    player.nominated_card = protocol::entity::Card::Paper;

    protocol::entity::client::request::RoundInfo request;
    request.is_winned = false;

    EXPECT_CALL(*connection, send(protocol::util::serialize_message(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 0);

    EXPECT_FALSE(player.nominated_card);
}

TEST_F(ComputePlayerWinnerTest, run_with_scissors_all_losed)
{
    player.nominated_card = protocol::entity::Card::Scissors;

    protocol::entity::client::request::RoundInfo request;
    request.is_winned = false;

    EXPECT_CALL(*connection, send(protocol::util::serialize_message(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 0);

    EXPECT_FALSE(player.nominated_card);
}

TEST_F(ComputePlayerWinnerTest, run_with_rock_win)
{
    auto second_connection = std::make_shared<ConnectionMock>();

    domain::model::Room::Player second_player;
    second_player.nominated_card = protocol::entity::Card::Scissors;
    second_player.connection     = second_connection;

    protocol::entity::client::request::RoundInfo second_request;
    second_request.is_winned = false;

    players.emplace_back(second_player);

    EXPECT_CALL(*second_connection, send(protocol::util::serialize_message(std::move(second_request)))).WillOnce(Return());

    player.nominated_card = protocol::entity::Card::Rock;

    protocol::entity::client::request::RoundInfo request;
    request.is_winned = true;

    EXPECT_CALL(*connection, send(protocol::util::serialize_message(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 1);
    EXPECT_EQ(second_player.wins_count, 0);

    EXPECT_FALSE(player.nominated_card);
    EXPECT_FALSE(second_player.nominated_card);
}

TEST_F(ComputePlayerWinnerTest, run_with_rock_lose)
{
    player.nominated_card = protocol::entity::Card::Rock;

    protocol::entity::client::request::RoundInfo request;
    request.is_winned = false;

    EXPECT_CALL(*connection, send(protocol::util::serialize_message(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 0);

    EXPECT_FALSE(player.nominated_card);
}

TEST_F(ComputePlayerWinnerTest, run_with_paper_win)
{
    auto second_connection = std::make_shared<ConnectionMock>();

    domain::model::Room::Player second_player;
    second_player.nominated_card = protocol::entity::Card::Rock;
    second_player.connection     = second_connection;

    protocol::entity::client::request::RoundInfo second_request;
    second_request.is_winned = false;

    players.emplace_back(second_player);

    EXPECT_CALL(*second_connection, send(protocol::util::serialize_message(std::move(second_request)))).WillOnce(Return());

    player.nominated_card = protocol::entity::Card::Paper;

    protocol::entity::client::request::RoundInfo request;
    request.is_winned = true;

    EXPECT_CALL(*connection, send(protocol::util::serialize_message(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 1);
    EXPECT_EQ(second_player.wins_count, 0);

    EXPECT_FALSE(player.nominated_card);
    EXPECT_FALSE(second_player.nominated_card);
}

TEST_F(ComputePlayerWinnerTest, run_with_paper_lose)
{
    player.nominated_card = protocol::entity::Card::Paper;

    protocol::entity::client::request::RoundInfo request;
    request.is_winned = false;

    EXPECT_CALL(*connection, send(protocol::util::serialize_message(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 0);

    EXPECT_FALSE(player.nominated_card);
}

TEST_F(ComputePlayerWinnerTest, run_with_scissors_win)
{
    auto second_connection = std::make_shared<ConnectionMock>();

    domain::model::Room::Player second_player;
    second_player.nominated_card = protocol::entity::Card::Paper;
    second_player.connection     = second_connection;

    protocol::entity::client::request::RoundInfo second_request;
    second_request.is_winned = false;

    players.emplace_back(second_player);

    EXPECT_CALL(*second_connection, send(protocol::util::serialize_message(std::move(second_request)))).WillOnce(Return());

    player.nominated_card = protocol::entity::Card::Scissors;

    protocol::entity::client::request::RoundInfo request;
    request.is_winned = true;

    EXPECT_CALL(*connection, send(protocol::util::serialize_message(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 1);
    EXPECT_EQ(second_player.wins_count, 0);

    EXPECT_FALSE(player.nominated_card);
    EXPECT_FALSE(second_player.nominated_card);
}

TEST_F(ComputePlayerWinnerTest, run_with_scissors_lose)
{
    player.nominated_card = protocol::entity::Card::Scissors;

    protocol::entity::client::request::RoundInfo request;
    request.is_winned = false;

    EXPECT_CALL(*connection, send(protocol::util::serialize_message(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 0);

    EXPECT_FALSE(player.nominated_card);
}
