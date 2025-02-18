#include <algorithm>
#include <cassert>

#include <RockPaperScissorsProtocol/entity/client/request/CardRaised.hpp>

#include <domain/model/round_pipe/RaisePlayerCard.hpp>

namespace rps::domain::model::round_pipe
{

RaisePlayerCard::RaisePlayerCard(protocol::entity::MessageSender& command_sender) : m_message_sender{command_sender}
{
}

void RaisePlayerCard::run(Room::RoundContext& context)
{
    auto& [player, player_uuid, cards, is_rock_raised, is_paper_raised, is_scissors_raised] = context;

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

    protocol::entity::client::request::CardRaised request;
    request.card = player.nominated_card.value();

    m_message_sender.send(std::move(request), player.connection);
}

} // namespace rps::domain::model::round_pipe
