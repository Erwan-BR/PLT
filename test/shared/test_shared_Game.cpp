#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Game.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(firstGameTest)
{
  {
	// Creation Arguments
	sf::Texture* profilePicture;
	std::vector<Player*> players;
	Player* firstPlayer = new Player("Maxime", 1, profilePicture);
	players.push_back(firstPlayer);
	Player* secondPlayer = new Player("Adrien", 2, profilePicture);
	players.push_back(secondPlayer);
	
	// Creation of the instance of Game
    Game* myFirstGame = new Game(players);
	myFirstGame->initGame();

    Game* myFirstGameTest = new Game(players, true);

	myFirstGameTest->getTurn();
	myFirstGameTest->getPhase();
	myFirstGameTest->getResourceProducing();

	// Delete pointers
	delete myFirstGame;
	delete myFirstGameTest;

  }
}

BOOST_AUTO_TEST_CASE(secondGameTest)
{
  {
	// Creation Arguments
	sf::Texture* profilePicture;
	std::vector<Player*> players;
	Player* firstPlayer = new Player("Maxime", 1, profilePicture);
	players.push_back(firstPlayer);
	Player* secondPlayer = new Player("Adrien", 2, profilePicture);
	players.push_back(secondPlayer);


	// Call Constructor
	Game* mySecondGame = new Game(players);
	
	mySecondGame->initGame();
	BOOST_CHECK_EQUAL(mySecondGame->getPhase(), GamePhase::DRAFT);
	
	//turn 1
	BOOST_CHECK_EQUAL(mySecondGame->getTurn(), 1);

	for (int draftTurn = 0 ; draftTurn < 7; draftTurn++)
	{
		mySecondGame->getPlayers()[0]->chooseDraftCard(0);
		mySecondGame->getPlayers()[1]->chooseDraftCard(0);
		mySecondGame->nextDraft();
		if (6 != draftTurn)
		{
			BOOST_CHECK_EQUAL(mySecondGame->getPhase(), GamePhase::DRAFT);
		}
	}
	BOOST_CHECK_EQUAL(mySecondGame->getPhase(), GamePhase::PLANIFICATION);

	for (int discardTurn = 0 ; discardTurn < 7; discardTurn++)
	{
		mySecondGame->getPlayers()[0]->discardCard(0,true);
		mySecondGame->getPlayers()[1]->discardCard(0,true);
	}
	mySecondGame->endPlanification();
	BOOST_CHECK_EQUAL(mySecondGame->getPhase(), GamePhase::PRODUCTION);
	
    // Elements to create for testing the full constructor.
    ResourceToPay* firstResourceToPay = new ResourceToPay{ResourceType::MATERIAL, false};


    ResourceToProduce* firstResourceToProduce = new ResourceToProduce{ResourceType::MATERIAL, 20, state::CardType::VEHICLE};
    ResourceToProduce* secondResourceToProduce = new ResourceToProduce{ResourceType::SCIENCE, 30, state::CardType::PROJECT};
    ResourceToProduce* thirdResourceToProduce = new ResourceToProduce{ResourceType::ENERGY, 20, state::CardType::NONETYPE};

    // Elements to pass to the constructor.
    std::string name = "myName";

    std::vector<ResourceToProduce*> productionGain;
    productionGain.push_back(firstResourceToProduce);
    productionGain.push_back(secondResourceToProduce);
    productionGain.push_back(thirdResourceToProduce);

    sf::Texture* design = new sf::Texture();

    CardVictoryPoint* victoryPoints = new CardVictoryPoint{1, state::CardType::NONETYPE};

    CardType type = CardType::PROJECT;

    int numberOfCopies = 2;

    std::vector<ResourceToPay*> costToBuild;
    costToBuild.push_back(firstResourceToPay);

    std::vector<ResourceType> instantGain;
    instantGain.push_back(ResourceType::GOLD);
    instantGain.push_back(ResourceType::SCIENCE);

    ResourceType discardGain = ResourceType::FINANCIER;

	// Vector created to check the current resource produced.
	const std::vector<ResourceType> resourceProduced = {ResourceType::ENERGY, ResourceType::SCIENCE, ResourceType::GOLD, ResourceType::EXPLORATION, ResourceType::KRYSTALLIUM};

	for (int i=0;i<5;i++)
	{
		BOOST_CHECK_EQUAL(mySecondGame->getResourceProducing(), resourceProduced[i]);
		mySecondGame->nextProduction();
	}

    // Testing the full constructor of DevelopmentCard.
    DevelopmentCard* mySecondDevelopmentCard = new DevelopmentCard(name, productionGain, design, victoryPoints, type, numberOfCopies, costToBuild, instantGain, discardGain);
	

	//turn 2
	BOOST_CHECK_EQUAL(mySecondGame->getTurn(), 2);
	for (int draftTurn = 0 ; draftTurn < 7; draftTurn++)
	{
		mySecondGame->getPlayers()[0]->chooseDraftCard(0);
		mySecondGame->getPlayers()[1]->chooseDraftCard(0);
		mySecondGame->nextDraft();
		if (6 != draftTurn)
		{
			BOOST_CHECK_EQUAL(mySecondGame->getPhase(), GamePhase::DRAFT);
		}
	}
	BOOST_CHECK_EQUAL(mySecondGame->getPhase(), GamePhase::PLANIFICATION);

	for (int discardTurn = 0 ; discardTurn < 6; discardTurn++)
	{
		mySecondGame->getPlayers()[0]->discardCard(0,true);
		mySecondGame->getPlayers()[1]->discardCard(0,true);
	}
	
	mySecondGame->getPlayers()[0]->keepCard(0);
	mySecondGame->getPlayers()[1]->keepCard(0);
	mySecondGame->getPlayers()[0]->addResource(state::ResourceType::MATERIAL, 0);

	mySecondGame->endPlanification();
	BOOST_CHECK_EQUAL(mySecondGame->getPhase(), GamePhase::PRODUCTION);

	for (int i=0;i<5;i++)
	{
		BOOST_CHECK_EQUAL(mySecondGame->getResourceProducing(), resourceProduced[i]);
		mySecondGame->nextProduction();
	}

	//turn 3
	BOOST_CHECK_EQUAL(mySecondGame->getTurn(), 3);
	for (int draftTurn = 0 ; draftTurn < 7; draftTurn++)
	{
		mySecondGame->getPlayers()[0]->chooseDraftCard(0);
		mySecondGame->getPlayers()[1]->chooseDraftCard(0);
		mySecondGame->nextDraft();
		if (6 != draftTurn)
		{
			BOOST_CHECK_EQUAL(mySecondGame->getPhase(), GamePhase::DRAFT);
		}
	}
	BOOST_CHECK_EQUAL(mySecondGame->getPhase(), GamePhase::PLANIFICATION);

	for (int discardTurn = 0 ; discardTurn < 7; discardTurn++)
	{
		mySecondGame->getPlayers()[0]->discardCard(0,true);
		mySecondGame->getPlayers()[1]->discardCard(0,true);
	}
	mySecondGame->endPlanification();
	BOOST_CHECK_EQUAL(mySecondGame->getPhase(), GamePhase::PRODUCTION);
	for (int i=0;i<5;i++)
	{
		BOOST_CHECK_EQUAL(mySecondGame->getResourceProducing(), resourceProduced[i]);
		mySecondGame->nextProduction();
	}

	
	//turn 4
	BOOST_CHECK_EQUAL(mySecondGame->getTurn(), 4);
	for (int draftTurn = 0 ; draftTurn < 7; draftTurn++)
	{
		mySecondGame->getPlayers()[0]->chooseDraftCard(0);
		mySecondGame->getPlayers()[1]->chooseDraftCard(0);
		mySecondGame->nextDraft();
		if (6 != draftTurn)
		{
			BOOST_CHECK_EQUAL(mySecondGame->getPhase(), GamePhase::DRAFT);
		}
	}
	BOOST_CHECK_EQUAL(mySecondGame->getPhase(), GamePhase::PLANIFICATION);

	for (int discardTurn = 0 ; discardTurn < 7; discardTurn++)
	{
		mySecondGame->getPlayers()[0]->discardCard(0,true);
		mySecondGame->getPlayers()[1]->discardCard(0,true);
	}
	mySecondGame->endPlanification();
	BOOST_CHECK_EQUAL(mySecondGame->getPhase(), GamePhase::PRODUCTION);

	for (int i=0;i<5;i++)
	{
		BOOST_CHECK_EQUAL(mySecondGame->getResourceProducing(), resourceProduced[i]);
		mySecondGame->nextProduction();
	}


	// Delete pointers
	delete mySecondGame;
	
  }
}

/* vim: set sw=2 sts=2 et : */

