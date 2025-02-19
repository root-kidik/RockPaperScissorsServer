#include <cassert>

#include <RockPaperScissorsProtocol/entity/client/request/RoundInfo.hpp>

#include <domain/model/round_pipe/ComputePlayerWinner.hpp>

namespace rps::domain::model::round_pipe
{

ComputePlayerWinner::ComputePlayerWinner(protocol::entity::MessageSender& command_sender) :
m_message_sender{command_sender}
{
}

void ComputePlayerWinner::run(Room::RoundContext& context)
{
    bool is_rock_raised{};
    bool is_paper_raised{};
    bool is_scissors_raised{};

    std::array<protocol::entity::Card, protocol::entity::kMaxPlayersPerRoom> raised_cards;
    std::uint8_t                                                             i{};

    for (auto& player_ref : context.players)
    {
        assert(player_ref.get().nominated_card && "player must have nominated card");

        auto card         = player_ref.get().nominated_card.value();
        raised_cards[i++] = card;

        if (card == protocol::entity::Card::Rock)
            is_rock_raised = true;
        else if (card == protocol::entity::Card::Paper)
            is_paper_raised = true;
        else if (card == protocol::entity::Card::Scissors)
            is_scissors_raised = true;
        else
            assert(false && "Raised some strange card");
    }

    while (i < protocol::entity::kMaxPlayersPerRoom)
        raised_cards[i++] = protocol::entity::Card::Backface;

    bool is_all_losed       = is_rock_raised && is_paper_raised && is_scissors_raised;
    bool is_paper_winned    = is_rock_raised && is_paper_raised;
    bool is_rock_winned     = is_rock_raised && is_scissors_raised;
    bool is_scissors_winned = is_scissors_raised && is_paper_raised;

    for (auto& player_ref : context.players)
    {
        auto& player = player_ref.get();

        assert(player.nominated_card && "player must have nominated card");

        auto card = player.nominated_card.value();

        protocol::entity::client::request::RoundInfo request;

        if (is_all_losed)
            request.is_winned = false;
        else if (is_paper_winned && card == protocol::entity::Card::Paper ||
                 is_rock_winned && card == protocol::entity::Card::Rock ||
                 is_scissors_winned && card == protocol::entity::Card::Scissors)
            request.is_winned = true;
        else
            request.is_winned = false;

        if (request.is_winned)
            player.wins_count++;

        request.raised_cards = raised_cards;

        m_message_sender.send(std::move(request), player.connection);

        player.nominated_card.reset();
    }
}

} // namespace rps::domain::model::round_pipe
