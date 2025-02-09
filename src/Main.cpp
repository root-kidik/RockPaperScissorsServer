#include <infrastructure/RockPaperScissorsServer.hpp>

int main(int argc, char* argv[])
{
    using namespace rps::infrastructure;

    RockPaperScissorsServer server{argc, argv};

    return server.run();
}
