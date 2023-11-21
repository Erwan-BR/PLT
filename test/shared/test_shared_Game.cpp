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
	myFirstGame->nextPhase();
	myFirstGame->newTurn();
	myFirstGame->initDraft();
	//myFirstGame->nextDraft();	
	myFirstGame->endDraft();

	myFirstGame->initPlanification();
    myFirstGame->endGame();

	// Test toString()
	std::string gameToString = myFirstGame->toString();
	BOOST_CHECK_EQUAL(gameToString,"");

/*
	ResourceType toProduceResource = ENERGY;
	Player* firstPlayer = new Player();
    myFirstGame->produceResource (toProduceResource);

	std::vector<EmpireCard*> empires = myFirstGame->initEmpire();
    myFirstGame->initPlayers (empires);





	// Test produceResource(ResourceType toProduce)
	ResourceType firstResource = SCIENCE;
	myFirstGame->produceResource(firstResource);

	// Test sendResourceToPlayer
	ResourceType secondResource = GOLD;
	myFirstGame->produceResource(secondResource);

	// Delete pointers
	delete firstPlayer;*/
	delete myFirstGame;

  }

  {
	// Test Full constructor

	// Creation Arguments
	std::vector<Player*> players;
	Player* firstPlayer = new Player();
	players.push_back(firstPlayer);
	Player* secondPlayer = new Player();
	players.push_back(secondPlayer);




	// Call Constructor
	Game* mySecondGame = new Game(players);
	
	mySecondGame->createCards();

	mySecondGame->initGame();
	mySecondGame->initCards();
	mySecondGame->startGame();
	mySecondGame->nextPhase();

	mySecondGame->newTurn();
	mySecondGame->newTurn();
	mySecondGame->newTurn();
	mySecondGame->newTurn();
	mySecondGame->newTurn();

	mySecondGame->produceResource(GOLD);

	mySecondGame->initDraft();

	
	mySecondGame->endDraft();

	mySecondGame->initPlanification();
    mySecondGame->endGame();
	mySecondGame->nextDraft();
	// Delete pointers
	delete mySecondGame;
	delete firstPlayer;
	delete secondPlayer;
	
  }
}

/* vim: set sw=2 sts=2 et : */

