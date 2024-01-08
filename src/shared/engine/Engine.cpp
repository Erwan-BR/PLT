#include "Engine.h"

#include <unistd.h>

namespace engine
{
    /// @brief Full constructor of the engine.
    /// @param currentGame Game that is played.
    /// @param currentCommands Command that can be done in the game.
    Engine::Engine(state::Game* currentGame, std::vector<Command*> currentCommands) :
        currentGame(currentGame),
        currentCommands(currentCommands)
    {

    }

    /// @brief Destructor of the engine class. Empty for the moment.
    Engine::~Engine()
    {

    }

    /// @brief Run the complete game. Logic of the game is done in Game, and waiting for AI / Players to play is done here.
    void Engine::gameRunning()
    {
        this->currentGame->initGame();
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
        for (state::Player* player : this->currentGame->getPlayers())
        {
            if (player->isAI())
            {
                // Calling the method linked to the current phase.
                (player->*(aiMethodVector[currentPhase]))();
            }
        }

        // Now, we are waiting for players to play. 1 second to avoid making too much computation for nothing.
        while(! this->areAllRealPlayersPending())
        {
            sleep(1);
        }
        // Once finished, we can call the next method of game.
        (this->currentGame->*(gameMethodVector[currentPhase]))();
    }

    /// @brief Check if all real players are pending or not.
    /// @return Boolean that state if all players have played. TRUE : all player are waiting. FALSE : At least one player is playing.
    bool Engine::areAllRealPlayersPending()
    {
        for(state::Player* player : this->currentGame->getPlayers())
        {
            // Checdking for real player if only one is playing.
            if (player->isRealPlayerAndPlaying())
            {
                return false;
            }
        }
        return true;
    }
}