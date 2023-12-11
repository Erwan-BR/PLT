#include "Engine.h"

namespace engine
{
    Engine::Engine() :
    currentGame(new state::Game());
    {};

    Engine::Engine(std::vector<state::Player*> players, std::vector<ai::AI> ais*) :
    currentGame(new state::Game(players));
    ais(ais);
    {};

    Engine::~Engine(){};

    void Engine::gameRunning()
    {
        currentGame.initGame();
        bool playersPending = false;
        bool aiPending
        while(currentGame.getTurn() != 5)
        {

            //Selecting the 7 drafted cards.
            for(int i=0; i<7; i++)draftRunning();

            planificationRunning();

            productionRunning();
        }
    }

    void Engine::draftRunning()
    {
        bool playersPlaying = true;

        for(AI* ai : this->ais)
        {
            ai.AIChooseDraftCard();
        }

        while(playersPlaying)playersPlaying = getPlayersState();

        this->currentGame.nextDraft();
    }

    void Engine::planificationRunning()
    {
        bool playersPlaying  = true;

        for(AI* ai : this->ais)
        {
            ai.AIKeepOrDiscardCard();
        }

        while(playersPlaying)playersPlaying = getPlayersState();

        this->currentGame.endPlanification();

    }

    void Engine::productionRunning()
    {
        bool playersPlaying  = true;

        for(AI* ai : this->ais)
        {
            ai.AIAddResource();
        }

        while(playersPlaying)playersPlaying = getPlayersState();

        this->currentGame.endProduction();

    }

    bool Engine::getPlayersState()
    {
        bool playersPlaying = false;
        for(state::Player* player : this->currentGame.getPlayers())
        {
            if(player.getState() == state::PlayerState::PLAYING)playersPlaying == true;
        }

        return playersState;
    }
}