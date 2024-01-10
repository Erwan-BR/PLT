#include "ChooseDraftCard.h"

namespace engine
{
    /// @brief Constructor of the ChooseDraftCard command from a json. Used by the engine when render send a JSON version of a command.
    /// @param jsonCommand Json content of the command.
    ChooseDraftCard::ChooseDraftCard (Json::Value jsonCommand) :
        Command(CommandID::CHOOSEDRAFTCARD, jsonCommand["playerIndex"].asInt(), jsonCommand["cardIndex"].asInt())
    {
    }

    /// @brief Constructor of the command that allows to keep a card from the draft phase.
    /// @param playerIndex Player that did the command.
    /// @param cardIndex Card that is kept during the drafting phase.
    ChooseDraftCard::ChooseDraftCard (int playerIndex, int cardIndex) :
        Command(CommandID::CHOOSEDRAFTCARD, playerIndex, cardIndex)
    {

    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    ChooseDraftCard::~ChooseDraftCard ()
    {

    }

    /// @brief Launching the command to choose the card from the draft cards.
    void ChooseDraftCard::launchCommand (std::shared_ptr<state::Game> game) const
    {
        game->getPlayers()[this->playerIndex]->chooseDraftCard(this->cardIndex);
    }
}