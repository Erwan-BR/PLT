#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Card.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(firstCardTest)
{
  {
    // Testing the empty constructor of Card
    Card* myFirstCard = new Card();

    /*
    The following lines were used when dia2code automatically generated setters and getters. As we no longer wish to do this, we'll comment on these lines.
    These lines can be uncommented if required.



    // Retrieving values from the getters for testing empty construct
    std::string firstReturnedName = myFirstCard->getName();
    const std::vector<ResourceToProduce*>& firstReturnedResourceToProduce = myFirstCard->getProductionGain();
    const sf::Texture& firstReturnedDesign = myFirstCard->getDesign();
    const CardVictoryPoint*& firstReturnedVictoryPoints = myFirstCard->getVictoryPoints();

    // Empty vectors to compare
    const std::vector<ResourceToProduce*>& expectedFirstResourceToProduce = {};
    const CardVictoryPoint*& expectedFirstCardVictoryPoint = CardVictoryPoint{10, 10};

    // Testing the getters
    BOOST_CHECK_EQUAL(firstReturnedName, "");
    BOOST_CHECK(firstReturnedResourceToProduce == expectedFirstResourceToProduce);
    // BOOST_CHECK_EQUAL(firstReturnedDesign, sf::Texture());
    BOOST_CHECK(firstReturnedVictoryPoints == expectedFirstCardVictoryPoint);
    
    // Initialising the ressource produced by the card and the victory points
    const CardVictoryPoint*& victoryPoints = new CardVictoryPoint{};
    const std::vector<ResourceToProduce*>&  firstResourceToProduce = {new ResourceToProduce{ResourceType::SCIENCE, 2, state::CardType::VEHICLE}};

    // Testing the setters
    myFirstCard->setName("name");
    myFirstCard->setProductionGain(firstResourceToProduce);
    myFirstCard->setDesign(sf::Texture());
    myFirstCard->setVictoryPoints(victoryPoints);

    // Retrieving the values after setting them
    std::string returnedName = myFirstCard->getName();
    const std::vector<ResourceToProduce*>& firstReturnedResourceToProduce2 = myFirstCard->getProductionGain();
    const sf::Texture& returnedDesign = myFirstCard->getDesign();
    const CardVictoryPoint*& firstReturnedVictoryPoints2 = myFirstCard->getVictoryPoints();

    // Checking
    BOOST_CHECK_EQUAL(returnedName, "name");
    BOOST_CHECK(firstReturnedResourceToProduce2 == firstResourceToProduce);
    // BOOST_CHECK_EQUAL(firstReturnedDesign, sf::Texture());
    BOOST_CHECK(firstReturnedVictoryPoints2 == victoryPoints);

    */

    // Testing the destructor
    delete myFirstCard;
  }

  {
    // Testing the explicit constructor
    std::string name = "Name";
    CardVictoryPoint* victoryPoints;
    sf::Texture design = sf::Texture();
    const std::vector<ResourceToProduce*>&  secondResourceToProduce = {new ResourceToProduce{ResourceType::GOLD, 2, state::CardType::VEHICLE}};

    Card* mySecondCard = new Card(name, secondResourceToProduce, design, victoryPoints);

    /*
    The following lines were used when dia2code automatically generated setters and getters. As we no longer wish to do this, we'll comment on these lines.
    These lines can be uncommented if required.

    

    // Retrieving values from the getters for testing construct
    std::string returnedName = mySecondCard->getName();
    const std::vector<ResourceToProduce*>& returnedResourceToProduce = mySecondCard->getProductionGain();
    const sf::Texture& returnedDesign = mySecondCard->getDesign();
    const CardVictoryPoint*& returnedVictoryPoints = mySecondCard->getVictoryPoints();

    // Vectors to compare
    const std::vector<ResourceToProduce*>& expectedResourceToProduce = {};
    const std::vector<CardVictoryPoint*>& expectedCardVictoryPoint = {};

    // Checking
    BOOST_CHECK_EQUAL(returnedName, "name");
    BOOST_CHECK(returnedResourceToProduce == secondResourceToProduce);
    // BOOST_CHECK_EQUAL(returnedDesign, sf::Texture());
    BOOST_CHECK(returnedVictoryPoints == victoryPoints);

    */

    // Testing the destructor
    delete mySecondCard;
  }
}

/* vim: set sw=2 sts=2 et : */
