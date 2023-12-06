#include "ChooseDraftCard.h"

namespace engine
{
    ChooseDraftCard::ChooseDraftCard(state::Player* player, state::DevelopmentCard* card):
    player(player),
    card(card)
    {
        id = CHOOSEDRAFTCARD;
    }

    ChooseDraftCard::~ChooseDraftCard(){}

    void ChooseDraftCard::execute()
    {
        player->chooseDraftCard(card);
    }
}