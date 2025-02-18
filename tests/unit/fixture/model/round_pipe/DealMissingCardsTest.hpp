#include <memory>
#include <mock/client/ConnectionMock.hpp>
#include <mock/util/TimerMock.hpp>

#include <domain/model/round_pipe/DealMissingCards.hpp>

class DealMissingCardsTest : public testing::Test
{
public:
    DealMissingCardsTest()
    {
        player.connection = connection;
        players.emplace_back(player);
    }

    std::shared_ptr<ConnectionMock>                                  connection = std::make_shared<ConnectionMock>();
    domain::model::Room::Player                                      player;
    std::vector<std::reference_wrapper<domain::model::Room::Player>> players;
    domain::entity::Uuid                                             uuid;
    std::vector<protocol::entity::Card>                              deck;
    domain::model::Room::RoundContext                                context{players, deck};
    protocol::entity::MessageSender                                  command_sender;
    domain::model::round_pipe::DealMissingCards                      pipe{command_sender};
};
