#include <fixture/model/round_pipe/ComputePlayerWinnerPipeFixture.hpp>

#include <gtest/gtest.h>

#include <RockPaperScissorsProtocol/entity/client/ClientCommandType.hpp>

using testing::Return;

TEST_F(ComputePlayerWinnerPipeFixture, run_with_rock_all_losed)
{
    context.is_paper_raised    = true;
    context.is_rock_raised     = true;
    context.is_scissors_raised = true;

    player.connection     = connection;
    player.nominated_card = protocol::entity::Card::Rock;

    std::string message = std::to_string(static_cast<protocol::entity::CommandRepresentation>(
                              protocol::entity::client::ClientCommandType::RoundInfo)) +
                          ' ' + std::to_string(false);

    EXPECT_CALL(*connection, send(message)).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 0);
}

TEST_F(ComputePlayerWinnerPipeFixture, run_with_paper_all_losed)
{
    context.is_paper_raised    = true;
    context.is_rock_raised     = true;
    context.is_scissors_raised = true;

    player.connection     = connection;
    player.nominated_card = protocol::entity::Card::Paper;

    std::string message = std::to_string(static_cast<protocol::entity::CommandRepresentation>(
                              protocol::entity::client::ClientCommandType::RoundInfo)) +
                          ' ' + std::to_string(false);

    EXPECT_CALL(*connection, send(message)).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 0);
}

TEST_F(ComputePlayerWinnerPipeFixture, run_with_scissors_all_losed)
{
    context.is_paper_raised    = true;
    context.is_rock_raised     = true;
    context.is_scissors_raised = true;

    player.connection     = connection;
    player.nominated_card = protocol::entity::Card::Scissors;

    std::string message = std::to_string(static_cast<protocol::entity::CommandRepresentation>(
                              protocol::entity::client::ClientCommandType::RoundInfo)) +
                          ' ' + std::to_string(false);

    EXPECT_CALL(*connection, send(message)).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 0);
}

TEST_F(ComputePlayerWinnerPipeFixture, run_with_rock_win)
{
    context.is_rock_raised     = true;
    context.is_scissors_raised = true;

    player.connection     = connection;
    player.nominated_card = protocol::entity::Card::Rock;

    std::string message = std::to_string(static_cast<protocol::entity::CommandRepresentation>(
                              protocol::entity::client::ClientCommandType::RoundInfo)) +
                          ' ' + std::to_string(true);

    EXPECT_CALL(*connection, send(message)).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 1);
}

TEST_F(ComputePlayerWinnerPipeFixture, run_with_rock_lose)
{
    context.is_paper_raised = true;
    context.is_rock_raised  = true;

    player.connection     = connection;
    player.nominated_card = protocol::entity::Card::Rock;

    std::string message = std::to_string(static_cast<protocol::entity::CommandRepresentation>(
                              protocol::entity::client::ClientCommandType::RoundInfo)) +
                          ' ' + std::to_string(false);

    EXPECT_CALL(*connection, send(message)).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 0);
}

TEST_F(ComputePlayerWinnerPipeFixture, run_with_paper_win)
{
    context.is_paper_raised = true;
    context.is_rock_raised  = true;

    player.connection     = connection;
    player.nominated_card = protocol::entity::Card::Paper;

    std::string message = std::to_string(static_cast<protocol::entity::CommandRepresentation>(
                              protocol::entity::client::ClientCommandType::RoundInfo)) +
                          ' ' + std::to_string(true);

    EXPECT_CALL(*connection, send(message)).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 1);
}

TEST_F(ComputePlayerWinnerPipeFixture, run_with_paper_lose)
{
    context.is_paper_raised    = true;
    context.is_scissors_raised = true;

    player.connection     = connection;
    player.nominated_card = protocol::entity::Card::Paper;

    std::string message = std::to_string(static_cast<protocol::entity::CommandRepresentation>(
                              protocol::entity::client::ClientCommandType::RoundInfo)) +
                          ' ' + std::to_string(false);

    EXPECT_CALL(*connection, send(message)).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 0);
}

TEST_F(ComputePlayerWinnerPipeFixture, run_with_scissors_win)
{
    context.is_scissors_raised = true;
    context.is_paper_raised    = true;

    player.connection     = connection;
    player.nominated_card = protocol::entity::Card::Scissors;

    std::string message = std::to_string(static_cast<protocol::entity::CommandRepresentation>(
                              protocol::entity::client::ClientCommandType::RoundInfo)) +
                          ' ' + std::to_string(true);

    EXPECT_CALL(*connection, send(message)).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 1);
}

TEST_F(ComputePlayerWinnerPipeFixture, run_with_scissors_lose)
{
    context.is_scissors_raised = true;
    context.is_rock_raised     = true;

    player.connection     = connection;
    player.nominated_card = protocol::entity::Card::Scissors;

    std::string message = std::to_string(static_cast<protocol::entity::CommandRepresentation>(
                              protocol::entity::client::ClientCommandType::RoundInfo)) +
                          ' ' + std::to_string(false);

    EXPECT_CALL(*connection, send(message)).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 0);
}
