#include <fixture/model/round_pipe/RaisePlayerCardPipeFixture.hpp>

#include <gtest/gtest.h>

#include <RockPaperScissorsProtocol/entity/client/request/CardRaised.hpp>

using testing::Return;

TEST_F(RaisePlayerCardPipeFixture, run_raise_rock)
{
    auto raised_card = protocol::entity::Card::Rock;

    player.nominated_card = raised_card;
    player.cards.emplace_back(raised_card);

    protocol::entity::client::request::CardRaised request;
    request.card = raised_card;

    EXPECT_CALL(*connection, send(protocol::util::serialize_message(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_TRUE(player.cards.empty());

    EXPECT_TRUE(context.is_rock_raised);
    EXPECT_FALSE(context.is_paper_raised);
    EXPECT_FALSE(context.is_scissors_raised);
}

TEST_F(RaisePlayerCardPipeFixture, run_raise_paper)
{
    auto raised_card = protocol::entity::Card::Paper;

    player.nominated_card = raised_card;
    player.cards.emplace_back(raised_card);

    protocol::entity::client::request::CardRaised request;
    request.card = raised_card;

    EXPECT_CALL(*connection, send(protocol::util::serialize_message(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_TRUE(player.cards.empty());

    EXPECT_FALSE(context.is_rock_raised);
    EXPECT_TRUE(context.is_paper_raised);
    EXPECT_FALSE(context.is_scissors_raised);
}

TEST_F(RaisePlayerCardPipeFixture, run_raise_scissors)
{
    auto raised_card = protocol::entity::Card::Scissors;

    player.nominated_card = raised_card;
    player.cards.emplace_back(raised_card);

    protocol::entity::client::request::CardRaised request;
    request.card = raised_card;

    EXPECT_CALL(*connection, send(protocol::util::serialize_message(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_TRUE(player.cards.empty());

    EXPECT_FALSE(context.is_rock_raised);
    EXPECT_FALSE(context.is_paper_raised);
    EXPECT_TRUE(context.is_scissors_raised);
}
