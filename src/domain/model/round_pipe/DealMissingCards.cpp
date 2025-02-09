#include <cassert>

#include <domain/model/round_pipe/DealMissingCards.hpp>

#include <RockPaperScissorsProtocol/entity/client/request/DealMissingCard.hpp>

namespace rps::domain::model::round_pipe
{

DealMissingCards::DealMissingCards(protocol::entity::MessageSender&     command_sender,
                                   std::vector<protocol::entity::Card>& deck) :
m_message_sender{command_sender},
m_deck{deck}
{
}

void DealMissingCards::run(Room::RoundContext& context)
{
    if (m_deck.empty())
        return;

    auto& player       = context.player;
    auto& player_cards = player.cards;

    assert(player_cards.size() < protocol::entity::kMaxCardsPerPlayer && "Player cards can not be max");

    auto card = m_deck.back();

    player_cards.push_back(card);
    m_deck.pop_back();

    protocol::entity::client::request::DealMissingCard request;
    request.card = card;

    m_message_sender.send(std::move(request), player.connection);
}

} // namespace rps::domain::model::round_pipe
