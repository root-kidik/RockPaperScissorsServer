#include <sstream>

#include <domain/command/RegisterCommand.hpp>
#include <domain/interface/UserConnection.hpp>
#include <domain/interface/UserStorage.hpp>

namespace rps::domain::command
{

RegisterCommand::RegisterCommand(interface::UserStorage& user_storage) : m_user_storage{user_storage}
{
}

void RegisterCommand::execute(const std::string& data, const std::shared_ptr<interface::UserConnection>& user_connection)
{
    std::istringstream iss{data};

    std::string nickname;

    iss >> nickname;

    if (nickname.empty())
    {
        user_connection->send("Error");
        return;
    }

    if (auto uuid = m_user_storage.try_add_user(nickname, user_connection))
        user_connection->send(uuid.value());
    else
        user_connection->send("Error");
}

} // namespace rps::domain::command
