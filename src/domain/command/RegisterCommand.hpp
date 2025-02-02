#pragma once

#include <domain/interface/Command.hpp>

namespace rps::domain::interface
{
class UserStorage;
}

namespace rps::domain::command
{

class RegisterCommand final : public interface::Command
{
public:
    RegisterCommand(interface::UserStorage& user_storage);

    void execute(const std::string& data, const std::shared_ptr<interface::UserClient>& user_client) override;

private:
    interface::UserStorage& m_user_storage;
};

} // namespace rps::domain::command
