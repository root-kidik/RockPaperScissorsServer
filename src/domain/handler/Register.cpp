#include <sstream>

#include <domain/handler/Register.hpp>
#include <domain/interface/UserStorage.hpp>

namespace rps::domain::handler
{

Register::Register(interface::UserStorage& user_storage) : m_user_storage{user_storage}
{
}

protocol::entity::server::response::Register Register::handle(protocol::entity::server::request::Register&& request,
                                                              const std::shared_ptr<protocol::interface::Connection>& connection)
{
    protocol::entity::server::response::Register response;

    if (request.user_nickname.empty())
        return response;

    if (auto uuid = m_user_storage.try_add_user(request.user_nickname))
        response.user_uuid = uuid.value();

    return response;
}

} // namespace rps::domain::handler
