#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/DevelopmentCard.h"

#include <string>

using namespace ::state;

BOOST_AUTO_TEST_CASE(test_ConversionJSON)
{
    // Testing JSON conversion with some empty tables (Card is Reseau de transport)
    // Constructing a card that will be export to JSON
    DevelopmentCard* cardToExport = new DevelopmentCard ("Reseau de transport",{},"../resources/img/Cards/Development_Cards/reseau_de_transport.png",new CardVictoryPoint{1, CardType::VEHICLE},CardType::STRUCTURE,2,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}},{},ResourceType::MATERIAL);

    Json::Value jsonContent = cardToExport->toJSON();

    // Only for debug, the JSON appears in a log file (PLT/build/test/Testing/Temporary/LastTest.log)
    /*
    for (int i = 0; i < 7; i++)
    {
        std::cout << std::endl;
    }
    
    std::cout << jsonContent;
    
    for (int i = 0; i < 7; i++)
    {
        std::cout << std::endl;
    }
    */

    DevelopmentCard* cardFromImport = new DevelopmentCard(jsonContent);

    BOOST_CHECK_EQUAL(cardFromImport->getName(), "Reseau de transport");

    std::vector<ResourceToProduce*> importedCardProduction = cardFromImport->getProductionGain();

    BOOST_CHECK_EQUAL(importedCardProduction.size(), 0);

    BOOST_CHECK_EQUAL(cardFromImport->getRelativePathToTexture(), "../resources/img/Cards/Development_Cards/reseau_de_transport.png");

    CardVictoryPoint* cardPoints = cardFromImport->getVictoryPoints();

    BOOST_CHECK_EQUAL(cardPoints->numberOfPoints, 1);
    BOOST_CHECK_EQUAL(cardPoints->cardOrResourceType, CardType::VEHICLE);

    BOOST_CHECK_EQUAL(cardFromImport->getDiscardGain(), ResourceType::MATERIAL);
    BOOST_CHECK_EQUAL(cardFromImport->getType(), CardType::STRUCTURE);

    std::vector<ResourceToPay*> cardCostToBuild = cardFromImport->getCostToBuild();

    BOOST_CHECK_EQUAL(cardCostToBuild[0]->type, ResourceType::MATERIAL);
    BOOST_CHECK_EQUAL(cardCostToBuild[0]->isPaid, false);

    BOOST_CHECK_EQUAL(cardCostToBuild[1]->type, ResourceType::MATERIAL);
    BOOST_CHECK_EQUAL(cardCostToBuild[1]->isPaid, false);

    BOOST_CHECK_EQUAL(cardCostToBuild[2]->type, ResourceType::MATERIAL);
    BOOST_CHECK_EQUAL(cardCostToBuild[2]->isPaid, false);

    delete cardToExport;
    delete cardFromImport;

    // Testing JSON conversion with every no empty table. (Card is sattelites)
    {
    // Constructing a card that will be export to JSON
    DevelopmentCard* cardToExport = new DevelopmentCard ("Satellites",{new ResourceToProduce{ResourceType::EXPLORATION, 2, CardType::NONETYPE}},"../resources/img/Cards/Development_Cards/satellites.png",new CardVictoryPoint{3, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{ResourceType::COLONEL},ResourceType::EXPLORATION);    

    Json::Value jsonContent = cardToExport->toJSON();

    /*for (int i = 0; i < 7; i++)
    {
        std::cout << std::endl;
    }
    std::cout << jsonContent;
    for (int i = 0; i < 7; i++)
    {
        std::cout << std::endl;
    }*/

    DevelopmentCard* cardFromImport = new DevelopmentCard(jsonContent);

    BOOST_CHECK_EQUAL(cardFromImport->getName(), "Satellites");

    std::vector<ResourceToProduce*> importedCardProduction = cardFromImport->getProductionGain();

    BOOST_CHECK_EQUAL(importedCardProduction[0]->cardType, CardType::NONETYPE);
    BOOST_CHECK_EQUAL(importedCardProduction[0]->quantity, 2);
    BOOST_CHECK_EQUAL(importedCardProduction[0]->type, ResourceType::EXPLORATION);

    BOOST_CHECK_EQUAL(cardFromImport->getRelativePathToTexture(), "../resources/img/Cards/Development_Cards/satellites.png");

    CardVictoryPoint* cardPoints = cardFromImport->getVictoryPoints();

    BOOST_CHECK_EQUAL(cardPoints->numberOfPoints, 3);
    BOOST_CHECK_EQUAL(cardPoints->cardOrResourceType, CardType::NONETYPE);

    BOOST_CHECK_EQUAL(cardFromImport->getDiscardGain(), ResourceType::EXPLORATION);
    BOOST_CHECK_EQUAL(cardFromImport->getType(), CardType::RESEARCH);

    std::vector<ResourceToPay*> cardCostToBuild = cardFromImport->getCostToBuild();

    BOOST_CHECK_EQUAL(cardCostToBuild[0]->type, ResourceType::ENERGY);
    BOOST_CHECK_EQUAL(cardCostToBuild[0]->isPaid, false);

    BOOST_CHECK_EQUAL(cardCostToBuild[1]->type, ResourceType::ENERGY);
    BOOST_CHECK_EQUAL(cardCostToBuild[1]->isPaid, false);

    BOOST_CHECK_EQUAL(cardCostToBuild[2]->type, ResourceType::SCIENCE);
    BOOST_CHECK_EQUAL(cardCostToBuild[2]->isPaid, false);

    BOOST_CHECK_EQUAL(cardCostToBuild[3]->type, ResourceType::SCIENCE);
    BOOST_CHECK_EQUAL(cardCostToBuild[3]->isPaid, false);

    BOOST_CHECK_EQUAL(cardCostToBuild[4]->type, ResourceType::SCIENCE);
    BOOST_CHECK_EQUAL(cardCostToBuild[4]->isPaid, false);

    BOOST_CHECK_EQUAL(cardCostToBuild[5]->type, ResourceType::SCIENCE);
    BOOST_CHECK_EQUAL(cardCostToBuild[5]->isPaid, false);
    }
}

