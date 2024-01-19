#include "SetPreferredPersonnage.h"

namespace engine
{
    /// @brief Constructor of the SetPreferredPersonnage command from a json. Used by the engine when render send a JSON version of a command.
    /// @param jsonCommand Json content of the command.
    SetPreferredPersonnage::SetPreferredPersonnage (Json::Value jsonCommand) :
        Command(CommandID::SETPREFFEREDPERSONNAGE,
                jsonCommand["playerIndex"].asInt(),
                static_cast<state::ResourceType> (jsonCommand["resource"].asInt())
                )
    {
    }

    /// @brief Constructor of the command that allows to change the favourite resource of the player.
    /// @param playerIndex Player that did the command.
    /// @param resource Resource that is send to the empire.
    SetPreferredPersonnage::SetPreferredPersonnage (int playerIndex, state::ResourceType resource) :
        Command(CommandID::SETPREFFEREDPERSONNAGE, playerIndex, resource)
    {

    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    SetPreferredPersonnage::~SetPreferredPersonnage ()
    {

    }

    /// @brief Launch the command to send a resource to the empire of a player.
    void SetPreferredPersonnage::launchCommand (constants::gamePtr game) const
    {
        game->getPlayers()[this->playerIndex]->setPreferedPersonnage(this->resource);
    }
}