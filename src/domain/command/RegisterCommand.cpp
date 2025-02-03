#include <sstream>

#include <domain/command/RegisterCommand.hpp>
#include <domain/interface/UserConnection.hpp>
#include <domain/interface/UserStorage.hpp>

namespace rps::domain::command
{

RegisterCommand::RegisterCommand(interface::UserStorage& user_storage) : m_user_storage{user_storage}
{
}

void RegisterCommand::execute(const std::string& data, const std::shared_ptr<interface::UserConnection>& user_client)
{
    std::istringstream iss{data};

    std::string nickname;

    iss >> nickname;

    if (nickname.empty())
    {
        user_client->send("Error");
        return;
    }

    if (auto uuid = m_user_storage.try_add_user(nickname))
        user_client->send(uuid.value());
    else
        user_client->send("Error");
}

} // namespace rps::domain::command