BOOST_AUTO_TEST_CASE(test_ConstructorAndMethods)
{
    DevelopmentCard* testDevCard = new DevelopmentCard ("Satellites",{new ResourceToProduce{ResourceType::EXPLORATION, 2, CardType::NONETYPE}},new CardVictoryPoint{3, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{ResourceType::COLONEL},ResourceType::EXPLORATION);    
    
    bool addable = testDevCard->isResourceAddable(ResourceType::ENERGY);
    BOOST_CHECK_EQUAL(addable, true);

    bool building = testDevCard->addResource(ResourceType::ENERGY);
    (void) testDevCard->addResource(ResourceType::ENERGY);
    (void) testDevCard->addResource(ResourceType::SCIENCE);
    (void) testDevCard->addResource(ResourceType::SCIENCE);
    building = testDevCard->addResource(ResourceType::SCIENCE);
    BOOST_CHECK_EQUAL(building, false);
    BOOST_CHECK_EQUAL(testDevCard->getQuantityResourcesMissing(),1);

    building = testDevCard->addResource(ResourceType::SCIENCE);
    BOOST_CHECK_EQUAL(building, true);
    BOOST_CHECK_EQUAL(testDevCard->getQuantityResourcesMissing(),0);
    BOOST_CHECK_EQUAL(building, true);

    building = testDevCard->addResource(ResourceType::SCIENCE);// For this is paid
    addable = testDevCard->isResourceAddable(ResourceType::ENERGY);// For this is paid


    std::vector<ResourceType> gainInstant = testDevCard->getInstantGain();
    BOOST_CHECK_EQUAL(gainInstant[0], ResourceType::COLONEL);
    BOOST_CHECK_EQUAL(gainInstant.size(), 1);
}

/* vim: set sw=2 sts=2 et : */
