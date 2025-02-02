#pragma once

#include <domain/interface/IUUIDGenerator.hpp>

namespace rps::infrastructure::generator
{

class UUIDGenerator final : public domain::interface::IUUIDGenerator
{
public:
    std::string generate() const;
};

} // namespace rps::infrastructure::generator
