#include "SendResourceToEmpire.h"

namespace engine
{
    /// @brief Constructor of the SendResourceToEmpire command from a json. Used by the engine when render send a JSON version of a command.
    /// @param jsonCommand Json content of the command.
    SendResourceToEmpire::SendResourceToEmpire (Json::Value jsonCommand) :
        Command(CommandID::SENDRESOURCETOEMPIRE,
                jsonCommand["playerIndex"].asInt(),
                static_cast<state::ResourceType> (jsonCommand["resource"].asInt())
                )
    {
    }

    /// @brief Constructor of the command that allows to send a resource to the empire.
    /// @param playerIndex Player that did the command.
    /// @param resource Resource that is send to the empire.
    SendResourceToEmpire::SendResourceToEmpire (int playerIndex, state::ResourceType resource) :
        Command(CommandID::SENDRESOURCETOEMPIRE, playerIndex, resource)
    {

    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    SendResourceToEmpire::~SendResourceToEmpire ()
    {

    }

    /// @brief Launch the command to send a resource to the empire of a player.
    void SendResourceToEmpire::launchCommand (constants::gamePtr game) const
    {
        game->getPlayers()[this->playerIndex]->sendResourceToEmpire(this->resource);
    }
}