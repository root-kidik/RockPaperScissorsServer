#include <mock/client/ConnectionMock.hpp>
#include <mock/storage/RoomStorageMock.hpp>

#include <domain/handler/NominateCardCommandHandler.hpp>

class NominateCardCommandHandlerFixture : public testing::Test
{
public:
    RoomStorageMock                             room_storage;
    std::shared_ptr<ConnectionMock>             connection = std::make_shared<ConnectionMock>();
    domain::handler::NominateCardCommandHandler nominate_card_command_handler{room_storage};
};
