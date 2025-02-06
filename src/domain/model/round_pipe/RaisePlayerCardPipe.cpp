#include <algorithm>
#include <cassert>

#include <domain/model/round_pipe/RaisePlayerCardPipe.hpp>

#include <RockPaperScissorsProtocol/entity/client/request/CardRaisedRequest.hpp>

namespace rps::domain::model::round_pipe
{

RaisePlayerCardPipe::RaisePlayerCardPipe(protocol::entity::CommandSender& command_sender) :
m_command_sender{command_sender}
{
}

void RaisePlayerCardPipe::run(Room::RoundContext& context)
{
    auto& [player, player_uuid, is_rock_raised, is_paper_raised, is_scissors_raised] = context;

    assert(player.nominated_card && "Card must be nominated");

    auto card = player.nominated_card.value();

    if (card == protocol::entity::Card::Rock)
        is_rock_raised = true;
    else if (card == protocol::entity::Card::Paper)
        is_paper_raised = true;
    else if (card == protocol::entity::Card::Scissors)
        is_scissors_raised = true;
    else
        assert(false && "Raised some strange card");

    auto it = std::find(player.cards.begin(), player.cards.end(), card);

    assert(it != player.cards.end() && "Nominated card must be exists");

    player.cards.erase(it);

    protocol::entity::client::CardRaisedRequest request;
    request.card = player.nominated_card.value();

    m_command_sender.send(std::move(request), player.connection);
}

} // namespace rps::domain::model::round_pipe
