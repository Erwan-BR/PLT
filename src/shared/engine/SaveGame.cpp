#include "SaveGame.h"

#include <fstream>
#include <sstream>
#include <string>

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
    /// @param game Game where the command is launched.
    void SaveGame::launchCommand (constants::gamePtr game) const
    {
        const std::string outputFileName = "./bin/save.json";
        const Json::Value jsonVersionOfGame = game->toJSON();

        Json::FastWriter fastWriter;
        const std::string output = fastWriter.write(jsonVersionOfGame);

        // Instantiation of a fstream object which is a file.
        std::fstream writingFile;

        // Opening the file in reading mode.
        writingFile.open(outputFileName, std::ios::out);

        // Checking if the file is correctly opened.
        if (writingFile.is_open())
        {
            // Writing in file the textFile information concerning the current student.
            writingFile << output << std::endl;
            
            // Closing the file because we do not need it anymore.
            writingFile.close();
        }
    }
}