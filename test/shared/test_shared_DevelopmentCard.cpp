#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/DevelopmentCard.h"
#include "../../src/shared/state/Resource.h"

#include <string>

using namespace ::state;

BOOST_AUTO_TEST_CASE(firstDevelopmentCardTest)
{
  {
    DevelopmentCard* myFirstDevelopmentCard = new DevelopmentCard();

    /*
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

    Resource* resource = new Resource();

    // Calling method of DevelopmentCard.
    myFirstDevelopmentCard->addResource(resource);
    bool resourceAddable = myFirstDevelopmentCard->isResourceAddable(resource);
    std::string cardToString = myFirstDevelopmentCard->toString();

    // Checking output of DevelopmentCard method.
    BOOST_CHECK_EQUAL(resourceAddable, false);
    BOOST_CHECK_EQUAL(cardToString, "");

    delete myFirstDevelopmentCard;
  }
  {
    DevelopmentCard* mySecondDevelopmentCard = new DevelopmentCard();

    /*
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
  }
}

/* vim: set sw=2 sts=2 et : */
