#include "EndProduction.h"

namespace engine
{
    /// @brief Constructor of the command that allows to end the production phase.
    /// @param player Player that did the command.
    EndProduction::EndProduction (state::Player* player) :
        Command(CommandID::ENDPRODUCTION, player)
    {

    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    EndProduction::~EndProduction ()
    {

    }

    /// @brief Launch the command to end the production phase for this player.
    void EndProduction::launchCommand () const
    {
        this->player->endProduction();
    }
}