#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Player.h"
#include "../../src/shared/state/Game.h"
#include "../../src/shared/state/CreateAllCards.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(test_ConversionJSON)
{
    Player* playerToExport = new Player("Erwan", 1);

    CreateAllCards* createEmpire = new CreateAllCards();

    playerToExport->setEmpire(createEmpire->createEmpireAFRICA(true));

    // Create multiple cards to send them in vectors and check if they are correctly placed in the JSON.
    // Amelioration genetique
    std::shared_ptr<DevelopmentCard> ameliorationGenetique(new DevelopmentCard ("Amelioration genetique",{},new CardVictoryPoint{3, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{ResourceType::FINANCIER, ResourceType::FINANCIER},ResourceType::SCIENCE));

    // Animorphes
    std::shared_ptr<DevelopmentCard> animorphes(new DevelopmentCard ("Animorphes",{new ResourceToProduce{ResourceType::MATERIAL, 1, CardType::NONETYPE}},new CardVictoryPoint{2, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{ResourceType::COLONEL},ResourceType::ENERGY));

    // Aquaculture
    std::shared_ptr<DevelopmentCard> aquaculture(new DevelopmentCard ("Aquaculture",{},new CardVictoryPoint{1, (int) ResourceType::FINANCIER},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::FINANCIER},ResourceType::SCIENCE));

    // Automates de controle
    std::shared_ptr<DevelopmentCard> automateControle(new DevelopmentCard ("Automates de controle",{},new CardVictoryPoint{1, (int) ResourceType::COLONEL},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}},{},ResourceType::GOLD));

    // Clonage humain
    std::shared_ptr<DevelopmentCard> clonageHumain(new DevelopmentCard ("Clonage Humain",{new ResourceToProduce{ResourceType::GOLD, 1, CardType::NONETYPE}},new CardVictoryPoint{1, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::FINANCIER},ResourceType::GOLD));

    // Controle du climat
    std::shared_ptr<DevelopmentCard> controlDuClimat(new DevelopmentCard ("Controle du climat",{new ResourceToProduce{ResourceType::ENERGY, 2, CardType::NONETYPE},new ResourceToProduce{ResourceType::GOLD, 1, CardType::NONETYPE}},new CardVictoryPoint{2, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::ENERGY));

    std::vector<std::shared_ptr<DevelopmentCard>> cardsOfPlayertoExport = {ameliorationGenetique, animorphes, aquaculture, automateControle, clonageHumain, controlDuClimat};

    playerToExport->setDraftingCards(cardsOfPlayertoExport);

    playerToExport->chooseDraftCard(0);
    playerToExport->chooseDraftCard(0);
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
    for (int i = 0; i < 7; i++)
    {
        std::cout << std::endl;
    }

    std::cout << playerJSON;

    for (int i = 0; i < 7; i++)
    {
        std::cout << std::endl;
    }

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
    ResourceToProduce* firstResourceToProduce = new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE};
    ResourceToProduce* secondResourceToProduce = new ResourceToProduce{ResourceType::ENERGY, 1, CardType::NONETYPE};
    ResourceToProduce* thirdResourceToProduce = new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::NONETYPE};
    std::vector<ResourceToProduce*> productionGainB = {firstResourceToProduce,secondResourceToProduce, thirdResourceToProduce};		

    ResourceToProduce* firstResourceToProduceAZTEC = new ResourceToProduce{ResourceType::ENERGY, 2, CardType::NONETYPE};
    ResourceToProduce* secondResourceToProduceAZTEC = new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::NONETYPE};
    std::vector<ResourceToProduce*> productionGainAZTEC = {firstResourceToProduceAZTEC, secondResourceToProduceAZTEC};
    
    CardVictoryPoint* victoryPointsAZTEC  = new CardVictoryPoint{3, CardType::DISCOVERY};
    std::shared_ptr<EmpireCard> aztec (new EmpireCard("AZTEC", productionGainAZTEC, victoryPointsAZTEC, productionGainB, AZTEC, true));

    // Giving the empire to the player
    myFirstPlayer->setEmpire(aztec);

    // Defining multiple cards to fully test all functions
    // Card that produces 1 SCIENCE * DISCOVERY cards, 10 victory points, 2 instant KRYSTALLIUM
    // Need to pay 1 EXPLORATION
    std::shared_ptr<DevelopmentCard> anciensAstronautes(new DevelopmentCard ("Anciens Astronautes",{new ResourceToProduce{ResourceType::SCIENCE,1, CardType::DISCOVERY}},new CardVictoryPoint{10, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}},{ResourceType::KRYSTALLIUM,ResourceType::KRYSTALLIUM},ResourceType::SCIENCE));


    // Card that produces 3 EXPLORATION, 2 victory points per DISCOVERY card, 1 instant COLONEL
    // Need to pay 1 ENERGY
    std::shared_ptr<DevelopmentCard> basePolaire(new DevelopmentCard ("Base polaire",{new ResourceToProduce{ResourceType::EXPLORATION, 3, CardType::NONETYPE}},new CardVictoryPoint{2, (int) CardType::DISCOVERY},CardType::PROJECT,1,{new ResourceToPay{ResourceType::ENERGY, false}},{ResourceType::COLONEL},ResourceType::EXPLORATION));

    // Card that produces nothing, 1 victory points per COLONEL
    // Need to pay 1 SCIENCE
    std::shared_ptr<DevelopmentCard> automateControle(new DevelopmentCard ("Automates de controle",{},new CardVictoryPoint{1, (int) ResourceType::COLONEL},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::GOLD));

    // Card that produces nothing, 1 victory points per FINANCIER, 1 instant FINANCIER
    // Need to pay 1 ENERGY
    std::shared_ptr<DevelopmentCard> ascenseurSpatial(new DevelopmentCard ("Ascenseur spatial",{},new CardVictoryPoint{1, (int) ResourceType::FINANCIER},CardType::PROJECT,1,{new ResourceToPay{ResourceType::ENERGY, false}},{ResourceType::FINANCIER},ResourceType::ENERGY));

    // Card that will be discard in toBuildCards
    // Giving 1 EXPLORATION
    std::shared_ptr<DevelopmentCard> zeppelinToBuild(new DevelopmentCard ("Zeppelin",{new ResourceToProduce{ResourceType::EXPLORATION,1, CardType::NONETYPE}},new CardVictoryPoint{0, CardType::NONETYPE},CardType::VEHICLE,6,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}},{},ResourceType::EXPLORATION));

    // Card that will be discard in draftCards
    // Giving 1 EXPLORATION
    std::shared_ptr<DevelopmentCard> zeppelinDraft(new DevelopmentCard ("Zeppelin",{new ResourceToProduce{ResourceType::EXPLORATION,1, CardType::NONETYPE}},new CardVictoryPoint{0, CardType::NONETYPE},CardType::VEHICLE,6,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}},{},ResourceType::EXPLORATION));

    //Card that will remain in draftingCards
    std::shared_ptr<DevelopmentCard> zeppelinDrafting(new DevelopmentCard ("Zeppelin",{new ResourceToProduce{ResourceType::EXPLORATION,1, CardType::NONETYPE}},new CardVictoryPoint{0, CardType::NONETYPE},CardType::VEHICLE,6,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}},{},ResourceType::EXPLORATION));

    // Adding cards in the drafting deck
    std::vector<std::shared_ptr<DevelopmentCard>> draftingDeck;
    draftingDeck.push_back(zeppelinDrafting);
    draftingDeck.push_back(zeppelinDraft);
    draftingDeck.push_back(zeppelinToBuild);
    draftingDeck.push_back(ascenseurSpatial);
    draftingDeck.push_back(automateControle);
    draftingDeck.push_back(basePolaire);
    draftingDeck.push_back(anciensAstronautes);

    myFirstPlayer->setDraftingCards(draftingDeck);
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftingCards().size(), 7);

    // Choosing the DraftCards
    for(int i=1; i<(int)draftingDeck.size(); i++)
    {
        myFirstPlayer->chooseDraftCard(1);
        int stringCompare = strcmp(draftingDeck.at(i)->getName().data(), myFirstPlayer->getDraftCards().at(i-1)->getName().data());
        BOOST_CHECK_EQUAL(stringCompare, 0);
    }
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftingCards().size(), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftCards().size(), 6);

    // Choosing out of bound draft card
    myFirstPlayer->chooseDraftCard(42);

    // Choosing the toBuildCards
    std::vector<std::shared_ptr<DevelopmentCard>> draftDeck = myFirstPlayer->getDraftCards();
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
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(ENERGY), 2);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(SCIENCE), 1);

    // Transferring the to produce resources to the possessed resources
    myFirstPlayer->receiveResources(MATERIAL, myFirstPlayer->getResourcesProduction().at(MATERIAL));
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(MATERIAL), 0);
    myFirstPlayer->receiveResources(ENERGY, myFirstPlayer->getResourcesProduction().at(ENERGY));
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(ENERGY), 2);
    myFirstPlayer->receiveResources(SCIENCE, myFirstPlayer->getResourcesProduction().at(SCIENCE));
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(SCIENCE), 1);
    myFirstPlayer->receiveResources(GOLD, myFirstPlayer->getResourcesProduction().at(GOLD));
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(GOLD), 0);
    myFirstPlayer->receiveResources(EXPLORATION, myFirstPlayer->getResourcesProduction().at(EXPLORATION));
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(EXPLORATION), 1);

    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(COLONEL), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(FINANCIER), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(KRYSTALLIUM), 0);

    // Checking if resources of a type can be added to a card
    BOOST_CHECK_EQUAL(myFirstPlayer->isResourcePlayable(ENERGY), true);
    BOOST_CHECK_EQUAL(myFirstPlayer->isResourcePlayable(GOLD), false);

    // Constructing cards
    myFirstPlayer->addResource(ENERGY, 1);
    int stringCompare = strcmp(myFirstPlayer->getBuiltCards().at(0)->getName().data(), "Ascenseur spatial");
    BOOST_CHECK_EQUAL(stringCompare, 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getBuiltCards().size(), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getToBuildCards().size(), 4);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(ENERGY), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(FINANCIER), 1);

    myFirstPlayer->addResource(SCIENCE, 1);
    stringCompare = strcmp(myFirstPlayer->getBuiltCards().at(1)->getName().data(), "Automates de controle");
    BOOST_CHECK_EQUAL(stringCompare, 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getBuiltCards().size(), 2);
    BOOST_CHECK_EQUAL(myFirstPlayer->getToBuildCards().size(), 3);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(SCIENCE), 0);

    myFirstPlayer->addResource(ENERGY, 1);
    stringCompare = strcmp(myFirstPlayer->getBuiltCards().at(2)->getName().data(), "Base polaire");
    BOOST_CHECK_EQUAL(stringCompare, 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getBuiltCards().size(), 3);
    BOOST_CHECK_EQUAL(myFirstPlayer->getToBuildCards().size(), 2);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(ENERGY), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(COLONEL), 1);

    myFirstPlayer->addResource(EXPLORATION, 1);
    stringCompare = strcmp(myFirstPlayer->getBuiltCards().at(3)->getName().data(), "Anciens Astronautes");
    BOOST_CHECK_EQUAL(stringCompare, 0);
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
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(ENERGY), 2);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(SCIENCE), 2);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(GOLD), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(EXPLORATION), 3);

    // Transferring again the to produce resources to the possessed resources
    myFirstPlayer->receiveResources(MATERIAL, myFirstPlayer->getResourcesProduction().at(MATERIAL));
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(MATERIAL), 0);
    myFirstPlayer->receiveResources(ENERGY, myFirstPlayer->getResourcesProduction().at(ENERGY));
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(ENERGY), 2);
    myFirstPlayer->receiveResources(SCIENCE, myFirstPlayer->getResourcesProduction().at(SCIENCE));
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(SCIENCE), 2);
    myFirstPlayer->receiveResources(GOLD, myFirstPlayer->getResourcesProduction().at(GOLD));
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(GOLD), 0);
    myFirstPlayer->receiveResources(EXPLORATION, myFirstPlayer->getResourcesProduction().at(EXPLORATION));
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(EXPLORATION), 3);

    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(COLONEL), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(FINANCIER), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(KRYSTALLIUM), 2);

    // Compute victory points
    int victoryPoints = myFirstPlayer->computeVictoryPoint();
    BOOST_CHECK_EQUAL(victoryPoints, 17);

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

    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesInEmpireUnit(), 3);

    // Testing the error return of sendResourceToEmpire
    myFirstPlayer->sendResourceToEmpire(GOLD);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(GOLD), 0);

    // Testing end the planification
    draftingDeck = {zeppelinDraft};
    myFirstPlayer->setDraftingCards(draftingDeck);
    myFirstPlayer->chooseDraftCard(0);
    stringCompare = strcmp(draftingDeck.at(0)->getName().data(), myFirstPlayer->getDraftCards().at(0)->getName().data());
    BOOST_CHECK_EQUAL(stringCompare, 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftCards().size(), 1);

    myFirstPlayer->endPlanification();
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftCards().size(), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getToBuildCards().size(), 1);

    // Test convertKrystallium
    myFirstPlayer->convertKrystallium(MATERIAL);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(MATERIAL), 1);

    myFirstPlayer->convertKrystallium(COLONEL);


    // Test chooseColonel (not implemented yet)
    BOOST_CHECK_EQUAL(myFirstPlayer->isPreferedPersonnageColonel(), true);

    //Test the setter of the player's state
    myFirstPlayer->setState(PLAYING);
    BOOST_CHECK_EQUAL(PLAYING, myFirstPlayer->getState());

    myFirstPlayer->setPreferedPersonnage(COLONEL);
    BOOST_CHECK_EQUAL(myFirstPlayer->isRealPlayerAndPlaying(), true);

