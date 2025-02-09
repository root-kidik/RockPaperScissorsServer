#include <memory>
#include <mock/client/ConnectionMock.hpp>
#include <mock/util/TimerMock.hpp>

#include <domain/model/Room.hpp>

class RoomFixture : public testing::Test
{
public:
    std::string                     name       = "room_name";
    domain::entity::Uuid            owner_uuid = "owner_uuid";
    std::shared_ptr<TimerMock>      timer      = std::make_shared<TimerMock>();
    protocol::entity::MessageSender command_sender;
    std::shared_ptr<ConnectionMock> connection = std::make_shared<ConnectionMock>();
    domain::model::Room             room{name, owner_uuid, timer, command_sender};
};
