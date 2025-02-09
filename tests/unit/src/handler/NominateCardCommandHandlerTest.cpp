#include <fixture/handler/NominateCardCommandHandlerFixture.hpp>
#include <mock/model/RoomMock.hpp>

#include <gtest/gtest.h>

using testing::Return;

TEST_F(NominateCardCommandHandlerFixture, room_name_user_uuid_card_are_empty)
{
    protocol::entity::server::request::NominateCard request;

    auto response = nominate_card_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(NominateCardCommandHandlerFixture, room_name_is_empty)
{
    protocol::entity::server::request::NominateCard request;
    request.user_uuid = "user_uuid";

    auto response = nominate_card_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(NominateCardCommandHandlerFixture, user_uuid_is_empty)
{
    protocol::entity::server::request::NominateCard request;
    request.room_name = "user_room";

    auto response = nominate_card_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(NominateCardCommandHandlerFixture, card_is_empty)
{
    protocol::entity::server::request::NominateCard request;
    request.room_name = "user_room";
    request.user_uuid = "user_uuid";

    auto response = nominate_card_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(NominateCardCommandHandlerFixture, room_name_user_uuid_card_have_value_but_room_not_finded)
{
    protocol::entity::server::request::NominateCard request;
    request.room_name = "user_room";
    request.user_uuid = "user_uuid";
    request.card      = protocol::entity::Card::Rock;

    EXPECT_CALL(room_storage, try_find_room(request.room_name)).WillOnce(Return(std::nullopt));

    auto response = nominate_card_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(NominateCardCommandHandlerFixture, room_name_user_uuid_card_have_value_room_finded_but_card_not_nominated)
{
    RoomMock room;

    protocol::entity::server::request::NominateCard request;
    request.room_name = "user_room";
    request.user_uuid = "user_uuid";
    request.card      = protocol::entity::Card::Rock;

    EXPECT_CALL(room_storage, try_find_room(request.room_name))
        .WillOnce(Return(std::optional<std::reference_wrapper<domain::interface::Room>>{room}));
    EXPECT_CALL(room, try_nominate_user_card(request.user_uuid, request.card)).WillOnce(Return(false));

    auto response = nominate_card_command_handler.handle(std::move(request), connection);

    EXPECT_FALSE(response.is_ok);
}

TEST_F(NominateCardCommandHandlerFixture, room_name_user_uuid_card_have_value_room_finded_but_card_nominated)
{
    RoomMock room;

    protocol::entity::server::request::NominateCard request;
    request.room_name = "user_room";
    request.user_uuid = "user_uuid";
    request.card      = protocol::entity::Card::Rock;

    EXPECT_CALL(room_storage, try_find_room(request.room_name))
        .WillOnce(Return(std::optional<std::reference_wrapper<domain::interface::Room>>{room}));
    EXPECT_CALL(room, try_nominate_user_card(request.user_uuid, request.card)).WillOnce(Return(true));

    auto response = nominate_card_command_handler.handle(std::move(request), connection);

    EXPECT_TRUE(response.is_ok);
}
