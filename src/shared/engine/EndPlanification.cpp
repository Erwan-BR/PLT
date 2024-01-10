#include "EndPlanification.h"

namespace engine
{
    /// @brief Constructor of the EndPlanification command from a json. Used by the engine when render send a JSON version of a command.
    /// @param jsonCommand Json content of the command.
    EndPlanification::EndPlanification (Json::Value jsonCommand) :
        Command(CommandID::ENDPLANIFICATION, jsonCommand["playerIndex"].asInt())
    {
    }

    /// @brief Constructor of the command that allows to end the planification phase.
    /// @param playerIndex Player that did the command.
    /// @param cardIndex Card that is kept during the drafting phase.
    EndPlanification::EndPlanification (int playerIndex) :
        Command(CommandID::ENDPLANIFICATION, playerIndex)
    {

    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    EndPlanification::~EndPlanification ()
    {

    }

    /// @brief Launch the command to end the planification phase for this player.
    void EndPlanification::launchCommand (state::Game* game) const
    {
        game->getPlayers()[this->playerIndex]->endPlanification();
    }
}