#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Card.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(test_ConversionJSON)
{
    // Constructing a card that will be export to JSON
    Card* cardToExport = new Card("Marc", {new ResourceToProduce{ResourceType::MATERIAL,1, CardType::NONETYPE}, new ResourceToProduce{ResourceType::SCIENCE,1, CardType::NONETYPE}}, "../resources/img/background.png", new CardVictoryPoint{1, CardType::VEHICLE});

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

    std::vector<ResourceToProduce*> secondCardProduction = cardFromImport->getProductionGain();

    BOOST_CHECK_EQUAL(secondCardProduction[0]->type, ResourceType::MATERIAL);
    BOOST_CHECK_EQUAL(secondCardProduction[0]->quantity, 1);
    BOOST_CHECK_EQUAL(secondCardProduction[0]->cardType, CardType::NONETYPE);

    BOOST_CHECK_EQUAL(secondCardProduction[1]->type, ResourceType::SCIENCE);
    BOOST_CHECK_EQUAL(secondCardProduction[1]->quantity, 1);
    BOOST_CHECK_EQUAL(secondCardProduction[1]->cardType, CardType::NONETYPE);

    BOOST_CHECK_EQUAL(cardFromImport->getRelativePathToTexture(), "../resources/img/background.png");

    CardVictoryPoint* cardPoints = cardFromImport->getVictoryPoints();

    BOOST_CHECK_EQUAL(cardPoints->numberOfPoints, 1);
    BOOST_CHECK_EQUAL(cardPoints->cardOrResourceType, CardType::VEHICLE);

    // Free memory.
    delete cardPoints;
    delete cardToExport;
    delete cardFromImport;
}

BOOST_AUTO_TEST_CASE(test_Constructor)
{
    sf::Texture* design = new sf::Texture();
    Card* testCard = new Card("Marc", {new ResourceToProduce{ResourceType::MATERIAL,1, CardType::NONETYPE}, new ResourceToProduce{ResourceType::SCIENCE,1, CardType::NONETYPE}}, design, new CardVictoryPoint{1, CardType::VEHICLE});
    
    BOOST_CHECK_EQUAL(testCard->getName(), "Marc");

    std::vector<ResourceToProduce*> secondCardProduction = testCard->getProductionGain();

    BOOST_CHECK_EQUAL(secondCardProduction[0]->type, ResourceType::MATERIAL);
    BOOST_CHECK_EQUAL(secondCardProduction[0]->quantity, 1);
    BOOST_CHECK_EQUAL(secondCardProduction[0]->cardType, CardType::NONETYPE);

    BOOST_CHECK_EQUAL(secondCardProduction[1]->type, ResourceType::SCIENCE);
    BOOST_CHECK_EQUAL(secondCardProduction[1]->quantity, 1);
    BOOST_CHECK_EQUAL(secondCardProduction[1]->cardType, CardType::NONETYPE);

    CardVictoryPoint* cardPoints = testCard->getVictoryPoints();

    BOOST_CHECK_EQUAL(cardPoints->numberOfPoints, 1);
    BOOST_CHECK_EQUAL(cardPoints->cardOrResourceType, CardType::VEHICLE);

    (void) testCard->getDesign();
    delete testCard;
    delete design;
    delete cardPoints;
}

/* vim: set sw=2 sts=2 et : */
