#include "EndProduction.h"

namespace engine
{
    /// @brief Constructor of the EndProduction command from a json. Used by the engine when render send a JSON version of a command.
    /// @param jsonCommand Json content of the command.
    EndProduction::EndProduction (Json::Value jsonCommand) :
        Command(CommandID::ENDPRODUCTION, jsonCommand["playerIndex"].asInt())
    {
    }

    /// @brief Constructor of the command that allows to end the production phase.
    /// @param playerIndex Player that did the command.
    EndProduction::EndProduction (int playerIndex) :
        Command(CommandID::ENDPRODUCTION, playerIndex)
    {

    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    EndProduction::~EndProduction ()
    {

    }

    /// @brief Launch the command to end the production phase for this player.
    void EndProduction::launchCommand (state::Game* game) const
    {
        game->getPlayers()[this->playerIndex]->endProduction();
    }
}