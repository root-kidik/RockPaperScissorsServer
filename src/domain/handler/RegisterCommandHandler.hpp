#pragma once

#include <domain/interface/CommandHandler.hpp>

namespace rps::domain::interface
{
class UserStorage;
}

namespace rps::domain::handler
{

class RegisterCommandHandler final : public interface::CommandHandler
{
public:
    RegisterCommandHandler(interface::UserStorage& user_storage);

    void execute(const std::string& data, const std::shared_ptr<interface::UserConnection>& user_connection) override;

private:
    interface::UserStorage& m_user_storage;
};

} // namespace rps::domain::handler
