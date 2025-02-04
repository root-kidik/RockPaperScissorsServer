#pragma once

#include <domain/entity/Uuid.hpp>

namespace rps::domain::interface
{

class UuidGenerator
{
public:
    virtual ~UuidGenerator() = default;

    virtual entity::Uuid generate() const = 0;
};

} // namespace rps::domain::interface
