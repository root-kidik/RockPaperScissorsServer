#include <mock/client/ConnectionMock.hpp>
#include <mock/storage/UserStorageMock.hpp>

#include <domain/handler/request/Register.hpp>

class RegisterTest : public testing::Test
{
public:
    UserStorageMock                    user_storage;
    std::shared_ptr<ConnectionMock>    connection = std::make_shared<ConnectionMock>();
    domain::handler::request::Register register_command_handler{user_storage};
};
