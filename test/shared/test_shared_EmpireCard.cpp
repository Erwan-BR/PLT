#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/EmpireCard.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(firstEmpireCardTest)
{
  {
    // Testing the empty constructor of EmpireCard 
    EmpireCard* myFirstEmpireCard = new EmpireCard();

    /*Adding some of those lines if somes getters are done.
    // Checking default value given by the empty constructor.
    // Checking values from the empty Card constructor.
    BOOST_CHECK_EQUAL(myFirstEmpireCard->getName(), "");
    BOOST_CHECK_EQUAL(myFirstEmpireCard->getProductionGain(), {});
    BOOST_CHECK_EQUAL(myFirstEmpireCard->getDesign(), sf::Texture());
    BOOST_CHECK_EQUAL(myFirstEmpireCard->getVictoryPoints(), {});

    // Checking default value given by the EmpireCard constructor.
    BOOST_CHECK_EQUAL(myFirstEmpireCard->getProductionGainAdvanced(), {});
    BOOST_CHECK_EQUAL(myFirstEmpireCard->getVictoryPointsAdvanced(), {});
    BOOST_CHECK_EQUAL(myFirstEmpireCard->getEmpire(), AFRICA);
    */
    
    // Calling methods of EmpireCard.
    std::string EmpireCardToString = myFirstEmpireCard->toString();

    // Checking output of EmpireCard method.
    BOOST_CHECK_EQUAL(EmpireCardToString, "");

    // Delete pointers that won't be used anymore.
    delete myFirstEmpireCard;
  }
  
  {
    // Elements to create for testing the full constructor.
    Resource* firstResource = new Resource{SCIENCE, sf::Texture()};
    Resource* secondResource = new Resource{GOLD, sf::Texture()};
    Resource* thirdResource = new Resource{EXPLORATION, sf::Texture()};
    Resource* fourthResource = new Resource{COLONEL, sf::Texture()};

    ResourceToPay* firstResourceToPay = new ResourceToPay{firstResource, false};
    ResourceToPay* secondResourceToPay = new ResourceToPay{secondResource, false};
    ResourceToPay* thirdResourceToPay = new ResourceToPay{thirdResource, false};
    ResourceToPay* fourthResourceToPay = new ResourceToPay{fourthResource, false};

    ResourceToProduce* firstResourceToProduce = new ResourceToProduce{fourthResource, 2, state::CardType::VEHICLE};
    ResourceToProduce* secondResourceToProduce = new ResourceToProduce{firstResource, 3, state::CardType::PROJECT};

    // Elements to pass to the constructor.
    std::string name = "myName";

    std::vector<ResourceToProduce*> productionGain;
    productionGain.push_back(firstResourceToProduce);
    productionGain.push_back(secondResourceToProduce);

    sf::Texture design = sf::Texture();

    std::vector<CardVictoryPoint*> victoryPoints;

    std::vector<ResourceToProduce*> productionGainAdvanced;
    productionGainAdvanced.push_back(firstResourceToProduce);
    productionGainAdvanced.push_back(secondResourceToProduce);

    std::vector<CardVictoryPoint*> victoryPointsAdvanced;

    EmpireLand empire = AZTEC;
    
    // Testing the full constructor of EmpireCard.
    EmpireCard* mySecondEmpireCard = new EmpireCard(name, productionGain, design, victoryPoints, productionGainAdvanced, victoryPointsAdvanced, empire);

    /*Adding some of those lines if somes getters are done.
    // Checking default value given by the empty constructor.
    // Checking values from the empty Card constructor.
    BOOST_CHECK_EQUAL(myFirstEmpireCard->getName(), "");
    BOOST_CHECK_EQUAL(myFirstEmpireCard->getProductionGain(), {});
    BOOST_CHECK_EQUAL(myFirstEmpireCard->getDesign(), sf::Texture());
    BOOST_CHECK_EQUAL(myFirstEmpireCard->getVictoryPoints(), {});

    // Checking default value given by the DevelopmentCard constructor.
    BOOST_CHECK_EQUAL(myFirstEmpireCard->getProductionGainAdvanced(), {});
    BOOST_CHECK_EQUAL(myFirstEmpireCard->getVictoryPointsAdvanced(), {});
    BOOST_CHECK_EQUAL(myFirstEmpireCard->getEmpire(), AFRICA);
    */

    // Delete pointers that won't be used anymore.
    delete firstResource;
    delete secondResource;
    delete thirdResource;
    delete fourthResource;

    delete firstResourceToPay;
    delete secondResourceToPay;
    delete thirdResourceToPay;
    delete fourthResourceToPay;

    delete firstResourceToProduce;
    delete secondResourceToProduce;

    delete mySecondEmpireCard;
  }
}

/* vim: set sw=2 sts=2 et : */
