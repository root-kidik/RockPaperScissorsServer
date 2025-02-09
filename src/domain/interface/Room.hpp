#pragma once

#include <chrono>
#include <cstdint>
#include <memory>

#include <domain/entity/Uuid.hpp>

#include <RockPaperScissorsProtocol/entity/Card.hpp>
#include <RockPaperScissorsProtocol/interface/Connection.hpp>

namespace rps::domain::interface
{

class Room
{
public:
    static constexpr std::uint8_t         kMaxPlayers{6};
    static constexpr std::chrono::seconds kTurnTime{10};

    virtual ~Room() = default;

    virtual bool try_add_user(const entity::Uuid&                                     user_uuid,
                              const std::string&                                      user_nickname,
                              const std::shared_ptr<protocol::interface::Connection>& connection) = 0;

    virtual bool try_start_game(const entity::Uuid& user_uuid) = 0;

    virtual bool try_nominate_user_card(const entity::Uuid& user_uuid, protocol::entity::Card card) = 0;
};

} // namespace rps::domain::interface
