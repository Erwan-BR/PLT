#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/CreateJSONFormatStructures.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(test_ResourceToPay_Conversion)
{
    constants::resourcePayPtr resourceToPay = std::make_shared<ResourceToPay>();
    resourceToPay->isPaid = false;
    resourceToPay->type = ResourceType::COLONEL;

    CreateJSONFormatStructures* jsonConversion = new CreateJSONFormatStructures();

    Json::Value jsonResource = jsonConversion->jsonOfResourceToPay(*resourceToPay);

    constants::resourcePayPtr resourceToPayCopy = jsonConversion->resourceToPayFromJSON(jsonResource);

    BOOST_CHECK_EQUAL(resourceToPayCopy->type, ResourceType::COLONEL);
    BOOST_CHECK_EQUAL(resourceToPayCopy->isPaid, false);
}

BOOST_AUTO_TEST_CASE(test_ResourceToProduce_Conversion)
{
    constants::resourceProdPtr resourceToProduce = std::make_shared<ResourceToProduce>();
    resourceToProduce->type = ResourceType::GOLD;
    resourceToProduce->quantity = 10;
    resourceToProduce->cardType = CardType::PROJECT;

    CreateJSONFormatStructures* jsonConversion = new CreateJSONFormatStructures();

    Json::Value jsonResource = jsonConversion->jsonOfResourceToProduce(*resourceToProduce);

    constants::resourceProdPtr resourceToProduceCopy = jsonConversion->resourceToProduceFromJSON(jsonResource);

    BOOST_CHECK_EQUAL(resourceToProduceCopy->type, ResourceType::GOLD);
    BOOST_CHECK_EQUAL(resourceToProduceCopy->quantity, 10);
    BOOST_CHECK_EQUAL(resourceToProduceCopy->cardType, CardType::PROJECT);
}

BOOST_AUTO_TEST_CASE(test_CardVictoryPoint_Conversion)
{
    constants::victoryPointsPtr cardVictoryPoint = std::make_shared<CardVictoryPoint>();
    cardVictoryPoint->numberOfPoints = 10;
    cardVictoryPoint->cardOrResourceType = static_cast<int>(ResourceType::FINANCIER);

    CreateJSONFormatStructures* jsonConversion = new CreateJSONFormatStructures();

    Json::Value jsonResource = jsonConversion->jsonOfCardVictoryPoint(*cardVictoryPoint);

    constants::victoryPointsPtr cardVictoryPointCopy = jsonConversion->cardVictoryPointFromJSON(jsonResource);

    BOOST_CHECK_EQUAL(cardVictoryPointCopy->numberOfPoints, 10);
    BOOST_CHECK_EQUAL(cardVictoryPointCopy->cardOrResourceType, (int)(ResourceType::FINANCIER));
}

/* vim: set sw=2 sts=2 et : */
