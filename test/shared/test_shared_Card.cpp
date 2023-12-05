#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Card.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(firstCardTest)
{
  {
    // Testing the empty constructor of Card
    Card* myFirstCard = new Card();

    // Testing the destructor
    myFirstCard->~Card();
  }

  {
    // Testing the explicit constructor
    std::string name = "Name";
    CardVictoryPoint* victoryPoints = new CardVictoryPoint();
    sf::Texture design = sf::Texture();
    const std::vector<ResourceToProduce*>&  secondResourceToProduce = {new ResourceToProduce{ResourceType::GOLD, 2, state::CardType::VEHICLE}};

    Card* mySecondCard = new Card(name, secondResourceToProduce, design, victoryPoints);

    //Testing the getters:
    (void)mySecondCard->getDesign();
    (void)mySecondCard->getName();
    (void)mySecondCard->getProductionGain();
    (void)mySecondCard->getVictoryPoints();

    // Testing the destructor
    mySecondCard->~Card();
  }
}

/* vim: set sw=2 sts=2 et : */
