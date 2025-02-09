#pragma once

#include <domain/model/Room.hpp>

namespace rps::domain::model::round_pipe
{

class ComputePlayerWinner : public Room::RoundPipeline::Pipe
{
public:
    ComputePlayerWinner(protocol::entity::MessageSender& command_sender);

    // assert(player.nominated_card && "player must have nominated card");
    void run(Room::RoundContext& player);

private:
    protocol::entity::MessageSender& m_command_sender;
};

} // namespace rps::domain::model::round_pipe
