//Written by Adrien MILLASSEAU

#include "Game.h"

namespace state {
	///@brief Create an instance of the class Game
	Game::Game() :
		players(),
		turn(0),
		phase(DRAFT),
		deck(),
		isClockwise(true)
	{

	}

	///@brief Create an instance of the class Game with players specified
	///@param players Vector of pointers which designate the players of the game
	Game::Game(std::vector<Player*> players) :
		players(players),
		turn(0),
		phase(DRAFT),
		deck(),
		isClockwise(true)
	{

	}

	///@brief Destructor of the Class Game
	Game::~Game ()
	{

	}

	///@brief Initialize the game
	void Game::initGame ()
	{
		Game();
		startGame();
	}

	///@brief Create and Initialize the Cards for the game
	void Game::initCards ()
	{

	}

	///@brief Create and Initialize the Empire for the game
	void Game::initEmpire ()
	{

	}

	///@brief Start the game
	void Game::startGame ()
	{

	}

	///@brief Manage the progress of the game and start the next phase among Draft, Planification and Production
	void Game::nextPhase ()
	{
		if(phase == DRAFT)
		{
			phase = PLANIFICATION;
		}
		if(phase == PLANIFICATION)
		{
			phase = PRODUCTION;
		}
		if(phase == PRODUCTION)
		{
			phase = DRAFT;
		}		
	}

	///@brief Start one of the four turn of the game
	void Game::newTurn ()
	{
		turn = turn + 1;
		if (turn%2 == 1)
		{
			isClockwise = true;
		}
		else
		{
			isClockwise = false;
		}
	}

	///@brief Initialize the Draft part of the game during which players select their cards
	void Game::initDraft ()
	{

	}

	///@brief Start a Draft
	void Game::nextDraft ()
	{

	}

	///@brief End the current Draft phase
	void Game::endDraft ()
	{

	}

	///@brief Initialize the Planification phase during which players choose the cards they will try to build
	void Game::initPlanification ()
	{

	}

	///@brief Manage the phase of production for all player and one resource
	///@param toProduceResource Pointer which designate the type of resource currently to produce
	void Game::produceResource (Resource* toProduceResource)
	{


	}

	///@brief Send a resource earned by a player to let him use it
	///@param resource Pointer which designate the type of resource sent
	///@param player Pointer which designate the player who receive the resource
	void Game::sendResourceToPlayer (Resource* resource, Player* player) const
	{

	}

	///@brief Debug method to check the state of the instance of Game
	///@return String explaining the state of Game
	std::string Game::toString () const
	{
		return "";
	}
}