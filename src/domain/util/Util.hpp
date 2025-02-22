#pragma once

#include <algorithm>
#include <chrono>
#include <random>

#include <RockPaperScissorsProtocol/entity/Card.hpp>

namespace rps::domain::util
{

std::vector<protocol::entity::Card> gen_cards()
{
    std::vector<protocol::entity::Card> cards;

    for (auto card : {protocol::entity::Card::Rock, protocol::entity::Card::Paper, protocol::entity::Card::Scissors})
        for (std::size_t i = 0;
             i < protocol::entity::kMaxCardsPerRoom /
                     (static_cast<protocol::entity::CardRepresentation>(protocol::entity::Card::End) - 2);
             i++)
            cards.emplace_back(card);

    cards.emplace_back(static_cast<protocol::entity::Card>(
        std::rand() % (static_cast<protocol::entity::CardRepresentation>(protocol::entity::Card::End) - 2) + 1));

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(cards.begin(), cards.end(), std::default_random_engine{static_cast<std::uint32_t>(seed)});

    return cards;
}

} // namespace rps::domain::util
