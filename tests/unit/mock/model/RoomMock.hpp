#pragma once

#include <gmock/gmock.h>

#include <domain/interface/Room.hpp>

using namespace rps;

class RoomMock final : public domain::interface::Room
{
public:
    MOCK_METHOD(bool,
                try_add_user,
                (const domain::entity::Uuid&                                     user_uuid,
                 const std::string&                                      user_nickname,
                 const std::shared_ptr<protocol::interface::Connection>& connection),
                (override));
    MOCK_METHOD(bool, try_start_game, (const domain::entity::Uuid& user_uuid), (override));
};
