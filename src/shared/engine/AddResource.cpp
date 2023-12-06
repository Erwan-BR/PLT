#include "AddResource.h"

namespace engine
{
    AddResource::AddResource(state::Player* player, state::ResourceType resource, state::DevelopmentCard* card):
    player(player),
    resource(resource),
    card(card)
    {
        id = ADDRESOURCE;
    }

    AddResource::~AddResource(){}

    void AddResource::execute()
    {
        player->addResource(resource, card);
    }
}




