#pragma once

#include <functional>
#include <string>
#include <unordered_map>

#include <domain/entity/CommandType.hpp>

namespace rps::domain::interface
{
class Command;
class UserClient;
} // namespace rps::domain::interface

namespace rps::domain
{

class CommandExecutor
{
public:
    void execute_command(entity::CommandType command_type, const std::string& data, interface::UserClient& user_client);
    void register_command(entity::CommandType command_type, interface::Command& command);

private:
    std::unordered_map<entity::CommandType, interface::Command&> m_commands;
};

} // namespace rps::domain
