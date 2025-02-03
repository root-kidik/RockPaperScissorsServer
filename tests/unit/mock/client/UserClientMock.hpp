#pragma once

#include <gmock/gmock.h>

#include <RockPaperScissorsProtocol/interface/Connection.hpp>

using namespace rps;

class UserClientMock final : public protocol::interface::Connection
{
public:
    MOCK_METHOD(bool, is_connected, (), (override, const));
    MOCK_METHOD(void, send, (const std::string& data), (override));
};
