#pragma once

#include <RockPaperScissorsProtocol/interface/CommandHandler.hpp>

namespace rps::domain::interface
{
class UserStorage;
}

namespace rps::domain::handler
{

class RegisterCommandHandler final : public protocol::interface::CommandHandler
{
public:
    RegisterCommandHandler(interface::UserStorage& user_storage);

    void execute(const std::string& data, const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    interface::UserStorage& m_user_storage;
};

} // namespace rps::domain::handler
