#include "AddResource.h"

namespace engine
{
    /// @brief Constructor of the command that allows to add a resource on a card.
    /// @param player Player that did the command.
    /// @param resource Resource to send to a card.
    /// @param cardIndex Card that receive the resource.
    AddResource::AddResource (state::Player* player, state::ResourceType resource, int cardIndex) :
        Command(CommandID::ADDRESOURCE, player, cardIndex, resource)
    {

    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    AddResource::~AddResource ()
    {

    }

    /// @brief Launching the command to add a resource.
    void AddResource::launchCommand () const
    {
        this->player->addResource(this->resource, this->cardIndex);
    }
}