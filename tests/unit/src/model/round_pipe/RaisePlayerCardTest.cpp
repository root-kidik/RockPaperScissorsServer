#include <fixture/model/round_pipe/RaisePlayerCardTest.hpp>

#include <RockPaperScissorsProtocol/entity/client/request/CardRaised.hpp>

#include <gtest/gtest.h>

using testing::Return;

TEST_F(RaisePlayerCardTest, run_raise_rock)
{
    auto raised_card = protocol::entity::Card::Rock;

    player.nominated_card = raised_card;
    player.cards.emplace_back(raised_card);

    protocol::entity::client::request::CardRaised request;
    request.card = raised_card;

    EXPECT_CALL(*connection, send(protocol::util::serialize_message(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_TRUE(player.cards.empty());
}

TEST_F(RaisePlayerCardTest, run_raise_paper)
{
    auto raised_card = protocol::entity::Card::Paper;

    player.nominated_card = raised_card;
    player.cards.emplace_back(raised_card);

    protocol::entity::client::request::CardRaised request;
    request.card = raised_card;

    EXPECT_CALL(*connection, send(protocol::util::serialize_message(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_TRUE(player.cards.empty());
}

TEST_F(RaisePlayerCardTest, run_raise_scissors)
{
    auto raised_card = protocol::entity::Card::Scissors;

    player.nominated_card = raised_card;
    player.cards.emplace_back(raised_card);

    protocol::entity::client::request::CardRaised request;
    request.card = raised_card;

    EXPECT_CALL(*connection, send(protocol::util::serialize_message(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_TRUE(player.cards.empty());
}
