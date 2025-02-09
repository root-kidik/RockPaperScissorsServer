#pragma once

#include <domain/model/Room.hpp>

namespace rps::domain::model::round_pipe
{

class DealMissingCards : public Room::RoundPipeline::Pipe
{
public:
    DealMissingCards(protocol::entity::MessageSender& command_sender, std::vector<protocol::entity::Card>& deck);

    void run(Room::RoundContext& context);

private:
    protocol::entity::MessageSender&     m_command_sender;
    std::vector<protocol::entity::Card>& m_deck;
};

} // namespace rps::domain::model::round_pipe
