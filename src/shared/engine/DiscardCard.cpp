#include "DiscardCard.h"

namespace engine
{
    /// @brief Constructor of the command that allows to discard a card.
    /// @param player Player that did the command.
    /// @param cardIndex Card that is kept during the drafting phase.
    DiscardCard::DiscardCard (state::Player* player, int cardIndex) :
        Command(CommandID::DISCARDCARD, player, cardIndex)
    {

    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    DiscardCard::~DiscardCard ()
    {

    }

    /// @brief Launch the command to discard a card.
    void DiscardCard::launchCommand () const
    {

    }
}