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
        players.emplace_back(player);
    }

    std::shared_ptr<ConnectionMock>                                  connection = std::make_shared<ConnectionMock>();
    domain::model::Room::Player                                      player;
    std::vector<std::reference_wrapper<domain::model::Room::Player>> players;
    std::vector<protocol::entity::Card>                              deck;

    domain::model::Room::RoundContext                  context{players, deck};
    protocol::entity::MessageSender                    command_sender;
    domain::model::round_pipe::ForceNominatePlayerCard pipe{command_sender};
};
