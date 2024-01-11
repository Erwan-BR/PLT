#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Game.h"
#include "../../src/shared/state/CreateAllCards.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(test_ConversionJSON)
{
    std::shared_ptr<Player> firstPlayerInGame = std::make_shared<Player>("Erwan", 10);
    std::shared_ptr<Player> secondPlayerInGame = std::make_shared<Player>("Adrien", 20);
	std::vector<std::shared_ptr<Player>> playersInGame = {firstPlayerInGame, secondPlayerInGame};

    // Creating a testing game. It won't shuffle cards so it will be easy to know if exportations worked correctly.
    std::shared_ptr<Game> gameToExport = std::make_shared<Game>(playersInGame, true);
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

	std::shared_ptr<Game> gameFromImport = std::make_shared<Game>(gameJSON);

	BOOST_CHECK_EQUAL(gameFromImport->getPlayers().size(), 2);
	BOOST_CHECK_EQUAL(gameFromImport->getPlayers()[0]->getName(), "Erwan");
	BOOST_CHECK_EQUAL(gameFromImport->getPlayers()[1]->getName(), "Adrien");
    BOOST_CHECK_EQUAL(gameFromImport->getResourceProducing(), ResourceType::MATERIAL);
    BOOST_CHECK_EQUAL(gameFromImport->getPhase(), GamePhase::DRAFT);
    BOOST_CHECK_EQUAL(gameFromImport->getTurn(), 1);
}

BOOST_AUTO_TEST_CASE(firstGameTest)
{
    // Creation Arguments
    std::shared_ptr<Player> firstPlayer = std::make_shared<Player>("Maxime", 1);
    std::shared_ptr<Player> secondPlayer = std::make_shared<Player>("Adrien", 2);

    std::vector<std::shared_ptr<Player>> players = {firstPlayer, secondPlayer};

    std::shared_ptr<Game> gameAnotherConstructor = std::make_shared<Game>(players, true);
    gameAnotherConstructor->initGame();
    //turn 1
    BOOST_CHECK_EQUAL(gameAnotherConstructor->getTurn(), 1);

    for (int draftTurn = 0 ; draftTurn < 7; draftTurn++)
    {
        gameAnotherConstructor->getPlayers()[0]->chooseDraftCard(0);
        gameAnotherConstructor->getPlayers()[1]->chooseDraftCard(0);
        gameAnotherConstructor->nextDraft();
        if (6 != draftTurn)
        {
            BOOST_CHECK_EQUAL(gameAnotherConstructor->getPhase(), GamePhase::DRAFT);
        }
    }
    BOOST_CHECK_EQUAL(gameAnotherConstructor->getPhase(), GamePhase::PLANIFICATION);

    for (int discardTurn = 0 ; discardTurn < 7; discardTurn++)
    {
        gameAnotherConstructor->getPlayers()[0]->discardCard(0,true);
        gameAnotherConstructor->getPlayers()[1]->discardCard(0,true);
    }
    gameAnotherConstructor->endPlanification();
    BOOST_CHECK_EQUAL(gameAnotherConstructor->getPhase(), GamePhase::PRODUCTION);
    
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
        BOOST_CHECK_EQUAL(gameAnotherConstructor->getResourceProducing(), resourceProduced[i]);
        gameAnotherConstructor->nextProduction();
    }
    (void) gameAnotherConstructor->getWinners();
}

BOOST_AUTO_TEST_CASE(secondGameTest)
{
    // Creation Arguments
    std::shared_ptr<Player> firstPlayer = std::make_shared<Player>("Maxime", 1);
    std::shared_ptr<Player> secondPlayer = std::make_shared<Player>("Adrien", 2);

    std::vector<std::shared_ptr<Player>> players = {firstPlayer, secondPlayer};

    // Call Constructor
    std::shared_ptr<Game> mySecondGame = std::make_shared<Game>(players);
    
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
}

/* vim: set sw=2 sts=2 et : */
