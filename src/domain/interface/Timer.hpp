#pragma once

#include <chrono>
#include <functional>

namespace rps::domain::interface
{

class Timer
{
public:
    virtual ~Timer() = default;

    virtual void start(std::chrono::milliseconds timeout, std::function<void()> callback, bool fire_once) = 0;
    virtual void stop()                                                                                   = 0;
};

} // namespace rps::domain::interface
