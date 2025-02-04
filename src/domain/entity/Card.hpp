#pragma once

#include <cstdint>

namespace rps::domain::entity
{

using CardRepresentation = std::uint32_t; 

enum class Card : CardRepresentation
{
    Begin, // just for min value
    Rock,
    Paper,
    Scissors,
    End // just for max value
};

} // namespace rps::domain::entity
