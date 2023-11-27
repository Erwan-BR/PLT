#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Game.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(firstGameTest)
{
  {
	
	// Creation of the instance of Game
    Game* myFirstGame = new Game();

	// Test toString()
	std::string gameToString = myFirstGame->toString();
	//BOOST_CHECK(gameToString == "");

	myFirstGame->getTurn();
	myFirstGame->getPhase();
	myFirstGame->getResourceProducing();

	// Delete pointers
	delete myFirstGame;

  }
}
BOOST_AUTO_TEST_CASE(secondGameTest)
{
  {
	// Test Full constructor

	// Creation Arguments
	sf::Texture profilePicture;
	std::vector<Player*> players;
	Player* firstPlayer = new Player("Maxime", 1, profilePicture);
	players.push_back(firstPlayer);
	Player* secondPlayer = new Player("Adrien", 2, profilePicture);
	players.push_back(secondPlayer);




	// Call Constructor
	Game* mySecondGame = new Game(players);
	
	mySecondGame->initGame();
	
	for(int index1 = 1; index1 < 4; index1++)
	{
		std::cout << mySecondGame->getTurn();
		for (int index2 = 0 ; index2 < 7; index2++)
		{
			mySecondGame->getPlayers()[0]->chooseDraftCard(mySecondGame->getPlayers()[0]->getDraftingCards()[0]);
			mySecondGame->getPlayers()[1]->chooseDraftCard(mySecondGame->getPlayers()[1]->getDraftingCards()[0]);
			mySecondGame->nextDraft();
		}
	}
	
    // Elements to create for testing the full constructor.
    ResourceToPay* firstResourceToPay = new ResourceToPay{ResourceType::FINANCIER, true};
    ResourceToPay* secondResourceToPay = new ResourceToPay{ResourceType::MATERIAL, true};
    ResourceToPay* thirdResourceToPay = new ResourceToPay{ResourceType::GOLD, true};
    ResourceToPay* fourthResourceToPay = new ResourceToPay{ResourceType::KRYSTALLIUM, true};

    ResourceToProduce* firstResourceToProduce = new ResourceToProduce{ResourceType::MATERIAL, 2, state::CardType::VEHICLE};
    ResourceToProduce* secondResourceToProduce = new ResourceToProduce{ResourceType::SCIENCE, 3, state::CardType::PROJECT};

    // Elements to pass to the constructor.
    std::string name = "myName";

    std::vector<ResourceToProduce*> productionGain;
    productionGain.push_back(firstResourceToProduce);
    productionGain.push_back(secondResourceToProduce);

    sf::Texture design = sf::Texture();

    CardVictoryPoint* victoryPoints = new CardVictoryPoint{1, 5};

    CardType type = CardType::PROJECT;

    int numberOfCopies = 2;

    std::vector<ResourceToPay*> costToBuild;
    costToBuild.push_back(firstResourceToPay);
    costToBuild.push_back(secondResourceToPay);
    costToBuild.push_back(thirdResourceToPay);
    costToBuild.push_back(fourthResourceToPay);

    std::vector<ResourceType> instantGain;
    instantGain.push_back(ResourceType::GOLD);
    instantGain.push_back(ResourceType::SCIENCE);

    ResourceType discardGain = ResourceType::FINANCIER;

    // Testing the full constructor of DevelopmentCard.
    DevelopmentCard* mySecondDevelopmentCard = new DevelopmentCard(name, productionGain, design, victoryPoints, type, numberOfCopies, costToBuild, instantGain, discardGain);
	mySecondGame->getPlayers()[1]->construct(mySecondDevelopmentCard);
	for (int index2 = 0 ; index2 < 8; index2++)
	{
		mySecondGame->getPlayers()[0]->chooseDraftCard(mySecondGame->getPlayers()[0]->getDraftingCards()[0]);
		mySecondGame->getPlayers()[1]->chooseDraftCard(mySecondGame->getPlayers()[1]->getDraftingCards()[0]);
		mySecondGame->nextDraft();
	}
	mySecondGame->getPlayers()[0]->construct(mySecondDevelopmentCard);

	// Delete pointers
	delete mySecondGame;
	//delete firstPlayer;
	//delete secondPlayer;
	
  }
}

/* vim: set sw=2 sts=2 et : */

