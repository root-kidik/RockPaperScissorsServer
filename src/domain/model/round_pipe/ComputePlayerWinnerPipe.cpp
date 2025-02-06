#include <algorithm>
#include <cassert>

#include <domain/model/round_pipe/ComputePlayerWinnerPipe.hpp>

#include <RockPaperScissorsProtocol/entity/client/request/RoundInfoRequest.hpp>

namespace rps::domain::model::round_pipe
{

ComputePlayerWinnerPipe::ComputePlayerWinnerPipe(protocol::entity::CommandSender& command_sender) :
m_command_sender{command_sender}
{
}

void ComputePlayerWinnerPipe::run(Room::RoundContext& context)
{
    auto& [player, player_uuid, is_rock_raised, is_paper_raised, is_scissors_raised] = context;

    protocol::entity::client::RoundInfoRequest request;

    assert(player.nominated_card && "player must have nominated card");

    auto card = player.nominated_card.value();

    bool is_all_losed       = is_rock_raised && is_paper_raised && is_scissors_raised;
    bool is_paper_winned    = is_rock_raised && is_paper_raised;
    bool is_rock_winned     = is_rock_raised && is_scissors_raised;
    bool is_scissors_winned = is_scissors_raised && is_paper_raised;

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
}

} // namespace rps::domain::model::round_pipe
