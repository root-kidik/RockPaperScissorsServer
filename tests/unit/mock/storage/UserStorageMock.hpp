#pragma once

#include <gmock/gmock.h>

#include <domain/interface/UserStorage.hpp>

using namespace rps::domain;

class UserStorageMock final : public interface::UserStorage
{
public:
    MOCK_METHOD(std::optional<entity::Uuid>, try_add_user, (const std::string& nickname), (override));
    MOCK_METHOD(std::optional<entity::Uuid>, try_find_user_uuid, (const std::string& nickname), (override, const));
    MOCK_METHOD(std::optional<std::string>, try_find_user_nickname, (const entity::Uuid& uuid), (override, const));
};
