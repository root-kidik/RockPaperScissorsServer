#pragma once

#include <functional>
#include <optional>

#include <domain/entity/Uuid.hpp>
#include <domain/interface/Room.hpp>

namespace rps::domain::interface
{

class RoomStorage
{
public:
    virtual ~RoomStorage() = default;

    virtual bool try_add_room(const std::string& name, const entity::Uuid& owner_uuid)         = 0;
    virtual std::optional<std::reference_wrapper<Room>> try_find_room(const std::string& name) = 0;
};

} // namespace rps::domain::interface
