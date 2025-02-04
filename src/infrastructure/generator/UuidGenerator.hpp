#pragma once

#include <domain/interface/UuidGenerator.hpp>

namespace rps::infrastructure::generator
{

class UuidGenerator final : public domain::interface::UuidGenerator
{
public:
    domain::entity::Uuid generate() const;
};

} // namespace rps::infrastructure::generator
