#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Player.h"
#include "../../src/shared/state/Game.h"
#include "../../src/shared/state/CreateAllCards.h"
#include "../../src/constants/constants/CustomTypes.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(test_ConversionJSON)
{
    Player* playerToExport = new Player("Erwan", 1);

    CreateAllCards* createEmpire = new CreateAllCards();

    playerToExport->setEmpire(createEmpire->createEmpireAFRICA(true));

    // Create multiple cards to send them in vectors and check if they are correctly placed in the JSON.

    // Amelioration genetique
    constants::victoryPointsPtr victoryPointsAmelioration = std::make_shared<CardVictoryPoint>();
    victoryPointsAmelioration->numberOfPoints = 3;
    victoryPointsAmelioration->cardOrResourceType = static_cast<int>(CardType::NONETYPE);
    
    constants::resourcePayList resourceToPayAmeliorationList = {};
    const std::vector<ResourceType> resourceToPayAmelioration = {ResourceType::SCIENCE, ResourceType::SCIENCE, ResourceType::SCIENCE, ResourceType::SCIENCE};
    for (size_t i = 0; resourceToPayAmelioration.size() > i; i++)
    {
        constants::resourcePayPtr resourceToPayAmeliorationPtr = std::make_shared<ResourceToPay>();
        resourceToPayAmeliorationPtr->type = resourceToPayAmelioration[i];
        resourceToPayAmeliorationPtr->isPaid = false;

        resourceToPayAmeliorationList.push_back(resourceToPayAmeliorationPtr);
    }
    constants::devCardPtr ameliorationGenetique(new DevelopmentCard("Amelioration genetique", constants::resourceProdList{}, victoryPointsAmelioration,CardType::RESEARCH,1,resourceToPayAmeliorationList,{ResourceType::FINANCIER, ResourceType::FINANCIER},ResourceType::SCIENCE));

    // Animorphes
    constants::resourceProdPtr resourceProducedAnimorphes = std::make_shared<ResourceToProduce>();
    resourceProducedAnimorphes->type = ResourceType::MATERIAL;
    resourceProducedAnimorphes->quantity = 1;
    resourceProducedAnimorphes->cardType = CardType::NONETYPE;

    constants::victoryPointsPtr victoryPointsAnimorphes = std::make_shared<CardVictoryPoint>();
    victoryPointsAnimorphes->numberOfPoints = 2;
    victoryPointsAnimorphes->cardOrResourceType = static_cast<int>(CardType::NONETYPE);
    
    constants::resourcePayList resourceToPayAnimorphesList = {};
    const std::vector<ResourceType> resourceToPayAnimorphes = {ResourceType::ENERGY, ResourceType::SCIENCE, ResourceType::SCIENCE};
    for (size_t i = 0; resourceToPayAnimorphes.size() > i; i++)
    {
        constants::resourcePayPtr resourceToPayAnimorphesPtr = std::make_shared<ResourceToPay>();
        resourceToPayAnimorphesPtr->type = resourceToPayAnimorphes[i];
        resourceToPayAnimorphesPtr->isPaid = false;

        resourceToPayAnimorphesList.push_back(resourceToPayAnimorphesPtr);
    }
    constants::devCardPtr animorphes(new DevelopmentCard("Animorphes", {resourceProducedAnimorphes}, victoryPointsAnimorphes, CardType::RESEARCH,1,resourceToPayAnimorphesList,{ResourceType::COLONEL},ResourceType::ENERGY));

    // Aquaculture
    constants::victoryPointsPtr victoryPointsAquaculture = std::make_shared<CardVictoryPoint>();
    victoryPointsAquaculture->numberOfPoints = 1;
    victoryPointsAquaculture->cardOrResourceType = static_cast<int>(ResourceType::FINANCIER);
    
    constants::resourcePayList resourceToPayAquacultureList = {};
    const std::vector<ResourceType> resourceToPayAquaculture = {ResourceType::SCIENCE, ResourceType::SCIENCE, ResourceType::SCIENCE, ResourceType::SCIENCE, ResourceType::GOLD, ResourceType::GOLD};
    for (size_t i = 0; resourceToPayAquaculture.size() > i; i++)
    {
        constants::resourcePayPtr resourceToPayAquaculturePtr = std::make_shared<ResourceToPay>();
        resourceToPayAquaculturePtr->type = resourceToPayAquaculture[i];
        resourceToPayAquaculturePtr->isPaid = false;

        resourceToPayAquacultureList.push_back(resourceToPayAquaculturePtr);
    }
    constants::devCardPtr aquaculture(new DevelopmentCard("Aquaculture",constants::resourceProdList{},victoryPointsAquaculture,CardType::RESEARCH,1,resourceToPayAquacultureList,{ResourceType::FINANCIER},ResourceType::SCIENCE));

    // Automates de controle
    constants::victoryPointsPtr victoryPointsAutomate = std::make_shared<CardVictoryPoint>();
    victoryPointsAutomate->numberOfPoints = 1;
    victoryPointsAutomate->cardOrResourceType = static_cast<int>(ResourceType::COLONEL);
    
    constants::resourcePayList resourceToPayAutomateList = {};
    const std::vector<ResourceType> resourceToPayAutomate = {ResourceType::SCIENCE, ResourceType::SCIENCE, ResourceType::SCIENCE, ResourceType::SCIENCE, ResourceType::GOLD};
    for (size_t i = 0; resourceToPayAutomate.size() > i; i++)
    {
        constants::resourcePayPtr resourceToPayAutomatePtr = std::make_shared<ResourceToPay>();
        resourceToPayAutomatePtr->type = resourceToPayAutomate[i];
        resourceToPayAutomatePtr->isPaid = false;

        resourceToPayAutomateList.push_back(resourceToPayAutomatePtr);
    }
    constants::devCardPtr automateControle(new DevelopmentCard("Automates de controle", constants::resourceProdList{}, victoryPointsAutomate,CardType::RESEARCH,1,resourceToPayAutomateList,{},ResourceType::GOLD));

    // Clonage humain
    constants::resourceProdPtr resourceProducedClonage = std::make_shared<ResourceToProduce>();
    resourceProducedClonage->type = ResourceType::GOLD;
    resourceProducedClonage->quantity = 1;
    resourceProducedClonage->cardType = CardType::NONETYPE;

    constants::victoryPointsPtr victoryPointsClonage = std::make_shared<CardVictoryPoint>();
    victoryPointsClonage->numberOfPoints = 1;
    victoryPointsClonage->cardOrResourceType = static_cast<int>(CardType::NONETYPE);
    
    constants::resourcePayList resourceToPayClonageList = {};
    const std::vector<ResourceType> resourceToPayClonage = {ResourceType::ENERGY, ResourceType::SCIENCE, ResourceType::GOLD};
    for (size_t i = 0; resourceToPayClonage.size() > i; i++)
    {
        constants::resourcePayPtr resourceToPayClonagePtr = std::make_shared<ResourceToPay>();
        resourceToPayClonagePtr->type = resourceToPayClonage[i];
        resourceToPayClonagePtr->isPaid = false;

        resourceToPayClonageList.push_back(resourceToPayClonagePtr);
    }
    constants::devCardPtr clonageHumain(new DevelopmentCard("Clonage Humain",{resourceProducedClonage}, victoryPointsClonage,CardType::RESEARCH,1,resourceToPayClonageList,{ResourceType::FINANCIER},ResourceType::GOLD));

    // Controle du climat
    constants::resourceProdPtr resourceProducedControle1 = std::make_shared<ResourceToProduce>();
    resourceProducedControle1->type = ResourceType::ENERGY;
    resourceProducedControle1->quantity = 2;
    resourceProducedControle1->cardType = CardType::NONETYPE;
    constants::resourceProdPtr resourceProducedControle2 = std::make_shared<ResourceToProduce>();
    resourceProducedControle2->type = ResourceType::GOLD;
    resourceProducedControle2->quantity = 1;
    resourceProducedControle2->cardType = CardType::NONETYPE;

    constants::victoryPointsPtr victoryPointsControle = std::make_shared<CardVictoryPoint>();
    victoryPointsControle->numberOfPoints = 2;
    victoryPointsControle->cardOrResourceType = static_cast<int>(CardType::NONETYPE);
    
    constants::resourcePayList resourceToPayControleList = {};
    const std::vector<ResourceType> resourceToPayControle = {ResourceType::SCIENCE, ResourceType::SCIENCE, ResourceType::SCIENCE, ResourceType::SCIENCE, ResourceType::SCIENCE};
    for (size_t i = 0; resourceToPayControle.size() > i; i++)
    {
        constants::resourcePayPtr resourceToPayControlePtr = std::make_shared<ResourceToPay>();
        resourceToPayControlePtr->type = resourceToPayControle[i];
        resourceToPayControlePtr->isPaid = false;

        resourceToPayControleList.push_back(resourceToPayControlePtr);
    }
    constants::devCardPtr controlDuClimat(new DevelopmentCard("Controle du climat",{resourceProducedControle1, resourceProducedControle2}, victoryPointsControle,CardType::RESEARCH,1,{resourceToPayControleList},{},ResourceType::ENERGY));

    constants::deckOfCards cardsOfPlayertoExport = {ameliorationGenetique, animorphes, aquaculture, automateControle, clonageHumain, controlDuClimat};

    playerToExport->setDraftingCards(cardsOfPlayertoExport);

    playerToExport->chooseDraftCard(0);
    playerToExport->setStatePlaying();
    playerToExport->chooseDraftCard(0);
    playerToExport->setStatePlaying();
    playerToExport->chooseDraftCard(0);

    playerToExport->receiveResources(ResourceType::SCIENCE, 5);
    playerToExport->receiveResources(ResourceType::KRYSTALLIUM, 1);
    playerToExport->receiveResources(ResourceType::COLONEL, 1);
    playerToExport->receiveResources(ResourceType::FINANCIER, 2);

    playerToExport->keepCard(0);
    playerToExport->keepCard(0);

    // Building the card 0.
    playerToExport->addResource(ResourceType::SCIENCE, 0);
    playerToExport->addResource(ResourceType::SCIENCE, 0);
    playerToExport->addResource(ResourceType::SCIENCE, 0);
    playerToExport->addResource(ResourceType::SCIENCE, 0);

    Json::Value playerJSON = playerToExport->toJSON();

    // Only for debug, the JSON appears in a log file (PLT/build/test/Testing/Temporary/LastTest.log)
    // for (int i = 0; i < 7; i++)
    // {
    //     std::cout << std::endl;
    // }

    // std::cout << playerJSON;

    // for (int i = 0; i < 7; i++)
    // {
    //     std::cout << std::endl;
    // }

    Player* playerToImport = new Player(playerJSON);

    BOOST_CHECK_EQUAL(playerToImport->getName(), "Erwan");
    BOOST_CHECK_EQUAL(playerToImport->getID(), 1);
    BOOST_CHECK_EQUAL(playerToImport->getEmpire()->getName(), "AFRICA");
    BOOST_CHECK_EQUAL(playerToImport->getState(), PlayerState::PENDING);
    BOOST_CHECK_EQUAL(playerToImport->getResourcesInEmpireUnit(), 0);

    BOOST_CHECK_EQUAL(playerToImport->getToBuildCards().size(), 1);
    BOOST_CHECK_EQUAL(playerToImport->getToBuildCards()[0]->getName(), "Animorphes");

    BOOST_CHECK_EQUAL(playerToImport->getDraftingCards().size(), 3);
    BOOST_CHECK_EQUAL(playerToImport->getDraftingCards()[0]->getName(), "Automates de controle");
    BOOST_CHECK_EQUAL(playerToImport->getDraftingCards()[1]->getName(), "Clonage Humain");
    BOOST_CHECK_EQUAL(playerToImport->getDraftingCards()[2]->getName(), "Controle du climat");

    BOOST_CHECK_EQUAL(playerToImport->getBuiltCards().size(), 1);
    BOOST_CHECK_EQUAL(playerToImport->getBuiltCards()[0]->getName(), "Amelioration genetique");

    BOOST_CHECK_EQUAL(playerToImport->getDraftCards().size(), 1);
    BOOST_CHECK_EQUAL(playerToImport->getDraftCards()[0]->getName(), "Aquaculture");

    BOOST_CHECK_EQUAL(playerToImport->getCurrentResources(ResourceType::MATERIAL), 0);
    BOOST_CHECK_EQUAL(playerToImport->getCurrentResources(ResourceType::ENERGY), 0);
    BOOST_CHECK_EQUAL(playerToImport->getCurrentResources(ResourceType::GOLD), 0);
    BOOST_CHECK_EQUAL(playerToImport->getCurrentResources(ResourceType::SCIENCE), 1);
    BOOST_CHECK_EQUAL(playerToImport->getCurrentResources(ResourceType::EXPLORATION), 0);
    BOOST_CHECK_EQUAL(playerToImport->getCurrentResources(ResourceType::KRYSTALLIUM), 1);
    BOOST_CHECK_EQUAL(playerToImport->getCurrentResources(ResourceType::COLONEL), 1);
    BOOST_CHECK_EQUAL(playerToImport->getCurrentResources(ResourceType::FINANCIER), 4);

    BOOST_CHECK_EQUAL(playerToImport->getCardsTypeList().at(CardType::STRUCTURE), 0);
    BOOST_CHECK_EQUAL(playerToImport->getCardsTypeList().at(CardType::VEHICLE), 0);
    BOOST_CHECK_EQUAL(playerToImport->getCardsTypeList().at(CardType::RESEARCH), 1);
    BOOST_CHECK_EQUAL(playerToImport->getCardsTypeList().at(CardType::PROJECT), 0);
    BOOST_CHECK_EQUAL(playerToImport->getCardsTypeList().at(CardType::DISCOVERY), 0);
    BOOST_CHECK_EQUAL(playerToImport->getCardsTypeList().at(CardType::VEHICLE), 0);

    BOOST_CHECK_EQUAL(playerToImport->getProductionGain(ResourceType::MATERIAL), 2);
    BOOST_CHECK_EQUAL(playerToImport->getProductionGain(ResourceType::ENERGY), 0);
    BOOST_CHECK_EQUAL(playerToImport->getProductionGain(ResourceType::GOLD), 0);
    BOOST_CHECK_EQUAL(playerToImport->getProductionGain(ResourceType::SCIENCE), 2);
    BOOST_CHECK_EQUAL(playerToImport->getProductionGain(ResourceType::EXPLORATION), 0);

    // Delete pointers
    delete playerToExport;
    delete createEmpire;
    delete playerToImport;
}

