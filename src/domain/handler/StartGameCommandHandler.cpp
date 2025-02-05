#include <sstream>
#include <cassert>

#include <domain/handler/StartGameCommandHandler.hpp>
#include <domain/interface/RoomStorage.hpp>
#include <domain/interface/Timer.hpp>
#include <domain/interface/UserStorage.hpp>

#include <RockPaperScissorsProtocol/utils/Utils.hpp>

namespace rps::domain::handler
{

StartGameCommandHandler::StartGameCommandHandler(interface::RoomStorage&                     room_storage,
                                                 interface::UserStorage&                     user_storage,
                                                 protocol::entity::GameStartedCommandSender& command_sender) :
m_room_storage{room_storage},
m_user_storage{user_storage},
m_command_sender{command_sender}
{
}

protocol::entity::server::StatusResponse StartGameCommandHandler::handle(
    protocol::entity::server::StartGameRequest&&            request,
    const std::shared_ptr<protocol::interface::Connection>& connection)
{
    protocol::entity::server::StatusResponse response;

    if (request.room_name.empty() || request.user_uuid.empty())
    {
        response.is_ok = false;
        return response;
    }

    auto room = m_room_storage.try_find_room(request.room_name);

    if (!room || room.value().get().owner_uuid != request.user_uuid)
    {
        response.is_ok = false;
        return response;
    }

    auto& room_ref           = room.value().get();
    room_ref.is_game_started = true;

    for (auto& player_uuid : room_ref.players)
        if (auto player = m_user_storage.try_find_user(player_uuid))
        {
            protocol::entity::client::GameStartedRequest new_request;

            for (std::size_t i = 0; i < protocol::entity::kMaxCardsPerPlayer; i++)
            {
                assert(!room_ref.cards.empty());
                
                auto card = room_ref.cards.back();
                new_request.cards[i] = card;
                player.value().get().cards.push_back(card);
                room_ref.cards.pop_back();
            }

            m_command_sender.send(std::move(new_request), player.value().get().connection);
        }

    // room_ref.timer->start(entity::Room::kTurnTime, [](){
    // DealDeck
    // }, false);

    response.is_ok = true;
    return response;
}

} // namespace rps::domain::handler
