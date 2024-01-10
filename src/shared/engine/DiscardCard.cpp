#include "DiscardCard.h"

namespace engine
{
    /// @brief Constructor of the command that allows to discard a card.
    /// @param playerIndex Player that did the command.
    /// @param cardIndex Card that is kept during the drafting phase.
    /// @param isADraftedCard Indicate the origin of the card of the player.
    DiscardCard::DiscardCard (int playerIndex, int cardIndex, bool isADraftedCard) :
        Command(CommandID::DISCARDCARD, playerIndex, cardIndex)
    {
        this->isADraftedCard = isADraftedCard;
    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    DiscardCard::~DiscardCard ()
    {

    }

    /// @brief Launch the command to discard a card.
    void DiscardCard::launchCommand (state::Game* game) const
    {
        game->getPlayers()[this->playerIndex]->discardCard(this->cardIndex, this->isADraftedCard);
    }
}