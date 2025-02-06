#pragma once

#include <domain/model/Room.hpp>

namespace rps::domain::model::round_pipe
{

class DealMissingCardsPipe : public Room::RoundPipeline::Pipe
{
public:
    DealMissingCardsPipe(protocol::entity::CommandSender& command_sender, std::vector<protocol::entity::Card>& deck);

    void run(Room::RoundContext& context);

private:
    protocol::entity::CommandSender&     m_command_sender;
    std::vector<protocol::entity::Card>& m_deck;
};

} // namespace rps::domain::model::round_pipe