/*
    // Testing different empire configuration
    // Config two
    firstResourceToProduceAZTEC = new ResourceToProduce{ResourceType::ENERGY, 4, CardType::DISCOVERY};
    productionGainAZTEC = {firstResourceToProduceAZTEC};
    victoryPointsAZTEC  = new CardVictoryPoint{2, ResourceType::FINANCIER};
    aztec = std::make_shared<EmpireCard>(new EmpireCard("AZTEC", productionGainAZTEC, victoryPointsAZTEC, productionGainB, AZTEC, true));

    myFirstPlayer->setEmpire(aztec);

    myFirstPlayer->updateProduction();
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(MATERIAL), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(ENERGY), 4);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(SCIENCE), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(GOLD), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(EXPLORATION), 3);

    victoryPoints = myFirstPlayer->computeVictoryPoint();
    BOOST_CHECK_EQUAL(victoryPoints, 16);

    // Config three
    victoryPointsAZTEC  = new CardVictoryPoint{8, ResourceType::COLONEL};
    aztec = std::make_shared<EmpireCard>(new EmpireCard("AZTEC", productionGainAZTEC, victoryPointsAZTEC, productionGainB, AZTEC, true));

    myFirstPlayer->setEmpire(aztec);

    myFirstPlayer->updateProduction();
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(MATERIAL), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(ENERGY), 4);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(SCIENCE), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(GOLD), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(EXPLORATION), 3);

    victoryPoints = myFirstPlayer->computeVictoryPoint();
    BOOST_CHECK_EQUAL(victoryPoints, 22);

    // Config four (last one)
    victoryPointsAZTEC  = new CardVictoryPoint{26, CardType::NONETYPE};
    aztec = std::make_shared<EmpireCard>(new EmpireCard("AZTEC", productionGainAZTEC, victoryPointsAZTEC, productionGainB, AZTEC, true));

    myFirstPlayer->setEmpire(aztec);

    myFirstPlayer->updateProduction();
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(MATERIAL), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(ENERGY), 4);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(SCIENCE), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(GOLD), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(EXPLORATION), 3);

    victoryPoints = myFirstPlayer->computeVictoryPoint();
    BOOST_CHECK_EQUAL(victoryPoints, 40);
*/
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

    (void)myFirstPlayer->isAI();

    // Testing void AI functions
    myFirstPlayer->AIChooseDraftingCard();
    myFirstPlayer->AIPlanification();
    myFirstPlayer->AIUseProducedResources();

    // Delete pointers that won't be used anymore.
    delete myFirstPlayer;
}

/* vim: set sw=2 sts=2 et : */