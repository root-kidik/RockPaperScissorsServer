#include <QUuid>

#include <infrastructure/generator/UUIDGenerator.hpp>

namespace rps::infrastructure::generator
{

std::string UUIDGenerator::generate() const
{
    return QUuid::createUuid().toString().toStdString();
}

} // namespace rps::infrastructure::generator
