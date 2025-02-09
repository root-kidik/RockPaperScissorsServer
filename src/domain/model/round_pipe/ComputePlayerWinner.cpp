#include <algorithm>
#include <cassert>

#include <domain/model/round_pipe/ComputePlayerWinner.hpp>

#include <RockPaperScissorsProtocol/entity/client/request/RoundInfo.hpp>

namespace rps::domain::model::round_pipe
{

ComputePlayerWinner::ComputePlayerWinner(protocol::entity::CommandSender& command_sender) :
m_command_sender{command_sender}
{
}

void ComputePlayerWinner::run(Room::RoundContext& context)
{
    auto& [player, player_uuid, is_rock_raised, is_paper_raised, is_scissors_raised] = context;

    assert(player.nominated_card && "player must have nominated card");

    auto card = player.nominated_card.value();

    bool is_all_losed       = is_rock_raised && is_paper_raised && is_scissors_raised;
    bool is_paper_winned    = is_rock_raised && is_paper_raised;
    bool is_rock_winned     = is_rock_raised && is_scissors_raised;
    bool is_scissors_winned = is_scissors_raised && is_paper_raised;

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

    m_command_sender.send(std::move(request), player.connection);

    player.nominated_card.reset();
}

} // namespace rps::domain::model::round_pipe
