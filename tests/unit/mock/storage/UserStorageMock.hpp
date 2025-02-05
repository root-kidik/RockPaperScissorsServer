#pragma once

#include <gmock/gmock.h>

#include <domain/interface/UserStorage.hpp>

using namespace rps;

class UserStorageMock final : public domain::interface::UserStorage
{
public:
    MOCK_METHOD(std::optional<domain::entity::Uuid>, try_add_user, (const std::string& nickname), (override));
    MOCK_METHOD(std::optional<domain::entity::Uuid>, try_find_user_uuid, (const std::string& nickname), (override, const));
    MOCK_METHOD(std::optional<std::string>, try_find_user_nickname, (const domain::entity::Uuid& uuid), (override, const));
    MOCK_METHOD(std::optional<std::reference_wrapper<domain::entity::User>>,
                try_find_user,
                (const domain::entity::Uuid& uuid),
                (override));
};
