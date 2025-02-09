#pragma once

#include <domain/model/Room.hpp>

namespace rps::domain::model::round_pipe
{

class ForceNominatePlayerCard : public Room::RoundPipeline::Pipe
{
public:
    ForceNominatePlayerCard(protocol::entity::MessageSender& command_sender);

    // assert(!player.cards.empty() && "Player must have cards");
    void run(Room::RoundContext& context);

private:
    protocol::entity::MessageSender& m_command_sender;
};

} // namespace rps::domain::model::round_pipe
