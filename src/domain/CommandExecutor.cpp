#include <cassert>

#include <domain/CommandExecutor.hpp>
#include <domain/interface/Command.hpp>
#include <domain/interface/UserConnection.hpp>

namespace rps::domain
{

void CommandExecutor::execute_command(protocol::entity::ServerCommandType                         command_type,
                                      const std::string&                                data,
                                      const std::shared_ptr<interface::UserConnection>& user_connection)
{
    auto it = m_commands.find(command_type);

    assert(it != m_commands.end() && "Not setted command to execute this command_type");

    it->second.execute(data, user_connection);
}

void CommandExecutor::register_command(protocol::entity::ServerCommandType command_type, interface::Command& command)
{
    assert(m_commands.find(command_type) == m_commands.end() && "Already setted command to execute this command_type");

    m_commands.emplace(command_type, command);
}

} // namespace rps::domain
