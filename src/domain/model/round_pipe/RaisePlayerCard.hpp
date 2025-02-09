#pragma once

#include <domain/model/Room.hpp>

namespace rps::domain::model::round_pipe
{

class RaisePlayerCard : public Room::RoundPipeline::Pipe
{
public:
    RaisePlayerCard(protocol::entity::CommandSender& command_sender);

    // assert(player.nominated_card && "Card must be nominated");
    // assert(m_play_table.find(player_uuid) == m_play_table.end() && "Play table must not have yet raised by player card");
    // assert(it != player.cards.end() && "Nominated card must be exists");
    void run(Room::RoundContext& player);

private:
    protocol::entity::CommandSender& m_command_sender;
};

} // namespace rps::domain::model::round_pipe
