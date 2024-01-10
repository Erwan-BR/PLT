#include "DiscardCard.h"

namespace engine
{
    /// @brief Constructor of the DiscardCard command from a json. Used by the engine when render send a JSON version of a command.
    /// @param jsonCommand Json content of the command.
    DiscardCard::DiscardCard (Json::Value jsonCommand) :
        Command(CommandID::DISCARDCARD,
                jsonCommand["playerIndex"].asInt(),
                jsonCommand["cardIndex"].asInt(),
                jsonCommand["isADraftedCard"].asBool()
                )
    {
    }

    /// @brief Constructor of the command that allows to discard a card.
    /// @param playerIndex Player that did the command.
    /// @param cardIndex Card that is kept during the drafting phase.
    /// @param isADraftedCard Indicate the origin of the card of the player.
    DiscardCard::DiscardCard (int playerIndex, int cardIndex, bool isADraftedCard) :
        Command(CommandID::DISCARDCARD, playerIndex, cardIndex)
    {
        this->isADraftedCard = isADraftedCard;
    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    DiscardCard::~DiscardCard ()
    {

    }

    /// @brief Launch the command to discard a card.
    void DiscardCard::launchCommand (std::shared_ptr<state::Game> game) const
    {
        game->getPlayers()[this->playerIndex]->discardCard(this->cardIndex, this->isADraftedCard);
    }
}