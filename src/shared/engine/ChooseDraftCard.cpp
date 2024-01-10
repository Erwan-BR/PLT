#include "ChooseDraftCard.h"

namespace engine
{
    /// @brief Constructor of the command that allows to keep a card from the draft phase.
    /// @param playerIndex Player that did the command.
    /// @param cardIndex Card that is kept during the drafting phase.
    ChooseDraftCard::ChooseDraftCard (int playerIndex, int cardIndex) :
        Command(CommandID::CHOOSEDRAFTCARD, playerIndex, cardIndex)
    {

    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    ChooseDraftCard::~ChooseDraftCard ()
    {

    }

    /// @brief Launching the command to choose the card from the draft cards.
    void ChooseDraftCard::launchCommand (state::Game* game) const
    {
        game->getPlayers()[this->playerIndex]->chooseDraftCard(this->cardIndex);
    }
}