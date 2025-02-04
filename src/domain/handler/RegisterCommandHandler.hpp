#pragma once

#include <RockPaperScissorsProtocol/interface/RegisterCommandHandlerBase.hpp>

namespace rps::domain::interface
{
class UserStorage;
}

namespace rps::domain::handler
{

class RegisterCommandHandler final : public protocol::interface::RegisterCommandHandlerBase
{
public:
    RegisterCommandHandler(interface::UserStorage& user_storage);

    protocol::entity::server::RegisterResponse handle(protocol::entity::server::RegisterRequest&& request,
                                                      const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    interface::UserStorage& m_user_storage;
};

} // namespace rps::domain::handler
