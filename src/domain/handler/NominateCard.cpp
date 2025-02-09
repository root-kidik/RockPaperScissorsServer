#include <domain/handler/NominateCard.hpp>
#include <domain/interface/RoomStorage.hpp>

namespace rps::domain::handler
{

NominateCard::NominateCard(interface::RoomStorage& room_storage) : m_room_storage{room_storage}
{
}

protocol::entity::server::StatusResponse NominateCard::handle(protocol::entity::server::NominateCardRequest&& request,
                                                              const std::shared_ptr<protocol::interface::Connection>& connection)
{
    protocol::entity::server::StatusResponse response;

    if (request.room_name.empty() || request.user_uuid.empty() || !protocol::util::is_enum_has_valid_value(request.card))
    {
        response.is_ok = false;
        return response;
    }

    auto room = m_room_storage.try_find_room(request.room_name);

    if (!room)
    {
        response.is_ok = false;
        return response;
    }

    response.is_ok = room.value().get().try_nominate_user_card(request.user_uuid, request.card);
    return response;
}

} // namespace rps::domain::handler
