#pragma once

#include <cstdint>

namespace rps::domain::entity
{

enum class ClientCommandType : std::uint32_t
{
    Begin,        // just for min value
    AddNewPlayer, // input: std::string name | output: -
    End           // just for max value
};

} // namespace rps::domain::entity
