#pragma once

#include <RockPaperScissorsProtocol/interface/server/handler/request/Register.hpp>

namespace rps::domain::interface
{
class UserStorage;
}

namespace rps::domain::handler
{

class Register final : public protocol::interface::server::handler::request::Register
{
public:
    Register(interface::UserStorage& user_storage);

    Response handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    interface::UserStorage& m_user_storage;
};

} // namespace rps::domain::handler
