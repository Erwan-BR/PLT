#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/DevelopmentCard.h"

#include <string>

using namespace ::state;

BOOST_AUTO_TEST_CASE(firstDevelopmentCardTest)
{
  // Testing JSON conversion with some empty tables (Card is Reseau de transport)
  {
    // Constructing a card that will be export to JSON

    DevelopmentCard* cardToExport = new DevelopmentCard ("Reseau de transport",{},"../resources/img/Cards/Development_Cards/reseau_de_transport.png",new CardVictoryPoint{1, CardType::VEHICLE},CardType::STRUCTURE,2,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}},{},ResourceType::MATERIAL);
    
    Json::Value jsonContent = cardToExport->toJSON();

    /*
    for (int i = 0; i < 7; i++)
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
  }

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


  /*{
    // Testing the empty constructor of DevelopmentCard 
    DevelopmentCard* myFirstDevelopmentCard = new DevelopmentCard();

    // We call toString but we don't want to test it.
    (void)myFirstDevelopmentCard->toString();

    // Delete pointers that won't be used anymore.
    myFirstDevelopmentCard->~DevelopmentCard();
  }

  {
    // Elements to create for testing the full constructor.
    ResourceToPay* firstResourceToPay = new ResourceToPay{ResourceType::FINANCIER, false};
    ResourceToPay* secondResourceToPay = new ResourceToPay{ResourceType::MATERIAL, false};
    ResourceToPay* thirdResourceToPay = new ResourceToPay{ResourceType::GOLD, false};
    ResourceToPay* fourthResourceToPay = new ResourceToPay{ResourceType::KRYSTALLIUM, false};

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

    // Testing if some materials can be added.
    bool isColonelAddable = mySecondDevelopmentCard->isResourceAddable(ResourceType::COLONEL);
    bool isKrystalliumAddable = mySecondDevelopmentCard->isResourceAddable(ResourceType::KRYSTALLIUM);

    BOOST_CHECK_EQUAL(isColonelAddable, false);
    BOOST_CHECK_EQUAL(isKrystalliumAddable, true);

    // Adding some resources to the card (resources that can be added)
    bool isCardFinishedFirst = mySecondDevelopmentCard->addKrystallium(ResourceType::GOLD);
    bool isCardFinishedSecond = mySecondDevelopmentCard->addResource(ResourceType::MATERIAL);
    bool isCardFinishedThird = mySecondDevelopmentCard->addResource(ResourceType::KRYSTALLIUM);

    BOOST_CHECK_EQUAL(isCardFinishedFirst, false);
    BOOST_CHECK_EQUAL(isCardFinishedSecond, false);
    BOOST_CHECK_EQUAL(isCardFinishedThird, false);

    // Checking if krystallium is addable. Should return false because krystallium doesn't replace FINANCIER / COLONEL.
    bool isKrystalliumAddableSecond = mySecondDevelopmentCard->isResourceAddable(ResourceType::KRYSTALLIUM);
    BOOST_CHECK_EQUAL(isKrystalliumAddableSecond, false);

    // Adding krystallium to complete the card.
    bool isCardFinishedFourth = mySecondDevelopmentCard->addResource(ResourceType::FINANCIER);
    BOOST_CHECK_EQUAL(isCardFinishedFourth, true);

    // Checking if a resource can be added once the card is completed.
    bool isMaterialAddable = mySecondDevelopmentCard->isResourceAddable(ResourceType::MATERIAL);
    BOOST_CHECK_EQUAL(isMaterialAddable, false);

    // Calling the toString method.
    (void)mySecondDevelopmentCard->toString();

    //Testing the getters:
    (void)mySecondDevelopmentCard->getCostToBuild();
    (void)mySecondDevelopmentCard->getType();
    (void)mySecondDevelopmentCard->getDiscardGain();

    // Delete pointers that won't be used anymore.
    mySecondDevelopmentCard->~DevelopmentCard();
  }*/
}

/* vim: set sw=2 sts=2 et : */
