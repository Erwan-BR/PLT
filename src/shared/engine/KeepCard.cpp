#include "KeepCard.h"

namespace engine
{
    /// @brief Constructor of the command that allows to keep a card.
    /// @param player Player that did the command.
    /// @param cardIndex Card that is kept during the pkanification phase.
    KeepCard::KeepCard (state::Player* player, int cardIndex) :
        Command(CommandID::KEEPCARD, player, cardIndex)
    {

    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    KeepCard::~KeepCard ()
    {

    }

    /// @brief Launch the command to keep a card.
    void KeepCard::launchCommand () const
    {

    }
}