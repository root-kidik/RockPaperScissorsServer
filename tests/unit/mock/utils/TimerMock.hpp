#pragma once

#include <gmock/gmock.h>

#include <domain/interface/Timer.hpp>

using namespace rps;

class TimerMock final : public domain::interface::Timer
{
public:
    MOCK_METHOD(void, start, (std::chrono::milliseconds timeout, std::function<void()> callback, bool fire_once), (override));
    MOCK_METHOD(void, stop, (), (override));
};
