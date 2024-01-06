#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/CreateJSONFormatStructures.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(test_ResourceToPay_Conversion)
{
    struct ResourceToPay* resourceToPay = new ResourceToPay{ResourceType::COLONEL, false};

    CreateJSONFormatStructures* jsonConversion = new CreateJSONFormatStructures();

    Json::Value jsonResource = jsonConversion->jsonOfResourceToPay(*resourceToPay);

    struct ResourceToPay* resourceToPayCopy = jsonConversion->resourceToPayFromJSON(jsonResource);

    BOOST_CHECK_EQUAL(resourceToPayCopy->type, ResourceType::COLONEL);
    BOOST_CHECK_EQUAL(resourceToPayCopy->isPaid, false);
}

BOOST_AUTO_TEST_CASE(test_ResourceToProduce_Conversion)
{
    struct ResourceToProduce* resourceToProduce = new ResourceToProduce{ResourceType::GOLD, 10, CardType::PROJECT};

    CreateJSONFormatStructures* jsonConversion = new CreateJSONFormatStructures();

    Json::Value jsonResource = jsonConversion->jsonOfResourceToProduce(*resourceToProduce);

    struct ResourceToProduce* resourceToProduceCopy = jsonConversion->resourceToProduceFromJSON(jsonResource);

    BOOST_CHECK_EQUAL(resourceToProduceCopy->type, ResourceType::GOLD);
    BOOST_CHECK_EQUAL(resourceToProduceCopy->quantity, 10);
    BOOST_CHECK_EQUAL(resourceToProduceCopy->cardType, CardType::PROJECT);
}

BOOST_AUTO_TEST_CASE(test_CardVictoryPoint_Conversion)
{
    struct CardVictoryPoint* cardVictoryPoint = new CardVictoryPoint{10, (int)(ResourceType::FINANCIER)};

    CreateJSONFormatStructures* jsonConversion = new CreateJSONFormatStructures();

    Json::Value jsonResource = jsonConversion->jsonOfCardVictoryPoint(*cardVictoryPoint);

    struct CardVictoryPoint* cardVictoryPointCopy = jsonConversion->cardVictoryPointFromJSON(jsonResource);

    BOOST_CHECK_EQUAL(cardVictoryPointCopy->numberOfPoints, 10);
    BOOST_CHECK_EQUAL(cardVictoryPointCopy->cardOrResourceType, (int)(ResourceType::FINANCIER));
}

/* vim: set sw=2 sts=2 et : */
