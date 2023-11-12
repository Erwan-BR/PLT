//Written by Adrien MILLASSEAU and Onur DEMIRBAS

#include "Game.h"
#include <algorithm>
#include <random>
#include <fstream>

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
		return ;
	}

	///@brief Create and Initialize the Cards for the game
	void Game::initCards ()
	{
		return ;
	}

	/// @brief Import all Cards from the CSV file.
	void Game::importCardsFromCsv ()
	{
		return ;
	}

	/// @brief Add a card to the deck, from a line of the CSV file.
	/// @param lineFromCsvFile Line from the CSV that contains data of a DevelopmentCard.
	void Game::addSingleCardToDeck (std::string lineFromCsvFile)
	{
		return ;
	}

	///@brief Create and Initialize the Empire for the game
	std::vector<EmpireCard*> Game::initEmpire ()
	{	
		return {};
	}

	///@brief Start the game
	void Game::startGame ()
	{
		nextPhase();
	}

	///@brief Manage the progress of the game and start the next phase among Draft, Planification and Production
	void Game::nextPhase ()
	{
		return ;
	}

	///@brief Start one of the four turn of the game
	void Game::newTurn ()
	{
		return ;
	}

	///@brief Initialize the Draft part of the game during which players select their cards
	void Game::initDraft ()
	{
		return ;
	}

	///@brief Start a Draft
	void Game::nextDraft ()
	{
		return ;
	}

	///@brief End the current Draft phase
	void Game::endDraft ()
	{
		return ;
	}

	///@brief Initialize the Planification phase during which players choose the cards they will try to build
	void Game::initPlanification ()
	{
		return ;
	}

	///@brief Manage the phase of production for all player and one resource
	///@param toProduceResource Pointer which designate the type of resource currently to produce
	void Game::produceResource (Resource* toProduceResource)
	{
		return ;
	}

	///@brief Send a resource earned by a player to let him use it
	///@param resource Pointer which designate the type of resource sent
	///@param player Pointer which designate the player who receive the resource
	void Game::sendResourceToPlayer (Resource* resource, Player* player) const
	{
		return ;
	}

	///@brief Debug method to check the state of the instance of Game
	///@return String explaining the state of Game
	std::string Game::toString () const
	{
		return "";
	}

	/// @brief Distributes the empires to the players
	void Game::initPlayers (std::vector<EmpireCard*> empires)
	{
		return ;
	}

	/// @brief Ends the game, counts every player's victory points and compares them tp give a podium
	void Game::endGame ()
	{
		return ;
	}
}