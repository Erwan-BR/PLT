#include "Command.h"

namespace engine
{
    /// @brief Create a command that doesn't require a player.
    /// @param id ID of the command.
    Command::Command(CommandID id) :
        id(id),
        player(NULL)
    {

    }

    /// @brief Constructor of a command.
    /// @param id ID of the command. List is on CommandID.h file.
    /// @param player Player that launched the command.
    /// @param cardIndex Index of the card where the command might be used.
    /// @param resource Type of the resource that might be used for the command.
    Command::Command (CommandID id, state::Player* player, int cardIndex, state::ResourceType resource) :
        id(id),
        player(player),
        cardIndex(cardIndex),
        resource(resource)        
    {

    }

    /// @brief Constructor of a command, without the need of resource.
    /// @param id ID of the command.
    /// @param player Player that launched the command.
    /// @param cardIndex Index of the card where the command is used.
    Command::Command (CommandID id, state::Player* player, int cardIndex) :
        id(id),
        player(player),
        cardIndex(cardIndex)
    {

    }

    /// @brief Constructor of a command, without the need of a card.
    /// @param id ID of the command.
    /// @param player Player that launched the command.
    /// @param cardIndex Resource tha tis needed for the command.
    Command::Command (CommandID id, state::Player* player, state::ResourceType resource) :
        id(id),
        player(player),
        resource(resource)
    {

    }

    /// @brief Constructor of a command.
    /// @param id ID of the command. List is on CommandID.h file.
    /// @param player Player that launched the command.
    Command::Command (CommandID id, state::Player* player) :
        id(id),
        player(player)
    {

    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    Command::~Command ()
    {

    }

    /************************************* Setters & Getters *************************************/

    /// @brief Allows to get the command ID, that is needed to know which action will be done.
    /// @return ID of the command done.
    CommandID Command::getCommandId () const
    {
        return this->id;
    }
}