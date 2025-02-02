#pragma once

#include <string>

namespace rps::domain::interface
{

class IUUIDGenerator
{
public:
    virtual ~IUUIDGenerator() = default;

    virtual std::string generate() const = 0;
};

} // namespace rps::domain::interface
