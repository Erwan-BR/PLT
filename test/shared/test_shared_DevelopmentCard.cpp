#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/DevelopmentCard.h"

#include <string>

using namespace ::state;

BOOST_AUTO_TEST_CASE(test_ConversionJSON)
{
    // Testing JSON conversion with some empty tables (Card is Reseau de transport)
    // Constructing a card that will be export to JSON
    constants::victoryPointsPtr victoryPoints = std::make_shared<CardVictoryPoint>();
    victoryPoints->numberOfPoints = 1;
    victoryPoints->cardOrResourceType = CardType::VEHICLE;

    constants::resourcePayPtr resourceToPay1 = std::make_shared<ResourceToPay>();
    resourceToPay1->isPaid = false;
    resourceToPay1->type = ResourceType::MATERIAL;

    constants::resourcePayPtr resourceToPay2 = std::make_shared<ResourceToPay>();
    resourceToPay2->isPaid = false;
    resourceToPay2->type = ResourceType::MATERIAL;

    constants::resourcePayPtr resourceToPay3 = std::make_shared<ResourceToPay>();
    resourceToPay3->isPaid = false;
    resourceToPay3->type = ResourceType::MATERIAL;
    
    constants::resourcePayList resourceToPayList = {resourceToPay1, resourceToPay2, resourceToPay3};

    DevelopmentCard* cardToExport = new DevelopmentCard ("Reseau de transport",{},"../resources/img/Cards/Development_Cards/reseau_de_transport.png",victoryPoints,CardType::STRUCTURE,2,resourceToPayList,{},ResourceType::MATERIAL);

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
    

    DevelopmentCard* cardFromImport = new DevelopmentCard(jsonContent);

    BOOST_CHECK_EQUAL(cardFromImport->getName(), "Reseau de transport");

    constants::resourceProdList importedCardProduction = cardFromImport->getProductionGain();

    BOOST_CHECK_EQUAL(importedCardProduction.size(), 0);

    BOOST_CHECK_EQUAL(cardFromImport->getRelativePathToTexture(), "../resources/img/Cards/Development_Cards/reseau_de_transport.png");

    constants::victoryPointsPtr cardPoints = cardFromImport->getVictoryPoints();

    BOOST_CHECK_EQUAL(cardPoints->numberOfPoints, 1);
    BOOST_CHECK_EQUAL(cardPoints->cardOrResourceType, CardType::VEHICLE);

    BOOST_CHECK_EQUAL(cardFromImport->getDiscardGain(), ResourceType::MATERIAL);
    BOOST_CHECK_EQUAL(cardFromImport->getType(), CardType::STRUCTURE);

    constants::resourcePayList cardCostToBuild = cardFromImport->getCostToBuild();

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
    constants::resourceProdPtr resourceProduced = std::make_shared<ResourceToProduce>();
    resourceProduced->type = ResourceType::EXPLORATION;
    resourceProduced->quantity = 2;
    resourceProduced->cardType = CardType::NONETYPE;

    constants::resourceProdList resourceProducedList = {resourceProduced};

    constants::victoryPointsPtr victoryPoints = std::make_shared<CardVictoryPoint>();
    victoryPoints->numberOfPoints = 3;
    victoryPoints->cardOrResourceType = CardType::NONETYPE;
    
    const std::vector<ResourceType> toPayResources = {ResourceType::ENERGY, ResourceType::ENERGY, ResourceType::SCIENCE, ResourceType::SCIENCE, ResourceType::SCIENCE, ResourceType::SCIENCE};
    constants::resourcePayList resourceToPayList = {};
    
    for (size_t index = 0; toPayResources.size() > index ; index++)
    {
        constants::resourcePayPtr resourceToPay = std::make_shared<ResourceToPay>();
        resourceToPay->isPaid = false;
        resourceToPay->type = toPayResources[index];

        resourceToPayList.push_back(resourceToPay);
    }

    DevelopmentCard* cardToExport = new DevelopmentCard ("Satellites", resourceProducedList, "../resources/img/Cards/Development_Cards/satellites.png", victoryPoints, CardType::RESEARCH, 1, resourceToPayList, {ResourceType::COLONEL}, ResourceType::EXPLORATION);    

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

    constants::resourceProdList importedCardProduction = cardFromImport->getProductionGain();

    BOOST_CHECK_EQUAL(importedCardProduction[0]->cardType, CardType::NONETYPE);
    BOOST_CHECK_EQUAL(importedCardProduction[0]->quantity, 2);
    BOOST_CHECK_EQUAL(importedCardProduction[0]->type, ResourceType::EXPLORATION);

    BOOST_CHECK_EQUAL(cardFromImport->getRelativePathToTexture(), "../resources/img/Cards/Development_Cards/satellites.png");

    constants::victoryPointsPtr cardPoints = cardFromImport->getVictoryPoints();

    BOOST_CHECK_EQUAL(cardPoints->numberOfPoints, 3);
    BOOST_CHECK_EQUAL(cardPoints->cardOrResourceType, CardType::NONETYPE);

    BOOST_CHECK_EQUAL(cardFromImport->getDiscardGain(), ResourceType::EXPLORATION);
    BOOST_CHECK_EQUAL(cardFromImport->getType(), CardType::RESEARCH);

    constants::resourcePayList cardCostToBuild = cardFromImport->getCostToBuild();

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
    constants::resourceProdPtr resourceProduced = std::make_shared<ResourceToProduce>();
    resourceProduced->type = ResourceType::EXPLORATION;
    resourceProduced->quantity = 2;
    resourceProduced->cardType = CardType::NONETYPE;

    constants::resourceProdList resourceProducedList = {resourceProduced};

    constants::victoryPointsPtr victoryPoints = std::make_shared<CardVictoryPoint>();
    victoryPoints->numberOfPoints = 3;
    victoryPoints->cardOrResourceType = CardType::NONETYPE;
    
    const std::vector<ResourceType> toPayResources = {ResourceType::ENERGY, ResourceType::ENERGY, ResourceType::SCIENCE, ResourceType::SCIENCE, ResourceType::SCIENCE, ResourceType::SCIENCE};
    constants::resourcePayList resourceToPayList = {};
    
    for (size_t index = 0; toPayResources.size() > index ; index++)
    {
        constants::resourcePayPtr resourceToPay = std::make_shared<ResourceToPay>();
        resourceToPay->isPaid = false;
        resourceToPay->type = toPayResources[index];

        resourceToPayList.push_back(resourceToPay);
    }

    DevelopmentCard* testDevCard = new DevelopmentCard ("Satellites", resourceProducedList, victoryPoints, CardType::RESEARCH, 1, resourceToPayList, {ResourceType::COLONEL}, ResourceType::EXPLORATION);    

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
