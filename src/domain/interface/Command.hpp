#pragma once

#include <memory>
#include <string>

namespace rps::domain::interface
{

class UserConnection;

class Command
{
public:
    virtual ~Command() = default;

    virtual void execute(const std::string& data, const std::shared_ptr<UserConnection>& user_client) = 0;
};

} // namespace rps::domain::interface
