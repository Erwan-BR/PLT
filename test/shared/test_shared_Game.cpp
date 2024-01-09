#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Game.h"
#include "../../src/shared/state/CreateAllCards.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(test_ConversionJSON)
{
    Player* firstPlayerInGame = new Player("Erwan", 10);
    Player* secondPlayerInGame = new Player("Adrien", 20);
	std::vector<Player*> playersInGame = {firstPlayerInGame, secondPlayerInGame};

    // Creating a testing game. It won't shuffle cards so it will be easy to know if exportations worked correctly.
    Game* gameToExport = new Game(playersInGame, true);
    gameToExport->initGame();

    Json::Value gameJSON = gameToExport->toJSON();
    
    // Only for debug, the JSON appears in a log file (PLT/build/test/Testing/Temporary/LastTest.log)
    /*
	for (int i = 0; i < 7; i++)
    {
        std::cout << std::endl;
    }
    
    std::cout << gameJSON;
    
    for (int i = 0; i < 7; i++)
    {
        std::cout << std::endl;
    }
	*/

	Game* gameFromImport = new Game(gameJSON);

	BOOST_CHECK_EQUAL(gameFromImport->getPlayers().size(), 2);
	BOOST_CHECK_EQUAL(gameFromImport->getPlayers()[0]->getName(), "Erwan");
	BOOST_CHECK_EQUAL(gameFromImport->getPlayers()[1]->getName(), "Adrien");
    BOOST_CHECK_EQUAL(gameFromImport->getResourceProducing(), ResourceType::MATERIAL);
    BOOST_CHECK_EQUAL(gameFromImport->getPhase(), GamePhase::DRAFT);
    BOOST_CHECK_EQUAL(gameFromImport->getTurn(), 1);

    // Delete pointers
    delete gameToExport;
    delete gameFromImport;
}

BOOST_AUTO_TEST_CASE(firstGameTest)
{
    // Creation Arguments
    Player* firstPlayer = new Player("Maxime", 1);
    Player* secondPlayer = new Player("Adrien", 2);

    std::vector<Player*> players = {firstPlayer, secondPlayer};

    Game* gameAnotherConstructor = new Game(players, true);

    delete gameAnotherConstructor;
}

BOOST_AUTO_TEST_CASE(secondGameTest)
{
    // Creation Arguments
    Player* firstPlayer = new Player("Maxime", 1);
    Player* secondPlayer = new Player("Adrien", 2);

    // Call Constructor
    Game* mySecondGame = new Game({firstPlayer, secondPlayer});
    
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

    std::vector<ResourceToProduce*> productionGain;
    productionGain.push_back(firstResourceToProduce);
    productionGain.push_back(secondResourceToProduce);
    productionGain.push_back(thirdResourceToProduce);

    std::vector<ResourceToPay*> costToBuild;
    costToBuild.push_back(firstResourceToPay);

    std::vector<ResourceType> instantGain;
    instantGain.push_back(ResourceType::GOLD);
    instantGain.push_back(ResourceType::SCIENCE);

    // Vector created to check the current resource produced.
    const std::vector<ResourceType> resourceProduced = {ResourceType::MATERIAL,  ResourceType::ENERGY, ResourceType::SCIENCE, ResourceType::GOLD, ResourceType::EXPLORATION, ResourceType::KRYSTALLIUM};

    for (int i=0;i<5;i++)
    {
        BOOST_CHECK_EQUAL(mySecondGame->getResourceProducing(), resourceProduced[i]);
        mySecondGame->nextProduction();
    }

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

    (void)mySecondGame->getWinners();

    for (int i=0;i<5;i++)
    {
        BOOST_CHECK_EQUAL(mySecondGame->getResourceProducing(), resourceProduced[i]);
        mySecondGame->nextProduction();
    }

    BOOST_CHECK_EQUAL(mySecondGame->getPhase(), GamePhase::FINISHED);
    (void)mySecondGame->getWinners();

    // Delete pointers
    delete mySecondGame;
}

/* vim: set sw=2 sts=2 et : */
