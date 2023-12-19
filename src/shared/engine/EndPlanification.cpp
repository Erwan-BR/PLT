#include "EndPlanification.h"

namespace engine
{
    /// @brief Constructor of the command that allows to end the planification phase.
    /// @param player Player that did the command.
    /// @param cardIndex Card that is kept during the drafting phase.
    EndPlanification::EndPlanification (state::Player* player) :
        Command(CommandID::ENDPLANIFICATION, player)
    {

    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    EndPlanification::~EndPlanification ()
    {

    }

    /// @brief Launch the command to end the planification phase for this player.
    void EndPlanification::launchCommand () const
    {
        this->player->endPlanification();
    }
}