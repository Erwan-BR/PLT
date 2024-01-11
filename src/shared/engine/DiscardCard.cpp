#include "DiscardCard.h"

namespace engine
{
    /// @brief Constructor of the command that allows to discard a card.
    /// @param player Player that did the command.
    /// @param cardIndex Card that is kept during the drafting phase.
    /// @param isADraftedCard Indicate the origin of the card of the player.
    DiscardCard::DiscardCard (state::Player* player, int cardIndex, bool isADraftedCard) :
        Command(CommandID::DISCARDCARD, player, cardIndex),
        isADraftedCard(isADraftedCard)
    {

    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    DiscardCard::~DiscardCard ()
    {

    }

    /// @brief Launch the command to discard a card.
    void DiscardCard::launchCommand () const
    {
        this->player->discardCard(this->cardIndex, this->isADraftedCard);
    }
}