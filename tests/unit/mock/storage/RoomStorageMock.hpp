#pragma once

#include <gmock/gmock.h>

#include <domain/interface/RoomStorage.hpp>

using namespace rps;

class RoomStorageMock final : public domain::interface::RoomStorage
{
public:
    MOCK_METHOD(bool, try_add_room, (const std::string& name, const std::string& owner_uuid), (override));
    MOCK_METHOD(std::optional<std::reference_wrapper<domain::entity::Room>>,
                try_find_room,
                (const std::string& name),
                (override));
};
