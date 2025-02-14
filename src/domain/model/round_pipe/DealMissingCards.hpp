#pragma once

#include <domain/model/Room.hpp>

namespace rps::domain::model::round_pipe
{

class DealMissingCards : public Room::RoundPipeline::Pipe
{
public:
    DealMissingCards(protocol::entity::MessageSender& command_sender);

    void run(Room::RoundContext& context);

private:
    protocol::entity::MessageSender& m_message_sender;
};

} // namespace rps::domain::model::round_pipe
