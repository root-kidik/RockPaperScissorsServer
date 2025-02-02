#pragma once

#include <string>

namespace rps::domain::interface
{

class UuidGenerator
{
public:
    virtual ~UuidGenerator() = default;

    virtual std::string generate() const = 0;
};

} // namespace rps::domain::interface
