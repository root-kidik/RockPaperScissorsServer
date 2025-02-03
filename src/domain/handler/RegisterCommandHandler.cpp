#include <sstream>

#include <domain/handler/RegisterCommandHandler.hpp>
#include <domain/interface/UserStorage.hpp>

#include <RockPaperScissorsProtocol/entity/server/RegisterCommand.hpp>
#include <RockPaperScissorsProtocol/utils/Utils.hpp>

namespace rps::domain::handler
{

RegisterCommandHandler::RegisterCommandHandler(interface::UserStorage& user_storage) : m_user_storage{user_storage}
{
}

void RegisterCommandHandler::execute(const std::string& data, const std::shared_ptr<protocol::interface::Connection>& connection)
{
    auto command = protocol::utils::deserialize<protocol::entity::RegisterCommand>(data);

    if (command.user_nickname.empty())
    {
        connection->send("Error");
        return;
    }

    if (auto uuid = m_user_storage.try_add_user(command.user_nickname, connection))
        connection->send(uuid.value());
    else
        connection->send("Error");
}

} // namespace rps::domain::handler
