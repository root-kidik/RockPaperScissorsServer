#pragma once

#include <gmock/gmock.h>

#include <domain/interface/RoomStorage.hpp>

using namespace rps::domain;

class RoomStorageMock final : public interface::RoomStorage
{
public:
    MOCK_METHOD(bool, try_add_room, (const std::string& name, const entity::Uuid& owner_uuid), (override));
    MOCK_METHOD(std::optional<std::reference_wrapper<entity::Room>>, try_find_room, (const std::string& name), (override));
};
