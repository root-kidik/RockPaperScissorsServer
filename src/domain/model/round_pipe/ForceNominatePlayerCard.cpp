#include <cassert>

#include <RockPaperScissorsProtocol/entity/client/request/CardForcedNominated.hpp>

#include <domain/model/round_pipe/ForceNominatePlayerCard.hpp>

namespace rps::domain::model::round_pipe
{

ForceNominatePlayerCard::ForceNominatePlayerCard(protocol::entity::MessageSender& command_sender) :
m_message_sender{command_sender}
{
}

void ForceNominatePlayerCard::run(Room::RoundContext& context)
{
    auto& player      = context.player;
    auto& player_uuid = context.player_uuid;

    if (player.nominated_card)
        return;

    assert(!player.cards.empty() && "Player must have cards");

    player.nominated_card = player.cards.back();

    protocol::entity::client::request::CardForcedNominated request;
    request.card = player.cards.back();

    m_message_sender.send(std::move(request), player.connection);
}

} // namespace rps::domain::model::round_pipe
