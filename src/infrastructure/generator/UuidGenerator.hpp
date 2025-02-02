#pragma once

#include <domain/interface/UuidGenerator.hpp>

namespace rps::infrastructure::generator
{

class UuidGenerator final : public domain::interface::UuidGenerator
{
public:
    std::string generate() const;
};

} // namespace rps::infrastructure::generator
