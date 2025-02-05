#include <sstream>

#include <domain/handler/RegisterCommandHandler.hpp>
#include <domain/interface/UserStorage.hpp>

#include <RockPaperScissorsProtocol/utils/Utils.hpp>

namespace rps::domain::handler
{

RegisterCommandHandler::RegisterCommandHandler(interface::UserStorage& user_storage) : m_user_storage{user_storage}
{
}

protocol::entity::server::RegisterResponse RegisterCommandHandler::handle(
    protocol::entity::server::RegisterRequest&&             request,
    const std::shared_ptr<protocol::interface::Connection>& connection)
{
    protocol::entity::server::RegisterResponse response;

    if (request.user_nickname.empty())
        return response;

    if (auto uuid = m_user_storage.try_add_user(request.user_nickname))
        response.user_uuid = uuid.value();

    return response;
}

} // namespace rps::domain::handler
