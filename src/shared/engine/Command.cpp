#include "Command.h"

namespace engine
{
    /// @brief Create a command that doesn't require a player.
    /// @param id ID of the command.
    Command::Command(CommandID id) :
        id(id)
    {
    }

    /// @brief Constructor of a command.
    /// @param id ID of the command. List is on CommandID.h file.
    /// @param playerIndex Player that launched the command.
    /// @param cardIndex Index of the card where the command might be used.
    /// @param resource Type of the resource that might be used for the command.
    Command::Command (CommandID id, int playerIndex, int cardIndex, state::ResourceType resource) :
        id(id),
        playerIndex(playerIndex),
        cardIndex(cardIndex),
        resource(resource)        
    {
    }

    /// @brief Constructor of a command, without the need of resource.
    /// @param id ID of the command.
    /// @param playerIndex Player that launched the command.
    /// @param cardIndex Index of the card where the command is used.
    Command::Command (CommandID id, int playerIndex, int cardIndex) :
        id(id),
        playerIndex(playerIndex),
        cardIndex(cardIndex)
    {
    }

    /// @brief Constructor of a command, without the need of a card.
    /// @param id ID of the command.
    /// @param playerIndex Player that launched the command.
    /// @param cardIndex Resource tha tis needed for the command.
    Command::Command (CommandID id, int playerIndex, state::ResourceType resource) :
        id(id),
        playerIndex(playerIndex),
        resource(resource)
    {
    }

    /// @brief Constructor of a command.
    /// @param id ID of the command. List is on CommandID.h file.
    /// @param playerIndex Player that launched the command.
    Command::Command (CommandID id, int playerIndex) :
        id(id),
        playerIndex(playerIndex)
    {
    }

    Command::Command (CommandID id, int playerIndex, int cardIndex, bool isADraftedCard) :
        id(id),
        playerIndex(playerIndex),
        cardIndex(cardIndex),
        isADraftedCard(isADraftedCard)
    {

    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    Command::~Command ()
    {
    }

    void Command::launchCommand(std::shared_ptr<state::Game> game) const 
    {
        return ;
    }

    Json::Value Command::toJSON() const 
    {
        Json::Value jsonContent ;

        jsonContent["id"] = static_cast<int> (this->id);
        jsonContent["playerIndex"] = this->playerIndex;
        jsonContent["cardIndex"] = this->cardIndex;
        jsonContent["resource"] = static_cast<int> (this->resource);
        jsonContent["isADraftedCard"] = this->isADraftedCard;

        return jsonContent;
    }

    /************************************* Setters & Getters *************************************/

    /// @brief Allows to get the command ID, that is needed to know which action will be done.
    /// @return ID of the command done.
    CommandID Command::getCommandId () const
    {
        return this->id;
    }
}