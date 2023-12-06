#include "SendResourceToEmpire.h"

namespace engine
{
    SendResourceToEmpire::SendResourceToEmpire(state::Player* player, state::ResourceType resource):
    player(player),
    resource(resource)
    {
        id = SENDRESOURCETOEMPIRE;
    }

    SendResourceToEmpire::~SendResourceToEmpire(){}

    void SendResourceToEmpire::execute()
    {
        player->sendResourceToEmpire(resource);
    }
}