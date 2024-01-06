#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/EmpireCard.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(firstEmpireCardTest)
{
  {
    // Testing the empty constructor of EmpireCard 
    EmpireCard* myFirstEmpireCard = new EmpireCard();
    
    // Calling methods of EmpireCard.
    std::string EmpireCardToString = myFirstEmpireCard->toString();

    // Checking output of EmpireCard method.
    BOOST_CHECK_EQUAL(EmpireCardToString, "");

    // Delete pointers that won't be used anymore.
    myFirstEmpireCard->~EmpireCard();
  }
  
  {
    // Elements to create for testing the full constructor.
    ResourceToProduce* firstResourceToProduce = new ResourceToProduce{ResourceType::KRYSTALLIUM, 2, state::CardType::VEHICLE};
    ResourceToProduce* secondResourceToProduce = new ResourceToProduce{ResourceType::GOLD, 3, state::CardType::PROJECT};

    ResourceToProduce* firstAdvancedResourceToProduce = new ResourceToProduce{ResourceType::MATERIAL, 1, state::CardType::NONETYPE};
    ResourceToProduce* secondAdvancedResourceToProduce = new ResourceToProduce{ResourceType::ENERGY, 3, state::CardType::PROJECT};

    // Elements to pass to the constructor.
    std::string name = "myName";

    std::vector<ResourceToProduce*> productionGain;
    productionGain.push_back(firstResourceToProduce);
    productionGain.push_back(secondResourceToProduce);

    sf::Texture design = sf::Texture();

    CardVictoryPoint* victoryPoints = new CardVictoryPoint();

    std::vector<ResourceToProduce*> productionGainAdvanced;
    productionGainAdvanced.push_back(firstAdvancedResourceToProduce);
    productionGainAdvanced.push_back(secondAdvancedResourceToProduce);

    CardVictoryPoint* victoryPointsAdvanced  = new CardVictoryPoint();

    EmpireLand empire = AZTEC;
    
    // Testing the full constructor of EmpireCard.
    EmpireCard* mySecondEmpireCard = new EmpireCard(name, productionGain, design, victoryPoints, productionGainAdvanced, victoryPointsAdvanced, empire);

    // Delete pointers that won't be used anymore.
    mySecondEmpireCard->~EmpireCard();
  }
}

/* vim: set sw=2 sts=2 et : */
