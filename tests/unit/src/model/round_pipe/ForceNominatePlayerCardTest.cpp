#include <fixture/model/round_pipe/ForceNominatePlayerCardTest.hpp>

#include <RockPaperScissorsProtocol/entity/client/request/CardForcedNominated.hpp>

#include <gtest/gtest.h>

using testing::Return;

TEST_F(ForceNominatePlayerCardTest, run_with_nominated_card)
{
    player.nominated_card = protocol::entity::Card::Paper;

    pipe.run(context);
}

TEST_F(ForceNominatePlayerCardTest, run_without_nominated_card_check_back_card_nominated)
{
    player.cards.push_back(protocol::entity::Card::Paper);
    player.cards.push_back(protocol::entity::Card::Rock);
    player.cards.push_back(protocol::entity::Card::Scissors);

    protocol::entity::client::request::CardForcedNominated request;
    request.card = player.cards.back();

    EXPECT_CALL(*connection, send(protocol::util::serialize_message(std::move(request)))).WillOnce(Return());

    pipe.run(context);
}
