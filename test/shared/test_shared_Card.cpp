#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Card.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(firstCardTest)
{
  {
    // Testing the empty constructor of Card
    Card* myFirstCard = new Card();

    // Retrieving values from the getters for testing empty construct
    std::string firstReturnedName = myFirstCard->getName();
    const std::vector<ResourceToProduce*>& firstReturnedResourceToProduce = myFirstCard->getProductionGain();
    const sf::Texture& firstReturnedDesign = myFirstCard->getDesign();
    const std::vector<CardVictoryPoint*>& firstReturnedVictoryPoints = myFirstCard->getVictoryPoints();

    // Empty vectors to compare
    const std::vector<ResourceToProduce*>& expectedFirstResourceToProduce = {};
    const std::vector<CardVictoryPoint*>& expectedFirstCardVictoryPoint = {};

    // Testing the getters
    BOOST_CHECK_EQUAL(firstReturnedName, "");
    BOOST_CHECK(firstReturnedResourceToProduce == expectedFirstResourceToProduce);
    // BOOST_CHECK_EQUAL(firstReturnedDesign, sf::Texture());
    BOOST_CHECK(firstReturnedVictoryPoints == expectedFirstCardVictoryPoint);
    //Initialising the ressource produced by the card and the victory points
    Resource* firstResource = new Resource{SCIENCE, sf::Texture()};
    std::vector<CardVictoryPoint*> victoryPoints;
    const std::vector<ResourceToProduce*>&  firstResourceToProduce = {new ResourceToProduce{firstResource, 2, state::CardType::VEHICLE}};

    // Testing the setters
    myFirstCard->setName("name");
    myFirstCard->setProductionGain(firstResourceToProduce);
    myFirstCard->setDesign(sf::Texture());
    myFirstCard->setVictoryPoints(victoryPoints);

    // Retrieving the values after setting them
    std::string returnedName = myFirstCard->getName();
    const std::vector<ResourceToProduce*>& firstReturnedResourceToProduce2 = myFirstCard->getProductionGain();
    const sf::Texture& returnedDesign = myFirstCard->getDesign();
    const std::vector<CardVictoryPoint*>& firstReturnedVictoryPoints2 = myFirstCard->getVictoryPoints();

    // Checking
    BOOST_CHECK_EQUAL(returnedName, "name");
    BOOST_CHECK(firstReturnedResourceToProduce2 == firstResourceToProduce);
    // //BOOST_CHECK_EQUAL(firstReturnedDesign, sf::Texture());
    BOOST_CHECK(firstReturnedVictoryPoints2 == victoryPoints);

    // Testing the destructor
    delete firstResource;
    delete myFirstCard;
  }

  {
    // Testing the explicit constructor
    Resource* firstResource = new Resource{SCIENCE, sf::Texture()};
    std::vector<CardVictoryPoint*> victoryPoints;
    const std::vector<ResourceToProduce*>&  secondResourceToProduce = {new ResourceToProduce{firstResource, 2, state::CardType::VEHICLE}};


    Card* mySecondCard = new Card("name",secondResourceToProduce,sf::Texture(),victoryPoints);

    // Retrieving values from the getters for testing construct
    std::string returnedName = mySecondCard->getName();
    const std::vector<ResourceToProduce*>& returnedResourceToProduce = mySecondCard->getProductionGain();
    const sf::Texture& returnedDesign = mySecondCard->getDesign();
    const std::vector<CardVictoryPoint*>& returnedVictoryPoints = mySecondCard->getVictoryPoints();

    // Vectors to compare
    const std::vector<ResourceToProduce*>& expectedResourceToProduce = {};
    const std::vector<CardVictoryPoint*>& expectedCardVictoryPoint = {};

    // Checking
    BOOST_CHECK_EQUAL(returnedName, "name");
    BOOST_CHECK(returnedResourceToProduce == secondResourceToProduce);
    // //BOOST_CHECK_EQUAL(returnedDesign, sf::Texture());
    BOOST_CHECK(returnedVictoryPoints == victoryPoints);

    delete mySecondCard;

  }
}

/* vim: set sw=2 sts=2 et : */
