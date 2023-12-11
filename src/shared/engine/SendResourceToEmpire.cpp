#include "SendResourceToEmpire.h"

namespace engine
{
    /// @brief Constructor of the command that allows to discard a card.
    /// @param player Player that did the command.
    /// @param resource Resource that is discarded by the player.
    SendResourceToEmpire::SendResourceToEmpire (state::Player* player, state::ResourceType resource) :
        Command(CommandID::SENDRESOURCETOEMPIRE, player, resource)
    {

    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    SendResourceToEmpire::~SendResourceToEmpire ()
    {

    }

    /// @brief Launch the command to send a resource to the empire of a player.
    void SendResourceToEmpire::launchCommand () const
    {

    }
}