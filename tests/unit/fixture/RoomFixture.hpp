#include <mock/client/UserClientMock.hpp>

#include <domain/Room.hpp>

class RoomFixture : public testing::Test
{
public:
    entity::Uuid room_uuid      = "1234";
    std::string  owner_nickname = "admin";
    entity::Uuid owner_uuid     = "5678";

    Room room{room_uuid, owner_uuid};
};
