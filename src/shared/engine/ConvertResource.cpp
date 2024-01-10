#include "ConvertResource.h"

namespace engine
{
    /// @brief Constructor of the ConvertResource command from a json. Used by the engine when render send a JSON version of a command.
    /// @param jsonCommand Json content of the command.
    ConvertResource::ConvertResource (Json::Value jsonCommand) :
        Command(CommandID::CONVERTRESOURCE, jsonCommand["playerIndex"].asInt(), static_cast<state::ResourceType> (jsonCommand["resource"].asInt()))
    {
    }

    /// @brief Constructor of the command that convert a krystallium into another resource.
    /// @param playerIndex Player that did the command.
    /// @param resource Resource that the player wants to have.
    ConvertResource::ConvertResource (int playerIndex, state::ResourceType resource) :
        Command(CommandID::CONVERTRESOURCE, playerIndex, resource)
    {

    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    ConvertResource::~ConvertResource ()
    {

    }

    /// @brief Launching the command to convert a krystallium.
    void ConvertResource::launchCommand (std::shared_ptr<state::Game> game) const
    {
        game->getPlayers()[this->playerIndex]->convertKrystallium(this->resource);
    }
}