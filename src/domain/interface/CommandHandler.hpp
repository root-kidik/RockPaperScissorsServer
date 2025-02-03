#pragma once

#include <memory>
#include <string>

namespace rps::domain::interface
{

class UserConnection;

class CommandHandler
{
public:
    virtual ~CommandHandler() = default;

    virtual void execute(const std::string& data, const std::shared_ptr<UserConnection>& user_connection) = 0;
};

} // namespace rps::domain::interface
