#include <memory>
#include <mock/client/ConnectionMock.hpp>
#include <mock/util/TimerMock.hpp>

#include <domain/model/round_pipe/DealMissingCards.hpp>

class DealMissingCardsPipeFixture : public testing::Test
{
public:
    DealMissingCardsPipeFixture()
    {
        player.connection = connection;
    }

    std::shared_ptr<ConnectionMock>             connection = std::make_shared<ConnectionMock>();
    domain::model::Room::Player                 player;
    domain::entity::Uuid                        uuid;
    domain::model::Room::RoundContext           context{player, uuid};
    protocol::entity::CommandSender             command_sender;
    std::vector<protocol::entity::Card>         deck;
    domain::model::round_pipe::DealMissingCards pipe{command_sender, deck};
};
