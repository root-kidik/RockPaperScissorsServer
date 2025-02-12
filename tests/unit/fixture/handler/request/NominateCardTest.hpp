#include <mock/client/ConnectionMock.hpp>
#include <mock/storage/RoomStorageMock.hpp>

#include <domain/handler/request/NominateCard.hpp>

class NominateCardTest : public testing::Test
{
public:
    RoomStorageMock                        room_storage;
    std::shared_ptr<ConnectionMock>        connection = std::make_shared<ConnectionMock>();
    domain::handler::request::NominateCard nominate_card_command_handler{room_storage};
};
