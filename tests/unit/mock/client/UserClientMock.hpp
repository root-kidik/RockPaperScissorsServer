#pragma once

#include <gmock/gmock.h>

#include <domain/interface/UserClient.hpp>

using namespace rps::domain;

class UserClientMock final : public interface::UserClient
{
public:
    MOCK_METHOD(bool, is_connected, (), (override, const));
    MOCK_METHOD(void, send, (const std::string& data), (override));
};
