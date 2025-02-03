#pragma once

#include <gmock/gmock.h>

#include <domain/interface/UserStorage.hpp>

using namespace rps;

class UserStorageMock final : public domain::interface::UserStorage
{
public:
    MOCK_METHOD(std::optional<domain::entity::Uuid>,
                try_add_user,
                (const std::string& nickname, const std::shared_ptr<domain::interface::UserConnection>& connection),
                (override));
    MOCK_METHOD(std::optional<domain::entity::Uuid>, try_find_user_uuid, (const std::string& nickname), (override, const));
    MOCK_METHOD(std::optional<std::string>, try_find_user_nickname, (const domain::entity::Uuid& uuid), (override, const));

    MOCK_METHOD(std::optional<std::reference_wrapper<const domain::entity::User>>,
                try_find_user,
                (const domain::entity::Uuid& uuid),
                (override, const));
};
