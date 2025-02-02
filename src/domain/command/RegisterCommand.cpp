#include <sstream>

#include <domain/command/RegisterCommand.hpp>
#include <domain/interface/UserClient.hpp>
#include <domain/interface/UserStorage.hpp>

namespace rps::domain::command
{

RegisterCommand::RegisterCommand(interface::UserStorage& user_storage) : m_user_storage{user_storage}
{
}

void RegisterCommand::execute(const std::string& data, interface::UserClient& user_client)
{
    std::istringstream iss{data};

    std::string nickname;

    iss >> nickname;

    if (auto uuid = m_user_storage.try_add_user(nickname))
        user_client.send(uuid.value());
    else
        user_client.send("Error");
}

} // namespace rps::domain::command
