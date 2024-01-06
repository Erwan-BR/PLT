#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/EmpireCard.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(test_ConversionJSON)
{
    // Testing conversion of JSON (face A)
    {
        // face B of the empire card
        ResourceToProduce* firstResourceToProduce = new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE};
        ResourceToProduce* secondResourceToProduce = new ResourceToProduce{ResourceType::ENERGY, 1, CardType::NONETYPE};
        ResourceToProduce* thirdResourceToProduce = new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::NONETYPE};
        std::vector<ResourceToProduce*> productionGainB = {firstResourceToProduce,secondResourceToProduce, thirdResourceToProduce};

        // empire AFRICA
        ResourceToProduce* firstResourceToProduceAFRICA = new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE};
        ResourceToProduce* secondResourceToProduceAFRICA = new ResourceToProduce{ResourceType::SCIENCE, 2, CardType::NONETYPE};
        std::vector<ResourceToProduce*> productionGainAFRICA = {firstResourceToProduceAFRICA, secondResourceToProduceAFRICA};
        std::string relativePathOfTexture = "../resources/img/Cards/Empire_Face_A/Panafricaine.png";
        std::string relativePathOfTextureFaceB = "../resources/img/Cards/Empire_Face_B/Panafricaine.png";
        CardVictoryPoint* victoryPointsAFRICA  = new CardVictoryPoint{2,CardType::RESEARCH};
        EmpireCard* empireCardToExport = new EmpireCard("AFRICA", productionGainAFRICA, relativePathOfTexture, victoryPointsAFRICA, productionGainB, new CardVictoryPoint{}, AFRICA, relativePathOfTextureFaceB, true);

        Json::Value jsonContent = empireCardToExport->toJSON();

        // Only for debug, the JSON appears in a log file (PLT/build/test/Testing/Temporary/LastTest.log)
        /*
        for (int i = 0; i < 7; i++)
        {
            std::cout << std::endl;
        }
        
        std::cout << jsonContent;
        
        for (int i = 0; i < 7; i++)
        {
            std::cout << std::endl;
        }
        */

        EmpireCard* empireFromImport = new EmpireCard(jsonContent);

        // Following lines will check all possible attributes from the card.
        BOOST_CHECK_EQUAL(empireFromImport->getName(), "AFRICA");

        std::vector<ResourceToProduce*> importedCardProduction = empireFromImport->getProductionGain();
        BOOST_CHECK_EQUAL(importedCardProduction.size(), 2);

        BOOST_CHECK_EQUAL(importedCardProduction[0]->type, ResourceType::MATERIAL);
        BOOST_CHECK_EQUAL(importedCardProduction[0]->quantity, 2);
        BOOST_CHECK_EQUAL(importedCardProduction[0]->cardType, CardType::NONETYPE);

        BOOST_CHECK_EQUAL(importedCardProduction[1]->type, ResourceType::SCIENCE);
        BOOST_CHECK_EQUAL(importedCardProduction[1]->quantity, 2);
        BOOST_CHECK_EQUAL(importedCardProduction[1]->cardType, CardType::NONETYPE);

        BOOST_CHECK_EQUAL(empireFromImport->getRelativePathToTexture(), "../resources/img/Cards/Empire_Face_A/Panafricaine.png");
        BOOST_CHECK_EQUAL(empireFromImport->getRelativePathOfTextureFaceB(), "../resources/img/Cards/Empire_Face_B/Panafricaine.png");

        CardVictoryPoint* importedCardPoints = empireFromImport->getVictoryPoints();

        BOOST_CHECK_EQUAL(importedCardPoints->numberOfPoints, 2);
        BOOST_CHECK_EQUAL(importedCardPoints->cardOrResourceType, CardType::RESEARCH);
    }

    // Testing conversion of JSON (face B)
    {
        // face B of the empire card
        ResourceToProduce* firstResourceToProduce = new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE};
        ResourceToProduce* secondResourceToProduce = new ResourceToProduce{ResourceType::ENERGY, 1, CardType::NONETYPE};
        ResourceToProduce* thirdResourceToProduce = new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::NONETYPE};
        std::vector<ResourceToProduce*> productionGainB = {firstResourceToProduce, secondResourceToProduce, thirdResourceToProduce};

        // empire AFRICA
        ResourceToProduce* firstResourceToProduceAFRICA = new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE};
        ResourceToProduce* secondResourceToProduceAFRICA = new ResourceToProduce{ResourceType::SCIENCE, 2, CardType::NONETYPE};
        std::vector<ResourceToProduce*> productionGainAFRICA = {firstResourceToProduceAFRICA, secondResourceToProduceAFRICA};
        std::string relativePathOfTexture = "../resources/img/Cards/Empire_Face_A/Panafricaine.png";
        std::string relativePathOfTextureFaceB = "../resources/img/Cards/Empire_Face_B/Panafricaine.png";
        CardVictoryPoint* victoryPointsAFRICA  = new CardVictoryPoint{2,CardType::RESEARCH};
        EmpireCard* empireCardToExport = new EmpireCard("AFRICA", productionGainAFRICA, relativePathOfTexture, victoryPointsAFRICA, productionGainB, new CardVictoryPoint{}, AFRICA, relativePathOfTextureFaceB, false);

        Json::Value jsonContent = empireCardToExport->toJSON();

        for (int i = 0; i < 7; i++)
        {
            std::cout << std::endl;
        }

        std::cout << jsonContent;
        
        for (int i = 0; i < 7; i++)
        {
            std::cout << std::endl;
        }

        EmpireCard* empireFromImport = new EmpireCard(jsonContent);

        // Following lines will check all possible attributes from the card.
        BOOST_CHECK_EQUAL(empireFromImport->getName(), "AFRICA");

        std::vector<ResourceToProduce*> importedCardProduction = empireFromImport->getProductionGain();
        BOOST_CHECK_EQUAL(importedCardProduction.size(), 3);

        BOOST_CHECK_EQUAL(importedCardProduction[0]->type, ResourceType::MATERIAL);
        BOOST_CHECK_EQUAL(importedCardProduction[0]->quantity, 2);
        BOOST_CHECK_EQUAL(importedCardProduction[0]->cardType, CardType::NONETYPE);

        BOOST_CHECK_EQUAL(importedCardProduction[1]->type, ResourceType::ENERGY);
        BOOST_CHECK_EQUAL(importedCardProduction[1]->quantity, 1);
        BOOST_CHECK_EQUAL(importedCardProduction[1]->cardType, CardType::NONETYPE);

        BOOST_CHECK_EQUAL(importedCardProduction[2]->type, ResourceType::SCIENCE);
        BOOST_CHECK_EQUAL(importedCardProduction[2]->quantity, 1);
        BOOST_CHECK_EQUAL(importedCardProduction[2]->cardType, CardType::NONETYPE);

        BOOST_CHECK_EQUAL(empireFromImport->getRelativePathToTexture(), "../resources/img/Cards/Empire_Face_A/Panafricaine.png");
        BOOST_CHECK_EQUAL(empireFromImport->getRelativePathOfTextureFaceB(), "../resources/img/Cards/Empire_Face_B/Panafricaine.png");

        CardVictoryPoint* importedCardPoints = empireFromImport->getVictoryPoints();

        BOOST_CHECK_EQUAL(importedCardPoints->numberOfPoints, 0);
        BOOST_CHECK_EQUAL(importedCardPoints->cardOrResourceType, 0);
    }
}

BOOST_AUTO_TEST_CASE(test_ConstructorMethods)
{
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

/* vim: set sw=2 sts=2 et : */
