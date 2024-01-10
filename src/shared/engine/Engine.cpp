#include "Engine.h"

// Including thos to construct commands
#include "engine/EndPlanification.h"
#include "engine/ChooseDraftCard.h"
#include "engine/SendResourceToEmpire.h"
#include "engine/KeepCard.h"
#include "engine/DiscardCard.h"
#include "engine/AddResource.h"
#include "engine/EndProduction.h"
#include "engine/ConvertResource.h"
#include "engine/SaveGame.h"

#include <unistd.h>
#include <thread>
#include <iostream>

namespace engine
{
    /// @brief Full constructor of the engine.
    /// @param currentGame Game that is played.
    /// @param locker Mutext that protects commandToExecute to avoid 2 resource using it simultaneously.
    Engine::Engine(std::shared_ptr<state::Game> currentGame, std::mutex & locker) :
        currentGame(currentGame),
        locker(locker)
    {

    }

    /// @brief Destructor of the engine class. Empty for the moment.
    Engine::~Engine()
    {
        for (Command* command : this->commandToExecute)
        {
            delete command;
        }
    }

    /// @brief Run the complete game. Logic of the game is done in Game, and waiting for AI / Players to play is done here.
    /// @param shouldLaunchGame State if the game is launched from the function. True when the game is not rendered.
    void Engine::gameRunning(bool shouldLaunchGame)
    {
        // Launch the game only if needed (the game is launched in main when rendered.)
        if (shouldLaunchGame)
        {
            this->currentGame->initGame();
        }

        while(state::GamePhase::FINISHED != this->currentGame->getPhase())
        {
            this->phaseRunning();
        }
    }

    /// @brief Run a phase, according to the current phase.
    void Engine::phaseRunning()
    {
        // Vector of method of AI
        using AIMethodPtr = void (state::Player::*)();
        const std::vector<AIMethodPtr> aiMethodVector = {&state::Player::AIChooseDraftingCard, &state::Player::AIPlanification, &state::Player::AIUseProducedResources};
        
        // Vector of method of Game to call at the end.
        using GameMethodPtr = void (state::Game::*)();
        const std::vector<GameMethodPtr> gameMethodVector = {&state::Game::nextDraft, &state::Game::endPlanification, &state::Game::nextProduction};

        int currentPhase = (int) (this->currentGame->getPhase());

        // Make AIs play first.
        for (std::shared_ptr<state::Player> player : this->currentGame->getPlayers())
        {
            if (player->isAI())
            {
                // Calling the method linked to the current phase.
                (player.get()->*(aiMethodVector[currentPhase]))();
            }
        }

        // Now, we are waiting for players to play. 1 second to avoid making too much computation for nothing.
        while(! this->areAllRealPlayersPending())
        {
            locker.lock();
            this->excuteAllCommands();
            locker.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
        }
        // Once finished, we can call the next method of game.
        (this->currentGame.get()->*(gameMethodVector[currentPhase]))();
    }

    /// @brief Check if all real players are pending or not.
    /// @return Boolean that state if all players have played. TRUE : all player are waiting. FALSE : At least one player is playing.
    bool Engine::areAllRealPlayersPending()
    {
        for(std::shared_ptr<state::Player> player : this->currentGame->getPlayers())
        {
            // Checdking for real player if only one is playing.
            if (player->isRealPlayerAndPlaying())
            {
                return false;
            }
        }
        return true;
    }

    /// @brief Execute all commands
    void Engine::excuteAllCommands ()
    {
        // Iterate among all commands to execute them.
        for (Command* command : this->commandToExecute)
        {
            command->launchCommand(this->currentGame);
        }

        // Clear the vector of command once they are executed.
        commandToExecute.clear();
    }

    /// @brief Receive a new command and execute it.
    /// @param jsonCommand New command that will be performed last.
    void Engine::receiveCommand (Json::Value jsonCommand)
    {
        Command* newCommand ;
        switch (jsonCommand["id"].asInt())
        {
            case CommandID::ADDRESOURCE :
                newCommand = new AddResource(jsonCommand);
                break;
            case CommandID::DISCARDCARD :
                newCommand = new DiscardCard(jsonCommand);
                break;
            case CommandID::CHOOSEDRAFTCARD :
                newCommand = new ChooseDraftCard(jsonCommand);
                break;
            case CommandID::KEEPCARD :
                newCommand = new KeepCard(jsonCommand);
                break;
            case CommandID::SENDRESOURCETOEMPIRE :
                newCommand = new SendResourceToEmpire(jsonCommand);
                break;
            case CommandID::ENDPLANIFICATION :
                newCommand = new EndPlanification(jsonCommand);
                break;
                case CommandID::ENDPRODUCTION :
                newCommand = new EndProduction(jsonCommand);
                break;
            case CommandID::CONVERTRESOURCE :
                newCommand = new ConvertResource(jsonCommand);
                break;
            case CommandID::SAVEGAME :
                newCommand = new SaveGame(jsonCommand);
                break;
            default :
                return ;
        }
        this->commandToExecute.push_back(newCommand);
    }
}