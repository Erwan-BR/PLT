#include "AddResource.h"

namespace engine
{

    // AddResource::AddResource (Json::Value jsonCommand)
    // {

    // }

    /// @brief Constructor of the command that allows to add a resource on a card.
    /// @param playerIndex Player that did the command.
    /// @param resource Resource to send to a card.
    /// @param cardIndex Card that receive the resource.
    AddResource::AddResource (int playerIndex, state::ResourceType resource, int cardIndex) :
        Command(CommandID::ADDRESOURCE, playerIndex, cardIndex, resource)
    {

    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    AddResource::~AddResource ()
    {

    }

    /// @brief Launching the command to add a resource.
    void AddResource::launchCommand (state::Game* game) const
    {
        game->getPlayers()[this->playerIndex]->addResource(this->resource, this->cardIndex);
    }

    /*Json::Value AddResource::toJSON() const
    {

    }*/
}