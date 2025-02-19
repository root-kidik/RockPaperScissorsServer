#include <cassert>

#include <RockPaperScissorsProtocol/entity/client/request/DealMissingCard.hpp>

#include <domain/model/round_pipe/DealMissingCards.hpp>

namespace rps::domain::model::round_pipe
{

DealMissingCards::DealMissingCards(protocol::entity::MessageSender& command_sender) : m_message_sender{command_sender}
{
}

void DealMissingCards::run(Room::RoundContext& context)
{
    for (auto& player_ref : context.players)
    {
        if (context.cards.empty())
            return;

        auto& player       = player_ref.get();
        auto& player_cards = player.cards;

        assert(player_cards.size() < protocol::entity::kMaxCardsPerPlayer && "Player cards can not be max");

        auto card = context.cards.back();

        player_cards.push_back(card);
        context.cards.pop_back();

        protocol::entity::client::request::DealMissingCard request;
        request.card = card;

        m_message_sender.send(std::move(request), player.connection);
    }
}

} // namespace rps::domain::model::round_pipe
