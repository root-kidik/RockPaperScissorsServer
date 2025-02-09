#pragma once

#include <domain/model/Room.hpp>

namespace rps::domain::model::round_pipe
{

class ForceNominatePlayerCard : public Room::RoundPipeline::Pipe
{
public:
    ForceNominatePlayerCard(protocol::entity::CommandSender& command_sender);

    // assert(!player.cards.empty() && "Player must have cards");
    void run(Room::RoundContext& context);

private:
    protocol::entity::CommandSender& m_command_sender;
};

} // namespace rps::domain::model::round_pipe
