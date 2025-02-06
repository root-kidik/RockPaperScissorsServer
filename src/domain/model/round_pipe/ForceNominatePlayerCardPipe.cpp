#include <cassert>

#include <domain/model/round_pipe/ForceNominatePlayerCardPipe.hpp>

#include <RockPaperScissorsProtocol/entity/client/request/CardForcedNominatedRequest.hpp>

namespace rps::domain::model::round_pipe
{

ForceNominatePlayerCardPipe::ForceNominatePlayerCardPipe(protocol::entity::CommandSender& command_sender) :
m_command_sender{command_sender}
{
}

void ForceNominatePlayerCardPipe::run(Room::RoundContext& context)
{
    auto& player      = context.player;
    auto& player_uuid = context.player_uuid;

    assert(!player.cards.empty() && "Player must have cards");

    if (player.nominated_card)
        return;

    player.nominated_card = player.cards.back();

    protocol::entity::client::CardForcedNominatedRequest request;
    request.card = player.cards.back();

    m_command_sender.send(std::move(request), player.connection);
}

} // namespace rps::domain::model::round_pipe
