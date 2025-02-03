#include <sstream>

#include <domain/handler/RegisterCommandHandler.hpp>
#include <domain/interface/UserConnection.hpp>
#include <domain/interface/UserStorage.hpp>

#include <RockPaperScissorsProtocol/utils/Utils.hpp>
#include <RockPaperScissorsProtocol/entity/server/RegisterCommand.hpp>

namespace rps::domain::handler
{

RegisterCommandHandler::RegisterCommandHandler(interface::UserStorage& user_storage) : m_user_storage{user_storage}
{
}

void RegisterCommandHandler::execute(const std::string& data, const std::shared_ptr<interface::UserConnection>& user_connection)
{
    auto command = protocol::utils::deserialize<protocol::entity::RegisterCommand>(data);

    if (command.user_nickname.empty())
    {
        user_connection->send("Error");
        return;
    }

    if (auto uuid = m_user_storage.try_add_user(command.user_nickname, user_connection))
        user_connection->send(uuid.value());
    else
        user_connection->send("Error");
}

} // namespace rps::domain::handler
