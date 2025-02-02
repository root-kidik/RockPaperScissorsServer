#pragma once

#include <string>

namespace rps::domain::interface
{

class UserClient
{
public:
    virtual ~UserClient() = default;

    virtual void send(const std::string& data) = 0;
};

} // namespace rps::domain::interface
