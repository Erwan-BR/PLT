#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Game.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(firstGameTest)
{
  {
	
	// Creation of the instance of Game
    Game* myFirstGame = new Game();

    // Testing void-void methods
	myFirstGame->initGame();
	myFirstGame->initCards();
	myFirstGame->startGame();
	myFirstGame->nextPhase();
	myFirstGame->newTurn();
	myFirstGame->initDraft();
	myFirstGame->nextDraft();
	myFirstGame->endDraft();
	myFirstGame->initPlanification();
    myFirstGame->endGame();


	ResourceType toProduceResource = ENERGY;
	ResourceType resource = MATERIAL;
	Player* firstPlayer = new Player();
    myFirstGame->produceResource (toProduceResource);

	std::vector<EmpireCard*> empires = myFirstGame->initEmpire();
    myFirstGame->initPlayers (empires);


	// Test toString()
	std::string gameToString = myFirstGame->toString();
	BOOST_CHECK_EQUAL(gameToString, "");

	// Test produceResource(ResourceType toProduce)
	ResourceType firstResource = SCIENCE;
	myFirstGame->produceResource(firstResource);

	// Test sendResourceToPlayer
	ResourceType secondResource = GOLD;
	myFirstGame->produceResource(secondResource);

	// Delete pointers
	delete myFirstGame;
	delete firstPlayer;
  }

  {
	// Test Full constructor

	// Creation Arguments
	Player* firstPlayer = new Player();
	Player* secondPlayer = new Player();
	Player* thirdPlayer = new Player();
	std::vector<Player*> players;
	players.push_back(firstPlayer);
	players.push_back(secondPlayer);
	players.push_back(thirdPlayer);

	// Call Constructor
	Game* mySecondGame = new Game(players);

	// Delete pointers
	delete mySecondGame;
	delete firstPlayer;
	delete secondPlayer;
	delete thirdPlayer;
	
  }
}

/* vim: set sw=2 sts=2 et : */

