#pragma once

#include <gmock/gmock.h>

#include <domain/interface/UserConnection.hpp>

using namespace rps::domain;

class UserClientMock final : public interface::UserConnection
{
public:
    MOCK_METHOD(bool, is_connected, (), (override, const));
    MOCK_METHOD(void, send, (const std::string& data), (override));
};
