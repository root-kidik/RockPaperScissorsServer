#include <fixture/handler/RegisterCommandFixture.hpp>

#include <gtest/gtest.h>

using testing::Return;

TEST_F(RegisterCommandFixture, name_is_empty)
{
    protocol::entity::server::request::Register request;

    auto response = register_command_handler.handle(std::move(request), connection);

    EXPECT_TRUE(response.user_uuid.empty());
}

TEST_F(RegisterCommandFixture, name_already_exist)
{
    protocol::entity::server::request::Register request;
    request.user_nickname = "user";

    EXPECT_CALL(user_storage, try_add_user(request.user_nickname)).WillOnce(Return(std::nullopt));

    auto response = register_command_handler.handle(std::move(request), connection);

    EXPECT_TRUE(response.user_uuid.empty());
}

TEST_F(RegisterCommandFixture, name_is_unqiue)
{
    protocol::entity::server::request::Register request;
    request.user_nickname = "user";

    std::string user_uuid = "1234";

    EXPECT_CALL(user_storage, try_add_user(request.user_nickname)).WillOnce(Return(user_uuid));

    auto response = register_command_handler.handle(std::move(request), connection);

    EXPECT_TRUE(response.user_uuid == user_uuid);
}