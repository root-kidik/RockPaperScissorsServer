#pragma once

#include <domain/model/Room.hpp>

namespace rps::domain::model::round_pipe
{

class ComputePlayerWinnerPipe : public Room::RoundPipeline::Pipe
{
public:
    ComputePlayerWinnerPipe(protocol::entity::CommandSender& command_sender);

    // assert(player.nominated_card && "player must have nominated card");
    void run(Room::RoundContext& player);

private:
    protocol::entity::CommandSender& m_command_sender;
};

} // namespace rps::domain::model::round_pipe
