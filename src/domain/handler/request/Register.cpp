#include <sstream>

#include <domain/handler/request/Register.hpp>
#include <domain/interface/UserStorage.hpp>

namespace rps::domain::handler::request
{

Register::Register(interface::UserStorage& user_storage) : m_user_storage{user_storage}
{
}

Register::Response Register::handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection)
{
    Response response;

    if (request.user_nickname.empty())
        return response;

    if (auto uuid = m_user_storage.try_add_user(request.user_nickname))
        response.user_uuid = uuid.value();

    return response;
}

} // namespace rps::domain::handler::request
