#include <fixture/model/round_pipe/ForceNominatePlayerCardPipeFixture.hpp>

#include <gtest/gtest.h>

#include <RockPaperScissorsProtocol/entity/client/request/CardForcedNominated.hpp>

using testing::Return;

TEST_F(ForceNominatePlayerCardPipeFixture, run_with_nominated_card)
{
    player.nominated_card = protocol::entity::Card::Paper;

    pipe.run(context);
}

TEST_F(ForceNominatePlayerCardPipeFixture, run_without_nominated_card_check_back_card_nominated)
{
    player.cards.push_back(protocol::entity::Card::Paper);
    player.cards.push_back(protocol::entity::Card::Rock);
    player.cards.push_back(protocol::entity::Card::Scissors);

    protocol::entity::client::request::CardForcedNominated request;
    request.card = player.cards.back();

    EXPECT_CALL(*connection, send(protocol::util::serialize_command(std::move(request)))).WillOnce(Return());

    pipe.run(context);
}
