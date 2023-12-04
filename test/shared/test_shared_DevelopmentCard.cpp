#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/DevelopmentCard.h"

#include <string>

using namespace ::state;

BOOST_AUTO_TEST_CASE(firstDevelopmentCardTest)
{
  {
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
  }
}

/* vim: set sw=2 sts=2 et : */
