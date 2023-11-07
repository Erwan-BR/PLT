//Written by Adrien MILLASSEAU and Onur DEMIRBAS

#include "Game.h"
#include <algorithm>
#include <random>

namespace state {
	///@brief Create an instance of the class Game
	Game::Game() :
		players(),
		turn(0),
		phase(PRODUCTION),
		deck(),
		isClockwise(true)
	{

	}

	///@brief Create an instance of the class Game with players specified
	///@param players Vector of pointers which designate the players of the game
	Game::Game(std::vector<Player*> players) :
		players(players),
		turn(0),
		phase(PRODUCTION),
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
		std::vector<EmpireCard*> empires = initEmpire();
		initCards();
		initPlayers(empires);
		startGame();
	}

	///@brief Create and Initialize the Cards for the game
	void Game::initCards ()
	{
		// To do: Create the deck with all the cards
		auto rng = std::default_random_engine {};
		std::shuffle(std::begin(deck), std::end(deck), rng);
	}

	/// @brief Import all Cards from the CSV file.
	void importCardsFromCsv ()
	{

	}

	///@brief Create and Initialize the Empire for the game
	std::vector<EmpireCard*> Game::initEmpire ()
	{
		// To do: Create the empires (choose face A and/or B ?) + create a deck to shuffle
		
	}

	///@brief Start the game
	void Game::startGame ()
	{
		nextPhase();
	}

	///@brief Manage the progress of the game and start the next phase among Draft, Planification and Production
	void Game::nextPhase ()
	{
		if(DRAFT == this->phase)
		{
			this->phase = PLANIFICATION;
			initPlanification();
		}
		else if(PLANIFICATION == this->phase)
		{
			this->phase = PRODUCTION;
		}
		else if(PRODUCTION == this->phase)
		{
			newTurn();
			this->phase = DRAFT;
			initDraft();
		}		
	}

	///@brief Start one of the four turn of the game
	void Game::newTurn ()
	{
		turn = turn + 1;
		if(turn == 5)
		{
			endGame();
		}

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
		for(Player* player : this->players)
		{
			// Initialise the cards that will be given to the players
		}
	}

	///@brief Start a Draft
	void Game::nextDraft ()
	{
		// 7 drafted cards
		for(int i=0;i<7;i++)
		{
			for(Player* player : this->players)
			{

			}
		}
		endDraft();

	}

	///@brief End the current Draft phase
	void Game::endDraft ()
	{
		nextPhase();
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
	/// @brief Distributes the empires to the players
	void initPlayers (std::vector<EmpireCard*> empires)
	{

	}

	/// @brief Ends the game, counts every player's victory points and compares them tp give a podium
	void endGame ()
	{

	}
}