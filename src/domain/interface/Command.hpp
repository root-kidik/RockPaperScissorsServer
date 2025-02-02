#pragma once

#include <string>

namespace rps::domain::interface
{

class UserClient;

class Command
{
public:
    virtual ~Command() = default;

    virtual void execute(const std::string& data, UserClient& user_client) = 0;
};

} // namespace rps::domain::interface
