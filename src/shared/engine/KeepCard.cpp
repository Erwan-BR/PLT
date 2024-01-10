#include "KeepCard.h"

namespace engine
{
    /// @brief Constructor of the KeepCard command from a json. Used by the engine when render send a JSON version of a command.
    /// @param jsonCommand Json content of the command.
    KeepCard::KeepCard (Json::Value jsonCommand) :
        Command(CommandID::KEEPCARD, jsonCommand["playerIndex"].asInt(), jsonCommand["cardIndex"].asInt())
    {
    }

    /// @brief Constructor of the command that allows to keep a card.
    /// @param playerIndex Player that did the command.
    /// @param cardIndex Card that is kept during the pkanification phase.
    KeepCard::KeepCard (int playerIndex, int cardIndex) :
        Command(CommandID::KEEPCARD, playerIndex, cardIndex)
    {

    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    KeepCard::~KeepCard ()
    {

    }

    /// @brief Launch the command to keep a card.
    void KeepCard::launchCommand (state::Game* game) const
    {
        game->getPlayers()[this->playerIndex]->keepCard(this->cardIndex);
    }
}