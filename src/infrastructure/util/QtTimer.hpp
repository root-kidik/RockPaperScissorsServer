#pragma once

#include <QTimer>

#include <domain/interface/Timer.hpp>

namespace rps::infrastructure::util
{

class QtTimer final : public domain::interface::Timer
{
public:
    void start(std::chrono::milliseconds timeout, std::function<void()> callback, bool fire_once);
    void stop();

private:
    QTimer timer;
};

} // namespace rps::infrastructure::utils
