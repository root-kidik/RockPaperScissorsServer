#include <infrastructure/utils/QtTimer.hpp>

namespace rps::infrastructure::utils
{

void QtTimer::start(std::chrono::milliseconds timeout, std::function<void()> callback, bool fire_once)
{
    timer.setSingleShot(fire_once);
    timer.start(timeout);

    QObject::connect(&timer, &QTimer::timeout, [&callback]() { callback(); });
}

void QtTimer::stop()
{
    timer.stop();
}

} // namespace rps::infrastructure::utils
