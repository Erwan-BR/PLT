#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Player.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(firstPlayerTest)
{
  {
    // Testing the empty contructor of Player
    //Player* myFirstPlayer = new Player();
    
    /*Adding some of those lines if some getters are done.
    // Checking default value given by the empty constructor.
    // Checking default values given by the Player constructor.
    BOOST_CHECK_EQUAL(myFirstPlayer->getName(), "");
    BOOST_CHECK_EQUAL(myFirstPlayer->getId(), -1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getEmpire(), ); //To Complete
    BOOST_CHECK_EQUAL(myFirstPlayer->getToBuildCards(), {});
    BOOST_CHECK_EQUAL(myFirstPlayer->getBuiltCards(), {});
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftingCards(), {});
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftCards(), {});
    BOOST_CHECK_EQUAL(myFirstPlayer->getState(), PENDING);
    BOOST_CHECK_EQUAL(myFirstPlayer->getFinancierTokensUnit(), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getColoneTokensUnit(), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getKrystalliumTokensUnit(), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources(), {});
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourceInEmpireUnit(), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getProfilePicture(), ); //To Complete
    */
/*
    // Creation of multiple elements to test the methods.
    DevelopmentCard* cardTest = new DevelopmentCard();
    Resource* resourceTest = new Resource();

    // Calling methods of Player.
    myFirstPlayer->construct(cardTest);
    myFirstPlayer->addResource(resourceTest, cardTest);
    myFirstPlayer->discardCard(cardTest);
    int production = myFirstPlayer->computeProduction(GOLD);
    int victoryPoints = myFirstPlayer->computeVictoryPoint();
    myFirstPlayer->sendResourceToEmpire(resourceTest);
    myFirstPlayer->convertToKrystallium();
    myFirstPlayer->chooseDraftCard(cardTest);
    bool colonelChoosed = myFirstPlayer->chooseColonelToken();
    std::string PlayerToString = myFirstPlayer->toString();

    // Checking output of Player methods.
    BOOST_CHECK_EQUAL(production, 0);
    BOOST_CHECK_EQUAL(victoryPoints, 0);
    BOOST_CHECK_EQUAL(colonelChoosed, false);
    BOOST_CHECK_EQUAL(PlayerToString, "");

    // Delete pointers that won't be used anymore.
    delete myFirstPlayer;
    delete cardTest;
    delete resourceTest;
  }

  {
  ;
  */
  }
  
}

/* vim: set sw=2 sts=2 et : */
