#include <mock/client/ConnectionMock.hpp>
#include <mock/storage/UserStorageMock.hpp>

#include <domain/handler/Register.hpp>

class RegisterCommandFixture : public testing::Test
{
public:
    UserStorageMock                 user_storage;
    std::shared_ptr<ConnectionMock> connection = std::make_shared<ConnectionMock>();
    domain::handler::Register       register_command_handler{user_storage};
};
