#include <memory>
#include <mock/client/ConnectionMock.hpp>
#include <mock/util/TimerMock.hpp>

#include <domain/model/round_pipe/ForceNominatePlayerCardPipe.hpp>

class ForceNominatePlayerCardPipeFixture : public testing::Test
{
public:
    ForceNominatePlayerCardPipeFixture()
    {
        player.connection = connection;
    }

    std::shared_ptr<ConnectionMock>                        connection = std::make_shared<ConnectionMock>();
    domain::model::Room::Player                            player;
    domain::entity::Uuid                                   uuid;
    domain::model::Room::RoundContext                      context{player, uuid};
    protocol::entity::CommandSender                        command_sender;
    domain::model::round_pipe::ForceNominatePlayerCardPipe pipe{command_sender};
};
