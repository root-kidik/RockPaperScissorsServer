#include <memory>
#include <mock/client/ConnectionMock.hpp>
#include <mock/util/TimerMock.hpp>

#include <domain/model/round_pipe/ForceNominatePlayerCard.hpp>

class ForceNominatePlayerCardTest : public testing::Test
{
public:
    ForceNominatePlayerCardTest()
    {
        player.connection = connection;
    }

    std::shared_ptr<ConnectionMock>     connection = std::make_shared<ConnectionMock>();
    domain::model::Room::Player         player;
    domain::entity::Uuid                uuid;
    std::vector<protocol::entity::Card> deck;

    domain::model::Room::RoundContext                  context{player, uuid, deck};
    protocol::entity::MessageSender                    command_sender;
    domain::model::round_pipe::ForceNominatePlayerCard pipe{command_sender};
};
