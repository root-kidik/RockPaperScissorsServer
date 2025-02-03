#include <mock/client/UserClientMock.hpp>
#include <mock/storage/UserStorageMock.hpp>

#include <domain/handler/RegisterCommandHandler.hpp>

class RegisterCommandFixture : public testing::Test
{
public:
    UserStorageMock                         user_storage;
    std::shared_ptr<UserClientMock>         user_connection = std::make_shared<UserClientMock>();
    domain::handler::RegisterCommandHandler register_command_handler{user_storage};
};
