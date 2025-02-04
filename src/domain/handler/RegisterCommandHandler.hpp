#pragma once

#include <RockPaperScissorsProtocol/interface/CommandHandler.hpp>

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

    protocol::entity::RegisterResponse handle(protocol::entity::RegisterRequest&& request,
                                              const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    interface::UserStorage& m_user_storage;
};

} // namespace rps::domain::handler
