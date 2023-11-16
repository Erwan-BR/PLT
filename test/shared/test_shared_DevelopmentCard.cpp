#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/DevelopmentCard.h"
#include "../../src/shared/state/Resource.h"

#include <string>

using namespace ::state;

BOOST_AUTO_TEST_CASE(firstDevelopmentCardTest)
{
  {
    // Testing the empty constructor of DevelopmentCard 
    //DevelopmentCard* myFirstDevelopmentCard = new DevelopmentCard();

    /* Adding some of those lines if somes getters are done.
    // Checking default value given by the empty constructor.
    // Checking values from the empty Card constructor.
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getName(), "");
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getProductionGain(), {});
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getDesign(), sf::Texture());
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getVictoryPoints(), {});

    // Checking default value given by the DevelopmentCard constructor.
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getInstantGain(), {});
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getType(), CardType::NONETYPE);
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getNumberOfCopies(), 0);
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getCostToBuild(), {});
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->InstantGain(), {});
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getCostToBuild(), {});
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getDiscardGain(), new Resource());
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getProductionGain(), {});
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getQuantityResourceMissing(), -1);
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getIsPaid(), false);
    */
/*
    // Creation of a resource to test methods.
    Resource* resource = new Resource();

    // Calling methods of DevelopmentCard.
    myFirstDevelopmentCard->addResource(resource);
    bool resourceAddable = myFirstDevelopmentCard->isResourceAddable(resource);
    std::string cardToString = myFirstDevelopmentCard->toString();

    // Checking output of DevelopmentCard method.
    BOOST_CHECK_EQUAL(resourceAddable, false);
    BOOST_CHECK_EQUAL(cardToString, "");

    // Delete pointers that won't be used anymore.
    delete myFirstDevelopmentCard;
    delete resource;
  }
  
  {
    // Elements to create for testing the full constructor.
    Resource* firstResource = new Resource{SCIENCE, sf::Texture()};
    Resource* secondResource = new Resource{GOLD, sf::Texture()};

    ResourceToPay* firstResourceToPay = new ResourceToPay{ResourceType::FINANCIER, false};
    ResourceToPay* secondResourceToPay = new ResourceToPay{ResourceType::COLONEL, false};
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

    CardVictoryPoint* victoryPoints = new CardVictoryPoint();

    state::CardType type = PROJECT;
    
    int numberOfCopies = 2;

    std::vector<ResourceToPay*> costToBuild;
    costToBuild.push_back(firstResourceToPay);
    costToBuild.push_back(secondResourceToPay);

    std::vector<Resource*> instantGain;
    instantGain.push_back(firstResource);
    instantGain.push_back(secondResource);

    Resource* discardGain = firstResource;
    
    // Testing the full constructor of DevelopmentCard.
    DevelopmentCard* mySecondDevelopmentCard = new DevelopmentCard(name, productionGain, design, victoryPoints, type, numberOfCopies, costToBuild, instantGain, discardGain);

    /* Adding some of those lines if somes getters are done.
    // Checking default value given by the empty constructor.

    // Checking values from the empty Card constructor.
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getName(), "");
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getProductionGain(), {});
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getDesign(), sf::Texture());
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getVictoryPoints(), {});

    // Checking default value given by the DevelopmentCard constructor.
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getInstantGain(), {});
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getType(), CardType::NONETYPE);
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getNumberOfCopies(), 0);
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getCostToBuild(), {});
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->InstantGain(), {});
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getCostToBuild(), {});
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getDiscardGain(), new Resource());
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getProductionGain(), {});
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getQuantityResourceMissing(), -1);
    BOOST_CHECK_EQUAL(myFirstDevelopmentCard->getIsPaid(), false);
    */
/*
    // Delete pointers that won't be used anymore.
    delete firstResource;
    delete secondResource;

    delete firstResourceToPay;
    delete secondResourceToPay;
    delete thirdResourceToPay;
    delete fourthResourceToPay;

    delete firstResourceToProduce;
    delete secondResourceToProduce;

    delete mySecondDevelopmentCard;
    */
  }
}

/* vim: set sw=2 sts=2 et : */
