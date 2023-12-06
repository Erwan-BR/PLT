#include "DiscardCard.h"

namespace engine
{
    DiscardCard::DiscardCard(state::Player* player, state::DevelopmentCard* card):
    player(player),
    card(card)
    {
        id = DISCARDCARD;
    }

    DiscardCard::~DiscardCard(){}

    void DiscardCard::execute()
    {
        player->discardCard(card);
    }
}