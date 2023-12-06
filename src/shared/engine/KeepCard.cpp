#include "KeepCard.h"

namespace engine
{
    KeepCard::KeepCard(state::Player* player, state::DevelopmentCard* card):
    player(player),
    card(card)
    {
        id = KEEPCARD;
    }

    KeepCard::~KeepCard(){}

    void KeepCard::execute()
    {
        player->keepCard(card);
    }
}