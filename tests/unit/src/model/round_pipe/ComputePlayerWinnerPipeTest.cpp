#include <fixture/model/round_pipe/ComputePlayerWinnerPipeFixture.hpp>

#include <gtest/gtest.h>

#include <RockPaperScissorsProtocol/entity/client/request/RoundInfoRequest.hpp>

using testing::Return;

TEST_F(ComputePlayerWinnerPipeFixture, run_with_rock_all_losed)
{
    context.is_paper_raised    = true;
    context.is_rock_raised     = true;
    context.is_scissors_raised = true;

    player.nominated_card = protocol::entity::Card::Rock;

    protocol::entity::client::RoundInfoRequest request;
    request.is_winned = false;

    EXPECT_CALL(*connection, send(protocol::util::serialize_request(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 0);

    EXPECT_FALSE(player.nominated_card);
}

TEST_F(ComputePlayerWinnerPipeFixture, run_with_paper_all_losed)
{
    context.is_paper_raised    = true;
    context.is_rock_raised     = true;
    context.is_scissors_raised = true;

    player.nominated_card = protocol::entity::Card::Paper;

    protocol::entity::client::RoundInfoRequest request;
    request.is_winned = false;

    EXPECT_CALL(*connection, send(protocol::util::serialize_request(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 0);

    EXPECT_FALSE(player.nominated_card);
}

TEST_F(ComputePlayerWinnerPipeFixture, run_with_scissors_all_losed)
{
    context.is_paper_raised    = true;
    context.is_rock_raised     = true;
    context.is_scissors_raised = true;

    player.nominated_card = protocol::entity::Card::Scissors;

    protocol::entity::client::RoundInfoRequest request;
    request.is_winned = false;

    EXPECT_CALL(*connection, send(protocol::util::serialize_request(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 0);

    EXPECT_FALSE(player.nominated_card);
}

TEST_F(ComputePlayerWinnerPipeFixture, run_with_rock_win)
{
    context.is_rock_raised     = true;
    context.is_scissors_raised = true;

    player.nominated_card = protocol::entity::Card::Rock;

    protocol::entity::client::RoundInfoRequest request;
    request.is_winned = true;

    EXPECT_CALL(*connection, send(protocol::util::serialize_request(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 1);

    EXPECT_FALSE(player.nominated_card);
}

TEST_F(ComputePlayerWinnerPipeFixture, run_with_rock_lose)
{
    context.is_paper_raised = true;
    context.is_rock_raised  = true;

    player.nominated_card = protocol::entity::Card::Rock;

    protocol::entity::client::RoundInfoRequest request;
    request.is_winned = false;

    EXPECT_CALL(*connection, send(protocol::util::serialize_request(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 0);

    EXPECT_FALSE(player.nominated_card);
}

TEST_F(ComputePlayerWinnerPipeFixture, run_with_paper_win)
{
    context.is_paper_raised = true;
    context.is_rock_raised  = true;

    player.nominated_card = protocol::entity::Card::Paper;

    protocol::entity::client::RoundInfoRequest request;
    request.is_winned = true;

    EXPECT_CALL(*connection, send(protocol::util::serialize_request(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 1);

    EXPECT_FALSE(player.nominated_card);
}

TEST_F(ComputePlayerWinnerPipeFixture, run_with_paper_lose)
{
    context.is_paper_raised    = true;
    context.is_scissors_raised = true;

    player.nominated_card = protocol::entity::Card::Paper;

    protocol::entity::client::RoundInfoRequest request;
    request.is_winned = false;

    EXPECT_CALL(*connection, send(protocol::util::serialize_request(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 0);

    EXPECT_FALSE(player.nominated_card);
}

TEST_F(ComputePlayerWinnerPipeFixture, run_with_scissors_win)
{
    context.is_scissors_raised = true;
    context.is_paper_raised    = true;

    player.nominated_card = protocol::entity::Card::Scissors;

    protocol::entity::client::RoundInfoRequest request;
    request.is_winned = true;

    EXPECT_CALL(*connection, send(protocol::util::serialize_request(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 1);

    EXPECT_FALSE(player.nominated_card);
}

TEST_F(ComputePlayerWinnerPipeFixture, run_with_scissors_lose)
{
    context.is_scissors_raised = true;
    context.is_rock_raised     = true;

    player.nominated_card = protocol::entity::Card::Scissors;

    protocol::entity::client::RoundInfoRequest request;
    request.is_winned = false;

    EXPECT_CALL(*connection, send(protocol::util::serialize_request(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_EQ(player.wins_count, 0);

    EXPECT_FALSE(player.nominated_card);
}
