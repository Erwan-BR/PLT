#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/EmpireCard.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(firstEmpireCardTest)
{
    {
      /*
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

      sf::Texture* design = new sf::Texture();

      CardVictoryPoint* victoryPoints = new CardVictoryPoint{1,state::CardType::NONETYPE};

      std::vector<ResourceToProduce*> productionGainAdvanced;
      productionGainAdvanced.push_back(firstAdvancedResourceToProduce);
      productionGainAdvanced.push_back(secondAdvancedResourceToProduce);

      CardVictoryPoint* victoryPointsAdvanced  = {};

      EmpireLand empire = AZTEC;
      */
      // face B
      ResourceToProduce* firstResourceToProduce = new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE};
      ResourceToProduce* secondResourceToProduce = new ResourceToProduce{ResourceType::ENERGY, 1, CardType::NONETYPE};
      ResourceToProduce* thirdResourceToProduce = new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::NONETYPE};
      std::vector<ResourceToProduce*> productionGainB = {firstResourceToProduce,secondResourceToProduce, thirdResourceToProduce};		

      bool isFaceA = true;
      
      // empire AFRICA
      ResourceToProduce* firstResourceToProduceAFRICA = new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE};
      ResourceToProduce* secondResourceToProduceAFRICA = new ResourceToProduce{ResourceType::SCIENCE, 2, CardType::NONETYPE};
      std::vector<ResourceToProduce*> productionGainAFRICA = {firstResourceToProduceAFRICA, secondResourceToProduceAFRICA};
      sf::Texture* designAFRICA = new sf::Texture;
      designAFRICA->loadFromFile("./resources/img/Cards/Empire_Face_A/Panafricaine.png");
      sf::Texture* designAFRICA_FaceB = new sf::Texture;
      designAFRICA_FaceB->loadFromFile("./resources/img/Cards/Empire_Face_B/Panafricaine.png");
      CardVictoryPoint* victoryPointsAFRICA  = new CardVictoryPoint{2,CardType::RESEARCH};
    
      // Testing the full constructor of EmpireCard.
      EmpireCard* mySecondEmpireCard = new EmpireCard("AFRICA", productionGainAFRICA, designAFRICA, victoryPointsAFRICA, productionGainB, {}, AFRICA, designAFRICA_FaceB, isFaceA);
      EmpireCard* myThirdEmpireCard = new EmpireCard("AFRICA", productionGainAFRICA, "./resources/img/Cards/Empire_Face_A/Panafricaine.png", victoryPointsAFRICA, productionGainB, {0}, AFRICA, "./resources/img/Cards/Empire_Face_B/Panafricaine.png", !isFaceA);


      (void) mySecondEmpireCard->getDesignFaceB();
      std::vector<ResourceToProduce*> productionGain = mySecondEmpireCard->getProductionGain();
      BOOST_CHECK_EQUAL(productionGain[0],firstResourceToProduceAFRICA);
      BOOST_CHECK_EQUAL(productionGain[1],secondResourceToProduceAFRICA);

      productionGain = myThirdEmpireCard->getProductionGain();
      BOOST_CHECK_EQUAL(productionGain[0],firstResourceToProduce);
      BOOST_CHECK_EQUAL(productionGain[1],secondResourceToProduce);
      BOOST_CHECK_EQUAL(productionGain[2],thirdResourceToProduce);

      CardVictoryPoint* victoryPoints = mySecondEmpireCard->getVictoryPoints();
      //BOOST_CHECK_EQUAL(victoryPoints[0],2);
      //BOOST_CHECK_EQUAL(victoryPoints[1],CardType::RESEARCH);
      (void) mySecondEmpireCard->getVictoryPoints();
    
      (void) myThirdEmpireCard->getRelativePathOfTextureFaceB();
      (void) myThirdEmpireCard->getVictoryPoints();

      // Delete pointers that won't be used anymore.
      delete mySecondEmpireCard;
      //delete myThirdEmpireCard;
    }
}

/* vim: set sw=2 sts=2 et : */
