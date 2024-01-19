#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Card.h"
#include "../../src/constants/constants/CustomTypes.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(test_ConversionJSON)
{
    // Constructing a card that will be export to JSON
    constants::resourceProdPtr resourceProd1 = std::make_shared<ResourceToProduce>();
    resourceProd1->cardType = CardType::NONETYPE;
    resourceProd1->type = ResourceType::MATERIAL;
    resourceProd1->quantity = 1;

    constants::resourceProdPtr resourceProd2 = std::make_shared<ResourceToProduce>();
    resourceProd2->cardType = CardType::NONETYPE;
    resourceProd2->type = ResourceType::SCIENCE;
    resourceProd2->quantity = 1;

    constants::resourceProdList resourceProdVect = {resourceProd1, resourceProd2};
    constants::victoryPointsPtr victoryPoints = std::make_shared<CardVictoryPoint>();
    victoryPoints->numberOfPoints = 1;
    victoryPoints->cardOrResourceType = static_cast<int>(CardType::VEHICLE);

    Card* cardToExport = new Card("Marc", resourceProdVect, "../resources/img/background.png", victoryPoints);

    Json::Value jsonContent = cardToExport->toJSON();

    // Only for debug, the JSON appears in a log file (PLT/build/test/Testing/Temporary/LastTest.log)
    /*for (int i = 0; i < 7; i++)
    {
        std::cout << std::endl;
    }
    std::cout << jsonContent;
    for (int i = 0; i < 7; i++)
    {
        std::cout << std::endl;
    }*/

    // Importing a card from a JSON.
    Card* cardFromImport = new Card(jsonContent);

    // Following lines will check all possible attributes from the card.
    BOOST_CHECK_EQUAL(cardFromImport->getName(), "Marc");

    constants::resourceProdList secondCardProduction = cardFromImport->getProductionGain();

    BOOST_CHECK_EQUAL(secondCardProduction[0]->type, ResourceType::MATERIAL);
    BOOST_CHECK_EQUAL(secondCardProduction[0]->quantity, 1);
    BOOST_CHECK_EQUAL(secondCardProduction[0]->cardType, CardType::NONETYPE);

    BOOST_CHECK_EQUAL(secondCardProduction[1]->type, ResourceType::SCIENCE);
    BOOST_CHECK_EQUAL(secondCardProduction[1]->quantity, 1);
    BOOST_CHECK_EQUAL(secondCardProduction[1]->cardType, CardType::NONETYPE);

    BOOST_CHECK_EQUAL(cardFromImport->getRelativePathToTexture(), "../resources/img/background.png");

    constants::victoryPointsPtr cardPoints = cardFromImport->getVictoryPoints();

    BOOST_CHECK_EQUAL(cardPoints->numberOfPoints, 1);
    BOOST_CHECK_EQUAL(cardPoints->cardOrResourceType, CardType::VEHICLE);

    // Free memory.
    delete cardToExport;
    delete cardFromImport;
}

BOOST_AUTO_TEST_CASE(test_Constructor)
{
    constants::resourceProdPtr resourceProd1 = std::make_shared<ResourceToProduce>();
    resourceProd1->cardType = CardType::NONETYPE;
    resourceProd1->type = ResourceType::MATERIAL;
    resourceProd1->quantity = 1;

    constants::resourceProdPtr resourceProd2 = std::make_shared<ResourceToProduce>();
    resourceProd2->cardType = CardType::NONETYPE;
    resourceProd2->type = ResourceType::SCIENCE;
    resourceProd2->quantity = 1;

    constants::resourceProdList resourceProdVect = {resourceProd1, resourceProd2};
    constants::victoryPointsPtr victoryPoints = std::make_shared<CardVictoryPoint>();
    victoryPoints->numberOfPoints = 1;
    victoryPoints->cardOrResourceType = static_cast<int>(CardType::VEHICLE);

    Card* testCard = new Card("Marc", resourceProdVect, victoryPoints);
    
    BOOST_CHECK_EQUAL(testCard->getName(), "Marc");

    constants::resourceProdList secondCardProduction = testCard->getProductionGain();

    BOOST_CHECK_EQUAL(secondCardProduction[0]->type, ResourceType::MATERIAL);
    BOOST_CHECK_EQUAL(secondCardProduction[0]->quantity, 1);
    BOOST_CHECK_EQUAL(secondCardProduction[0]->cardType, CardType::NONETYPE);

    BOOST_CHECK_EQUAL(secondCardProduction[1]->type, ResourceType::SCIENCE);
    BOOST_CHECK_EQUAL(secondCardProduction[1]->quantity, 1);
    BOOST_CHECK_EQUAL(secondCardProduction[1]->cardType, CardType::NONETYPE);

    constants::victoryPointsPtr cardPoints = testCard->getVictoryPoints();

    BOOST_CHECK_EQUAL(cardPoints->numberOfPoints, 1);
    BOOST_CHECK_EQUAL(cardPoints->cardOrResourceType, CardType::VEHICLE);

    delete testCard;
}

/* vim: set sw=2 sts=2 et : */
