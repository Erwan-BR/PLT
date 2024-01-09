#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/EmpireCard.h"
#include "../../src/shared/state/CreateAllCards.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(test_ConversionJSON)
{
    // Testing conversion of JSON (face A)
    {
        CreateAllCards* createEmpire = new CreateAllCards();
        EmpireCard* empireCardToExport = createEmpire->createEmpireAFRICA(true);
        
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

        BOOST_CHECK_EQUAL(empireFromImport->getRelativePathToTexture(), "./resources/img/Cards/Empire_Face_A/Panafricaine.png");

        CardVictoryPoint* importedCardPoints = empireFromImport->getVictoryPoints();

        BOOST_CHECK_EQUAL(importedCardPoints->numberOfPoints, 2);
        BOOST_CHECK_EQUAL(importedCardPoints->cardOrResourceType, CardType::RESEARCH);
    }

    // Testing conversion of JSON (face B)
    {
        CreateAllCards* createEmpire = new CreateAllCards();
        EmpireCard* empireCardToExport = createEmpire->createEmpireAFRICA(false);

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

        BOOST_CHECK_EQUAL(empireFromImport->getRelativePathToTexture(), "./resources/img/Cards/Empire_Face_A/Panafricaine.png");

        CardVictoryPoint* importedCardPoints = empireFromImport->getVictoryPoints();

        BOOST_CHECK_EQUAL(importedCardPoints->numberOfPoints, 0);
        BOOST_CHECK_EQUAL(importedCardPoints->cardOrResourceType, 0);
    }
}

BOOST_AUTO_TEST_CASE(test_otherMethods)
{
    CreateAllCards* createEmpire = new CreateAllCards();
    EmpireCard* empireExample = createEmpire->createEmpireASIA(false);

    delete createEmpire;
    delete empireExample;
}

/* vim: set sw=2 sts=2 et : */
