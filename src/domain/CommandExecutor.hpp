#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include <domain/entity/ServerCommandType.hpp>

namespace rps::domain::interface
{
class Command;
class UserConnection;
} // namespace rps::domain::interface

namespace rps::domain
{

class CommandExecutor
{
public:
    void execute_command(entity::ServerCommandType                     command_type,
                         const std::string&                            data,
                         const std::shared_ptr<interface::UserConnection>& user_client);
    void register_command(entity::ServerCommandType command_type, interface::Command& command);

private:
    std::unordered_map<entity::ServerCommandType, interface::Command&> m_commands;
};

} // namespace rps::domain
