#include <mock/client/UserClientMock.hpp>
#include <mock/storage/UserStorageMock.hpp>

#include <domain/command/RegisterCommand.hpp>

class RegisterCommandFixture : public testing::Test
{
public:
    UserStorageMock                 user_storage;
    std::shared_ptr<UserClientMock> user_client = std::make_shared<UserClientMock>();
    command::RegisterCommand        register_command{user_storage};
};
