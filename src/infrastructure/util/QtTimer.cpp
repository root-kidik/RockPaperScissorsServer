#include <infrastructure/util/QtTimer.hpp>

namespace rps::infrastructure::util
{

void QtTimer::start(std::chrono::milliseconds timeout, std::function<void()> callback, bool fire_once)
{
    callback();

    timer.setSingleShot(fire_once);
    timer.start(timeout);

    QObject::connect(&timer, &QTimer::timeout, [cb = std::move(callback)]() { cb(); });
}

void QtTimer::stop()
{
    timer.stop();
}

} // namespace rps::infrastructure::util
