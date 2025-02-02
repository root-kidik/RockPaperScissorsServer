#pragma once

#include <unordered_map>

#include <domain/interface/UserStorage.hpp>

namespace rps::domain::interface
{
class UuidGenerator;
}

namespace rps::infrastructure::storage
{

class MemoryUserStorage final : public domain::interface::UserStorage
{
public:
    MemoryUserStorage(const domain::interface::UuidGenerator& uuid_generator);

    std::optional<domain::entity::Uuid> try_add_user(const std::string& nickname) override;

    std::optional<domain::entity::Uuid> try_find_user_uuid(const std::string& nickname) const override;

private:
    const domain::interface::UuidGenerator& m_uuid_generator;

    std::unordered_map<std::string, domain::entity::Uuid> m_users;
};

} // namespace rps::infrastructure::storage
