#pragma once

#include <cstdint>

namespace rps::domain::entity
{

enum class Card : std::uint32_t
{
    Begin, // just for min value
    Rock,
    Paper,
    Scissors,
    End // just for max value
};

} // namespace rps::domain::entity
