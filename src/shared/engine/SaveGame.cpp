#include "SaveGame.h"

namespace engine
{
    /// @brief Constructor of the command that allows to save a game.
    SaveGame::SaveGame () :
        Command(CommandID::SAVEGAME)
    {

    }

    /// @brief Destructor of the command. Should destruct anything because pointers are shared.
    SaveGame::~SaveGame ()
    {

    }

    /// @brief Launch the command to save a game.
    void SaveGame::launchCommand () const
    {
        // To complete.
        return ;
    }
}