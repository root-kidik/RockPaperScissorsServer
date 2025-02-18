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
    for (auto& player_ref : context.players)
    {
        auto& player = player_ref.get();

        assert(player.nominated_card && "Card must be nominated");

        auto card = player.nominated_card.value();

        auto it = std::find(player.cards.begin(), player.cards.end(), card);

        assert(it != player.cards.end() && "Nominated card must be exists");

        player.cards.erase(it);

        protocol::entity::client::request::CardRaised request;
        request.card = player.nominated_card.value();

        m_message_sender.send(std::move(request), player.connection);
    }
}

} // namespace rps::domain::model::round_pipe
