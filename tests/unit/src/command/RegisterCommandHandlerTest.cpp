#include <fixture/command/RegisterCommandFixture.hpp>

#include <gtest/gtest.h>

using testing::Return;

TEST_F(RegisterCommandFixture, name_is_unqiue)
{
    protocol::entity::server::RegisterRequest request;
    request.user_nickname = "user";

    std::string user_uuid = "1234";

    EXPECT_CALL(user_storage,
                try_add_user(request.user_nickname, std::static_pointer_cast<protocol::interface::Connection>(connection)))
        .WillOnce(Return(user_uuid));

    auto response = register_command_handler.handle(std::move(request), connection);

    EXPECT_TRUE(response.user_uuid == user_uuid);
}

TEST_F(RegisterCommandFixture, name_is_empty)
{
    protocol::entity::server::RegisterRequest request;
    request.user_nickname = "";

    auto response = register_command_handler.handle(std::move(request), connection);

    EXPECT_TRUE(response.user_uuid.empty());
}

TEST_F(RegisterCommandFixture, name_already_exist)
{
    protocol::entity::server::RegisterRequest request;
    request.user_nickname = "user";

    EXPECT_CALL(user_storage,
                try_add_user(request.user_nickname, std::static_pointer_cast<protocol::interface::Connection>(connection)))
        .WillOnce(Return(std::nullopt));

    register_command_handler.handle(std::move(request), connection);
}
