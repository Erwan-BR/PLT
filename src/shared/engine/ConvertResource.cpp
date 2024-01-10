#include "ConvertResource.h"

namespace engine
{
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
    void ConvertResource::launchCommand (state::Game* game) const
    {
        game->getPlayers()[this->playerIndex]->convertKrystallium(this->resource);
    }
}