#pragma once

#include <cstdint>

namespace rps::domain::entity
{

enum class CommandType : std::uint32_t
{
    Begin,         // just for min value
    Register,      // input: std::string nickname                        | output: std::string uuid || "Error"
    CreateRoom,    // input: std::string name std::string uuid           | output: std::string uuid || "Error"
    ConnectToRoom, // input: std::string user_uuid std::string room_name | output: std::string "Ok" || "Error"
    End            // just for max value
};

} // namespace rps::domain::entity
