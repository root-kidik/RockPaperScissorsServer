#include <fixture/RoomFixture.hpp>
#include <mock/client/UserClientMock.hpp>

#include <domain/entity/ClientCommandType.hpp>

#include <gtest/gtest.h>

using testing::Return;

TEST_F(RoomFixture, owner_is_added)
{
    std::shared_ptr<UserClientMock> owner_client = std::make_shared<UserClientMock>();

    EXPECT_TRUE(room.try_add_player(owner_uuid, owner_nickname, owner_client));
}

TEST_F(RoomFixture, owner_is_added_then_notifed_after_new_user_added)
{
    std::shared_ptr<UserClientMock> owner_client = std::make_shared<UserClientMock>();

    EXPECT_TRUE(room.try_add_player(owner_uuid, owner_nickname, owner_client));

    entity::Uuid                    new_clint_uuid      = "9999";
    std::string                     new_client_nickname = "new_client";
    std::shared_ptr<UserClientMock> new_client          = std::make_shared<UserClientMock>();

    std::string revied_owner_message = std::to_string(static_cast<std::uint32_t>(entity::ClientCommandType::AddNewPlayer)) +
                                       ' ' + new_client_nickname;

    EXPECT_CALL(*owner_client, send(revied_owner_message)).WillOnce(Return());

    EXPECT_TRUE(room.try_add_player(new_clint_uuid, new_client_nickname, new_client));
}

TEST_F(RoomFixture, player_number_7_is_not_added)
{
    std::shared_ptr<UserClientMock> owner_client = std::make_shared<UserClientMock>();

    EXPECT_TRUE(room.try_add_player(owner_uuid, owner_nickname, owner_client));

    std::vector<std::shared_ptr<UserClientMock>> m_players;
    for (std::size_t i = 0; i < 5; i++)
    {
        entity::Uuid                    new_clint_uuid      = std::to_string(i);
        std::string                     new_client_nickname = std::to_string(i);
        std::shared_ptr<UserClientMock> new_client          = std::make_shared<UserClientMock>();

        std::string recieved_message = std::to_string(static_cast<std::uint32_t>(entity::ClientCommandType::AddNewPlayer)) +
                                       ' ' + new_client_nickname;

        EXPECT_CALL(*owner_client, send(recieved_message)).WillOnce(Return());

        for (auto player : m_players)
            EXPECT_CALL(*player, send(recieved_message)).WillOnce(Return());

        EXPECT_TRUE(room.try_add_player(new_clint_uuid, new_client_nickname, new_client));

        m_players.push_back(new_client);
    }

    EXPECT_FALSE(room.try_add_player("new_clint_uuid", "new_client_nickname", std::make_shared<UserClientMock>()));
}

TEST_F(RoomFixture, player_numer_6_is_not_added_because_owner_is_not_yes_added_and_owner_is_added)
{
    std::vector<std::shared_ptr<UserClientMock>> m_players;
    for (std::size_t i = 0; i < 5; i++)
    {
        entity::Uuid                    new_clint_uuid      = std::to_string(i);
        std::string                     new_client_nickname = std::to_string(i);
        std::shared_ptr<UserClientMock> new_client          = std::make_shared<UserClientMock>();

        std::string recieved_message = std::to_string(static_cast<std::uint32_t>(entity::ClientCommandType::AddNewPlayer)) +
                                       ' ' + new_client_nickname;

        for (auto player : m_players)
            EXPECT_CALL(*player, send(recieved_message)).WillOnce(Return());

        EXPECT_TRUE(room.try_add_player(new_clint_uuid, new_client_nickname, new_client));

        m_players.push_back(new_client);
    }

    EXPECT_FALSE(room.try_add_player("new_clint_uuid", "new_client_nickname", std::make_shared<UserClientMock>()));

    std::shared_ptr<UserClientMock> owner_client = std::make_shared<UserClientMock>();

    std::string recieved_message = std::to_string(static_cast<std::uint32_t>(entity::ClientCommandType::AddNewPlayer)) +
                                   ' ' + owner_nickname;
                                   
    for (auto player : m_players)
        EXPECT_CALL(*player, send(recieved_message)).WillOnce(Return());

    EXPECT_TRUE(room.try_add_player(owner_uuid, owner_nickname, owner_client));
}