BOOST_AUTO_TEST_CASE(firstPlayerTest)
{
    Player* myFirstPlayer = new Player("Maxime", 1);

    //Defining Empire
    //Producing 2 ENERGY, 1 SCIENCE, gain 3 victory points per DISCOVERY cards
    const std::vector<ResourceType> resourceProdRsc = {ResourceType::MATERIAL, ResourceType::ENERGY, ResourceType::SCIENCE};
    const std::vector<int> resourceProdQty = {2, 1, 1};
    constants::resourceProdList productionGainB = {};
    for (size_t index; resourceProdRsc.size() > index; index++)
    {
        constants::resourceProdPtr resourceToProduce = std::make_shared<ResourceToProduce>();
        resourceToProduce->cardType = CardType::NONETYPE;
        resourceToProduce->type = resourceProdRsc[index];
        resourceToProduce->quantity = resourceProdQty[index];
        productionGainB.push_back(resourceToProduce);
    }

    const std::vector<ResourceType> resourceProdAztecRsc = {ResourceType::ENERGY, ResourceType::SCIENCE};
    const std::vector<int> resourceProdAztecQty = {2, 1};
    constants::resourceProdList productionGainAZTEC = {};
    for (size_t index; resourceProdAztecRsc.size() > index; index++)
    {
        constants::resourceProdPtr resourceToProduce = std::make_shared<ResourceToProduce>();
        resourceToProduce->cardType = CardType::NONETYPE;
        resourceToProduce->type = resourceProdAztecRsc[index];
        resourceToProduce->quantity = resourceProdAztecQty[index];
        productionGainAZTEC.push_back(resourceToProduce);
    }
    
    constants::victoryPointsPtr victoryPointsAZTEC = std::make_shared<CardVictoryPoint>(); 
    victoryPointsAZTEC->numberOfPoints = 3; CardVictoryPoint{3, CardType::DISCOVERY};
    victoryPointsAZTEC->cardOrResourceType = static_cast<int>(CardType::DISCOVERY);
    constants::empireCardPtr aztec (new EmpireCard("AZTEC", productionGainAZTEC, victoryPointsAZTEC, productionGainB, AZTEC, true));

    // Giving the empire to the player
    myFirstPlayer->setEmpire(aztec);

    // Drafting deck to fill
    constants::deckOfCards draftingDeck = {};

    // Three Zeppelin : One to draft, one to build and one to stay in drafting.
    for (int i = 0; 3 > i; i++)
    {
        // Giving 1 EXPLORATION
        constants::resourceProdPtr resourceProducedZeppelin = std::make_shared<ResourceToProduce>();
        resourceProducedZeppelin->type = ResourceType::EXPLORATION;
        resourceProducedZeppelin->quantity = 1;
        resourceProducedZeppelin->cardType = CardType::NONETYPE;

        constants::victoryPointsPtr victoryPointsZeppelin = std::make_shared<CardVictoryPoint>();
        victoryPointsZeppelin->numberOfPoints = 0;
        victoryPointsZeppelin->cardOrResourceType = static_cast<int>(CardType::NONETYPE);

        constants::resourcePayPtr resourceToPayZeppelin1 = std::make_shared<ResourceToPay>();
        resourceToPayZeppelin1->type = ResourceType::ENERGY;
        resourceToPayZeppelin1->isPaid = false;
        constants::resourcePayPtr resourceToPayZeppelin2 = std::make_shared<ResourceToPay>();
        resourceToPayZeppelin2->type = ResourceType::ENERGY;
        resourceToPayZeppelin2->isPaid = false;

        constants::devCardPtr zeppelin(new DevelopmentCard("Zeppelin",{resourceProducedZeppelin}, victoryPointsZeppelin, CardType::VEHICLE,6,{resourceToPayZeppelin1, resourceToPayZeppelin2},{},ResourceType::EXPLORATION));
        draftingDeck.push_back(zeppelin);
    }
    // Card that produces nothing, 1 victory points per FINANCIER, 1 instant FINANCIER
    // Need to pay 1 ENERGY
    constants::victoryPointsPtr victoryPointsAscenseurSpatial = std::make_shared<CardVictoryPoint>();
    victoryPointsAscenseurSpatial->numberOfPoints = 1;
    victoryPointsAscenseurSpatial->cardOrResourceType = static_cast<int>(ResourceType::FINANCIER);

    constants::resourcePayPtr resourceToPayAscenseurSpatial = std::make_shared<ResourceToPay>();
    resourceToPayAscenseurSpatial->type = ResourceType::ENERGY;
    resourceToPayAscenseurSpatial->isPaid = false;
    constants::devCardPtr ascenseurSpatial(new DevelopmentCard("Ascenseur spatial", constants::resourceProdList{}, victoryPointsAscenseurSpatial,CardType::PROJECT,1,{resourceToPayAscenseurSpatial},{ResourceType::FINANCIER},ResourceType::ENERGY));
    draftingDeck.push_back(ascenseurSpatial);

    // Card that produces nothing, 1 victory points per COLONEL
    // Need to pay 1 SCIENCE
    constants::victoryPointsPtr victoryPointsAutomateControle = std::make_shared<CardVictoryPoint>();
    victoryPointsAutomateControle->numberOfPoints = 1;
    victoryPointsAutomateControle->cardOrResourceType = static_cast<int>(ResourceType::COLONEL);

    constants::resourcePayPtr resourceToPayAutomateControle = std::make_shared<ResourceToPay>();
    resourceToPayAutomateControle->type = ResourceType::SCIENCE;
    resourceToPayAutomateControle->isPaid = false;
    constants::devCardPtr automateControle(new DevelopmentCard("Automates de controle",constants::resourceProdList{}, victoryPointsAutomateControle, CardType::RESEARCH, 1, {resourceToPayAutomateControle},{},ResourceType::GOLD));
    draftingDeck.push_back(automateControle);

    // Card that produces 3 EXPLORATION, 2 victory points per DISCOVERY card, 1 instant COLONEL
    // Need to pay 1 ENERGY
    constants::resourceProdPtr resourceProducedBasePolaire = std::make_shared<ResourceToProduce>();
    resourceProducedBasePolaire->type = ResourceType::EXPLORATION;
    resourceProducedBasePolaire->quantity = 3;
    resourceProducedBasePolaire->cardType = CardType::DISCOVERY;

    constants::victoryPointsPtr victoryPointsBasePolaire = std::make_shared<CardVictoryPoint>();
    victoryPointsBasePolaire->numberOfPoints = 2;
    victoryPointsBasePolaire->cardOrResourceType = static_cast<int>(CardType::DISCOVERY);

    constants::resourcePayPtr resourceToPayBasePolaire = std::make_shared<ResourceToPay>();
    resourceToPayBasePolaire->type = ResourceType::ENERGY;
    resourceToPayBasePolaire->isPaid = false;
    constants::devCardPtr basePolaire(new DevelopmentCard("Base polaire", {resourceProducedBasePolaire}, victoryPointsBasePolaire,CardType::PROJECT,1,{resourceToPayBasePolaire},{ResourceType::COLONEL},ResourceType::EXPLORATION));
    draftingDeck.push_back(basePolaire);

    // Defining multiple cards to fully test all functions
    // Card that produces 1 SCIENCE * DISCOVERY cards, 10 victory points, 2 instant KRYSTALLIUM
    // Need to pay 1 EXPLORATION
    constants::resourceProdPtr resourceProducedAstronautes = std::make_shared<ResourceToProduce>();
    resourceProducedAstronautes->type = ResourceType::SCIENCE;
    resourceProducedAstronautes->quantity = 1;
    resourceProducedAstronautes->cardType = CardType::DISCOVERY;

    constants::victoryPointsPtr victoryPointsAstronautes = std::make_shared<CardVictoryPoint>();
    victoryPointsAstronautes->numberOfPoints = 10;
    victoryPointsAstronautes->cardOrResourceType = static_cast<int>(CardType::NONETYPE);

    constants::resourcePayPtr resourceToPayAstronautes = std::make_shared<ResourceToPay>();
    resourceToPayAstronautes->type = ResourceType::EXPLORATION;
    resourceToPayAstronautes->isPaid = false;

    constants::devCardPtr anciensAstronautes(new DevelopmentCard("Anciens Astronautes",{resourceProducedAstronautes},victoryPointsAstronautes,CardType::DISCOVERY,1,{resourceToPayAstronautes},{ResourceType::KRYSTALLIUM,ResourceType::KRYSTALLIUM},ResourceType::SCIENCE));
    draftingDeck.push_back(anciensAstronautes);

    myFirstPlayer->setDraftingCards(draftingDeck);
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftingCards().size(), 7);

    // Choosing the DraftCards
    for(int i=1; i<(int)draftingDeck.size(); i++)
    {
        myFirstPlayer->chooseDraftCard(1);
        myFirstPlayer->setStatePlaying();
        int stringCompare = strcmp(draftingDeck.at(i)->getName().data(), myFirstPlayer->getDraftCards().at(i-1)->getName().data());
        BOOST_CHECK_EQUAL(stringCompare, 0);
    }
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftingCards().size(), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftCards().size(), 6);

    // Choosing out of bound draft card
    myFirstPlayer->chooseDraftCard(42);
    myFirstPlayer->setStatePlaying();

    // Choosing the toBuildCards
    constants::deckOfCards draftDeck = myFirstPlayer->getDraftCards();
    for(int i=1; i<6; i++)
    {
        myFirstPlayer->keepCard(1);
        int stringCompare = strcmp(myFirstPlayer->getToBuildCards().at(i-1)->getName().data(), draftDeck.at(i)->getName().data());
        BOOST_CHECK_EQUAL(stringCompare, 0);   
    }
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftCards().size(), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getToBuildCards().size(), 5);

    // Choosing out of bound keep card
    myFirstPlayer->keepCard(42);

    // Discarding the last drafted Card
    myFirstPlayer->discardCard(0,true);
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftCards().size(), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(EXPLORATION), 1);

    // Discarding out of bound card
    myFirstPlayer->discardCard(42, true);

    // Production phase with empire only
    myFirstPlayer->updateProduction();
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(ENERGY), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(SCIENCE), 0);

    // Transferring the to produce resources to the possessed resources
    myFirstPlayer->receiveResources(MATERIAL, myFirstPlayer->getResourcesProduction().at(MATERIAL));
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(MATERIAL), 0);
    myFirstPlayer->receiveResources(ENERGY, myFirstPlayer->getResourcesProduction().at(ENERGY));
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(ENERGY), 0);
    myFirstPlayer->receiveResources(SCIENCE, myFirstPlayer->getResourcesProduction().at(SCIENCE));
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(SCIENCE), 0);
    myFirstPlayer->receiveResources(GOLD, myFirstPlayer->getResourcesProduction().at(GOLD));
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(GOLD), 0);
    myFirstPlayer->receiveResources(EXPLORATION, myFirstPlayer->getResourcesProduction().at(EXPLORATION));
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(EXPLORATION), 1);

    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(COLONEL), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(FINANCIER), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(KRYSTALLIUM), 0);

    // Checking if resources of a type can be added to a card
    BOOST_CHECK_EQUAL(myFirstPlayer->isResourcePlayable(ENERGY), false);
    BOOST_CHECK_EQUAL(myFirstPlayer->isResourcePlayable(GOLD), false);

    // Constructing cards
    myFirstPlayer->receiveResources(ENERGY, 2);
    myFirstPlayer->addResource(ENERGY, 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getBuiltCards().size(), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getToBuildCards().size(), 4);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(ENERGY), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(FINANCIER), 1);

    myFirstPlayer->receiveResources(SCIENCE, 1);
    myFirstPlayer->addResource(SCIENCE, 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getBuiltCards().size(), 2);
    BOOST_CHECK_EQUAL(myFirstPlayer->getToBuildCards().size(), 3);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(SCIENCE), 0);

    myFirstPlayer->addResource(ENERGY, 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getBuiltCards().size(), 3);
    BOOST_CHECK_EQUAL(myFirstPlayer->getToBuildCards().size(), 2);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(ENERGY), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(COLONEL), 1);

    myFirstPlayer->addResource(EXPLORATION, 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getBuiltCards().size(), 4);
    BOOST_CHECK_EQUAL(myFirstPlayer->getToBuildCards().size(), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(EXPLORATION), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(KRYSTALLIUM), 2);

    // Out of bound addResource test
    myFirstPlayer->addResource(ENERGY, 1);

    // Discarding last card of toBuild deck
    myFirstPlayer->discardCard(0, false);
    BOOST_CHECK_EQUAL(myFirstPlayer->getToBuildCards().size(), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesInEmpireUnit(), 1);

    // Discarding out of bound card
    myFirstPlayer->discardCard(42, false);

    // Recompute production
    myFirstPlayer->updateProduction();
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(MATERIAL), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(ENERGY), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(SCIENCE), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(GOLD), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(EXPLORATION), 3);

    // Transferring again the to produce resources to the possessed resources
    myFirstPlayer->receiveResources(MATERIAL, myFirstPlayer->getResourcesProduction().at(MATERIAL));
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(MATERIAL), 0);
    myFirstPlayer->receiveResources(ENERGY, myFirstPlayer->getResourcesProduction().at(ENERGY));
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(ENERGY), 0);
    myFirstPlayer->receiveResources(SCIENCE, myFirstPlayer->getResourcesProduction().at(SCIENCE));
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(SCIENCE), 1);
    myFirstPlayer->receiveResources(GOLD, myFirstPlayer->getResourcesProduction().at(GOLD));
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(GOLD), 0);
    myFirstPlayer->receiveResources(EXPLORATION, myFirstPlayer->getResourcesProduction().at(EXPLORATION));
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(EXPLORATION), 3);

    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(COLONEL), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(FINANCIER), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(KRYSTALLIUM), 2);

    // Compute victory points
    int victoryPoints = myFirstPlayer->computeVictoryPoint();
    BOOST_CHECK_EQUAL(victoryPoints, 19);

    // Ending the production
    myFirstPlayer->endProduction();
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(MATERIAL), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(ENERGY), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(SCIENCE), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(GOLD), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(EXPLORATION), 0);

    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(COLONEL), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(FINANCIER), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(KRYSTALLIUM), 3);

    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesInEmpireUnit(), 0);

    // Testing the error return of sendResourceToEmpire
    myFirstPlayer->sendResourceToEmpire(GOLD);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(GOLD), 0);

    // Testing end the planification
    draftingDeck = {draftingDeck[0]};
    myFirstPlayer->setDraftingCards(draftingDeck);
    myFirstPlayer->chooseDraftCard(0);
    myFirstPlayer->setStatePlaying();
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftCards().size(), 1);

    myFirstPlayer->endPlanification();
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftCards().size(), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getToBuildCards().size(), 1);
    
    (void)myFirstPlayer->isResourcePlayable(ResourceType::SCIENCE, 0);

    // Test convertKrystallium
    myFirstPlayer->convertKrystallium(MATERIAL);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(MATERIAL), 1);

    myFirstPlayer->convertKrystallium(COLONEL);


    // Test chooseColonel (not implemented yet)
    BOOST_CHECK_EQUAL(myFirstPlayer->isPreferedPersonnageColonel(), true);

    //Test the setter of the player's state
    myFirstPlayer->setStatePlaying();
    BOOST_CHECK_EQUAL(PLAYING, myFirstPlayer->getState());

    myFirstPlayer->setPreferedPersonnage(COLONEL);
    BOOST_CHECK_EQUAL(myFirstPlayer->isRealPlayerAndPlaying(), true);

    // Testing getters
    (void)myFirstPlayer->getProductionGain(MATERIAL);
    (void)myFirstPlayer->getName();
    (void)myFirstPlayer->getEmpire();
    (void)myFirstPlayer->getBuiltCards();
    (void)myFirstPlayer->getToBuildCards();
    (void)myFirstPlayer->getDraftingCards();
    (void)myFirstPlayer->getDraftCards();
    (void)myFirstPlayer->getState();
    (void)myFirstPlayer->getCurrentResources();
    (void)myFirstPlayer->getCurrentResources(MATERIAL);
    (void)myFirstPlayer->getResourcesInEmpireUnit();
    (void)myFirstPlayer->getResourcesProduction();
    (void)myFirstPlayer->getCardsTypeList();
    (void)myFirstPlayer->getID();
    (void)myFirstPlayer->isResourcePlayable(ResourceType::SCIENCE, 0);

    (void)myFirstPlayer->isAI();

    // Testing void AI functions
    myFirstPlayer->AIChooseDraftingCard();
    myFirstPlayer->AIPlanification();
    myFirstPlayer->AIUseProducedResources();

    // Delete pointers that won't be used anymore.
    delete myFirstPlayer;
}

/* vim: set sw=2 sts=2 et : */