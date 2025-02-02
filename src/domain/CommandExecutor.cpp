#include <cassert>

#include <domain/CommandExecutor.hpp>
#include <domain/interface/Command.hpp>

namespace rps::domain
{

void CommandExecutor::execute_command(entity::CommandType command_type, const std::string& data, interface::UserClient& user_client)
{
    auto it = m_commands.find(command_type);

    assert(it != m_commands.end() && "Not setted command to execute this command_type");

    it->second.execute(data, user_client);
}

void CommandExecutor::register_command(entity::CommandType command_type, interface::Command& command)
{
    assert(m_commands.find(command_type) == m_commands.end() && "Already setted command to execute this command_type");

    m_commands.emplace(command_type, command);
}

} // namespace rps::domain
