#include "ConvertResource.h"

namespace engine
{
    /// @brief Constructor of the command that convert a krystallium into another resource.
    /// @param player Player that did the command.
    /// @param resource Resource that the player wants to have.
    ConvertResource::ConvertResource (state::Player* player, state::ResourceType resource) :
        Command(CommandID::CONVERTRESOURCE, player, resource)
    {

    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    ConvertResource::~ConvertResource ()
    {

    }

    /// @brief Launching the command to convert a krystallium.
    void ConvertResource::launchCommand () const
    {
        this->player->convertKrystallium(this->resource);
    }
}