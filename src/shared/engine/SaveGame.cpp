#include "SaveGame.h"

namespace engine
{
    /// @brief Constructor of the SaveGame command from a json. Used by the engine when render send a JSON version of a command.
    /// @param jsonCommand Json content of the command.
    SaveGame::SaveGame (Json::Value jsonCommand) :
        Command(CommandID::SAVEGAME)
    {
    }

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
    void SaveGame::launchCommand (state::Game* game) const
    {
        // To complete.
        return ;
    }
}