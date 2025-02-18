#include <fixture/model/round_pipe/DealMissingCardsTest.hpp>

#include <RockPaperScissorsProtocol/entity/client/request/DealMissingCard.hpp>

#include <gtest/gtest.h>

using testing::Return;

TEST_F(DealMissingCardsTest, run_with_empty_deck)
{
    pipe.run(context);

    EXPECT_TRUE(player.cards.empty());
}

TEST_F(DealMissingCardsTest, run_with_deck)
{
    auto back_card = protocol::entity::Card::Scissors;

    deck.emplace_back(protocol::entity::Card::Rock);
    deck.emplace_back(protocol::entity::Card::Paper);
    deck.emplace_back(back_card);

    protocol::entity::client::request::DealMissingCard request;
    request.card = back_card;

    EXPECT_CALL(*connection, send(protocol::util::serialize_message(std::move(request)))).WillOnce(Return());

    pipe.run(context);

    EXPECT_FALSE(player.cards.empty());
    EXPECT_TRUE(deck.size() == 2);
    EXPECT_TRUE(std::find(deck.begin(), deck.end(), back_card) == deck.end());

    EXPECT_TRUE(player.cards.front() == back_card);
}
