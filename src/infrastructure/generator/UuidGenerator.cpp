#include <QUuid>

#include <infrastructure/generator/UuidGenerator.hpp>

namespace rps::infrastructure::generator
{

std::string UuidGenerator::generate() const
{
    return QUuid::createUuid().toString().toStdString();
}

} // namespace rps::infrastructure::generator
