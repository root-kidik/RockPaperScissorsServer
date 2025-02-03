#include <fixture/command/RegisterCommandFixture.hpp>

#include <gtest/gtest.h>

using testing::Return;

TEST_F(RegisterCommandFixture, name_is_unqiue)
{
    std::string  name = "user";
    domain::entity::Uuid uuid = "1234";

    EXPECT_CALL(user_storage, try_add_user(name, std::static_pointer_cast<domain::interface::UserConnection>(user_connection)))
        .WillOnce(Return(uuid));
    EXPECT_CALL(*user_connection, send(uuid)).WillOnce(Return());

    register_command.execute(name, user_connection);
}

TEST_F(RegisterCommandFixture, name_is_empty)
{
    std::string name = " ";

    EXPECT_CALL(*user_connection, send("Error")).WillOnce(Return());

    register_command.execute(name, user_connection);
}

TEST_F(RegisterCommandFixture, name_already_exist)
{
    std::string name = "user";

    EXPECT_CALL(user_storage, try_add_user(name, std::static_pointer_cast<domain::interface::UserConnection>(user_connection)))
        .WillOnce(Return(std::nullopt));
    EXPECT_CALL(*user_connection, send("Error")).WillOnce(Return());

    register_command.execute(name, user_connection);
}
