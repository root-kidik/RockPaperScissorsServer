#pragma once

#include <chrono>
#include <cstdint>
#include <memory>
#include <unordered_set>
#include <vector>

#include <domain/entity/Uuid.hpp>
#include <domain/interface/Timer.hpp>

#include <RockPaperScissorsProtocol/interface/Connection.hpp>
#include <RockPaperScissorsProtocol/entity/Card.hpp>

namespace rps::domain::entity
{

struct Room
{
    static constexpr std::uint8_t         kMaxPlayers{6};
    static constexpr std::chrono::seconds kTurnTime{10};

    std::string  name;
    entity::Uuid owner_uuid;

    bool is_game_started{};

    std::shared_ptr<interface::Timer> timer;

    std::unordered_set<entity::Uuid>    players;
    std::vector<protocol::entity::Card> cards;
};

} // namespace rps::domain::entity
