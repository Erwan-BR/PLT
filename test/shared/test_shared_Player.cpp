#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Player.h"
#include "../../src/shared/state/Game.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(firstPlayerTest)
{
  {
    // Testing the empty contructor of Player
    sf::Texture* profilePicture = new sf::Texture();
    Player* myFirstPlayer = new Player("Maxime", 1, profilePicture);

    //Defining Empire
      //Producing 2 ENERGY, 1 SCIENCE, gain 3 victory points per DISCOVERY cards
    ResourceToProduce* firstResourceToProduce = new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE};
		ResourceToProduce* secondResourceToProduce = new ResourceToProduce{ResourceType::ENERGY, 1, CardType::NONETYPE};
		ResourceToProduce* thirdResourceToProduce = new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::NONETYPE};
		std::vector<ResourceToProduce*> productionGainB = {firstResourceToProduce,secondResourceToProduce, thirdResourceToProduce};		

		ResourceToProduce* firstResourceToProduceAZTEC = new ResourceToProduce{ResourceType::ENERGY, 2, CardType::NONETYPE};
    ResourceToProduce* secondResourceToProduceAZTEC = new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::NONETYPE};
		std::vector<ResourceToProduce*> productionGainAZTEC = {firstResourceToProduceAZTEC, secondResourceToProduceAZTEC};
		sf::Texture* designAZTEC = new sf::Texture;
		designAZTEC->loadFromFile("./resources/img/Cards/Empire_Face_A/Azteca.png");
		sf::Texture* designAZTEC_FaceB = new sf::Texture;
		designAZTEC_FaceB->loadFromFile("./resources/img/Cards/Empire_Face_B/Azteca.png");
		CardVictoryPoint* victoryPointsAZTEC  = new CardVictoryPoint{3, CardType::DISCOVERY};
		EmpireCard* aztec = new EmpireCard("AZTEC", productionGainAZTEC, designAZTEC, victoryPointsAZTEC, productionGainB, {0}, AZTEC, designAZTEC_FaceB, true);

    //Giving the empire to the player
    myFirstPlayer->setEmpire(aztec);

    //Definiing multiple cards to fully test all functions
      //Card that produces 1 SCIENCE * DISCOVERY cards, 10 victory points, 2 instant KRYSTALLIUM
      //Need to pay 1 EXPLORATION
    sf::Texture* designAnciensAstronautes = new sf::Texture;
    designAnciensAstronautes->loadFromFile("./resources/img/Cards/Development_Cards/anciens_astronautes.png");
    DevelopmentCard* anciensAstronautes = new DevelopmentCard ("Anciens Astronautes",{new ResourceToProduce{ResourceType::SCIENCE,1, CardType::DISCOVERY}},designAnciensAstronautes,new CardVictoryPoint{10, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}},{ResourceType::KRYSTALLIUM,ResourceType::KRYSTALLIUM},ResourceType::SCIENCE);


      //Card that produces 3 EXPLORATION, 2 victory points per DISCOVERY card, 1 instant COLONEL
      //Need to pay 1 ENERGY
    sf::Texture* designBasePolaire = new sf::Texture;
    designBasePolaire->loadFromFile("./resources/img/Cards/Development_Cards/base_polaire.png");
    DevelopmentCard* basePolaire = new DevelopmentCard ("Base polaire",{new ResourceToProduce{ResourceType::EXPLORATION, 3, CardType::NONETYPE}},designBasePolaire,new CardVictoryPoint{2, (int) CardType::DISCOVERY},CardType::PROJECT,1,{new ResourceToPay{ResourceType::ENERGY, false}},{ResourceType::COLONEL},ResourceType::EXPLORATION);
        
      //Card that produces nothing, 1 victory points per COLONEL
      //Need to pay 1 SCIENCE
    sf::Texture* designAutomateControle = new sf::Texture;
    designAutomateControle->loadFromFile("./resources/img/Cards/Development_Cards/automates_de_controle.png");
    DevelopmentCard* automateControle = new DevelopmentCard ("Automates de controle",{},designAutomateControle,new CardVictoryPoint{1, (int) ResourceType::COLONEL},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::GOLD);

      //Card that produces nothing, 1 victory points per FINANCIER, 1 instant FINANCIER
      //Need to pay 1 ENERGY
    sf::Texture* designAscenseurSpatial = new sf::Texture;
    designAscenseurSpatial->loadFromFile("./resources/img/Cards/Development_Cards/ascenseur_spatial.png");
    DevelopmentCard* ascenseurSpatial = new DevelopmentCard ("Ascenseur spatial",{},designAscenseurSpatial,new CardVictoryPoint{1, (int) ResourceType::FINANCIER},CardType::PROJECT,1,{new ResourceToPay{ResourceType::ENERGY, false}},{ResourceType::FINANCIER},ResourceType::ENERGY);

      //Card that will be discard in toBuildCards
      //Giving 1 EXPLORATION
    sf::Texture* designZeppelin = new sf::Texture;
    designZeppelin->loadFromFile("./resources/img/Cards/Development_Cards/zeppelin.png");
    DevelopmentCard* zeppelinToBuild = new DevelopmentCard ("Zeppelin",{new ResourceToProduce{ResourceType::EXPLORATION,1, CardType::NONETYPE}},designZeppelin,new CardVictoryPoint{0, CardType::NONETYPE},CardType::VEHICLE,6,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}},{},ResourceType::EXPLORATION);

      //Card that will be discard in draftCards
      //Giving 1 EXPLORATION
    DevelopmentCard* zeppelinDraft = new DevelopmentCard ("Zeppelin",{new ResourceToProduce{ResourceType::EXPLORATION,1, CardType::NONETYPE}},designZeppelin,new CardVictoryPoint{0, CardType::NONETYPE},CardType::VEHICLE,6,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}},{},ResourceType::EXPLORATION);

      //Card that will remain in draftingCards
    DevelopmentCard* zeppelinDrafting = new DevelopmentCard ("Zeppelin",{new ResourceToProduce{ResourceType::EXPLORATION,1, CardType::NONETYPE}},designZeppelin,new CardVictoryPoint{0, CardType::NONETYPE},CardType::VEHICLE,6,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}},{},ResourceType::EXPLORATION);

    //Adding cards in the drafting deck
    std::vector<DevelopmentCard*> draftingDeck;
    draftingDeck.push_back(zeppelinDrafting);
    draftingDeck.push_back(zeppelinDraft);
    draftingDeck.push_back(zeppelinToBuild);
    draftingDeck.push_back(ascenseurSpatial);
    draftingDeck.push_back(automateControle);
    draftingDeck.push_back(basePolaire);
    draftingDeck.push_back(anciensAstronautes);

    myFirstPlayer->setDraftingCards(draftingDeck);
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftingCards().size(), 7);

    //Choosing the DraftCards
    for(int i=1; i<(int)draftingDeck.size(); i++)
    {
      myFirstPlayer->chooseDraftCard(1);
      int stringCompare = strcmp(draftingDeck.at(i)->getName().data(), myFirstPlayer->getDraftCards().at(i-1)->getName().data());
      BOOST_CHECK_EQUAL(stringCompare, 0);
    }
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftingCards().size(), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftCards().size(), 6);

    //Choosing out of bound draft card
    myFirstPlayer->chooseDraftCard(42);

    //Choosing the toBuildCards
    std::vector<DevelopmentCard*> draftDeck = myFirstPlayer->getDraftCards();
    for(int i=1; i<6; i++)
    {
      myFirstPlayer->keepCard(1);
      int stringCompare = strcmp(myFirstPlayer->getToBuildCards().at(i-1)->getName().data(), draftDeck.at(i)->getName().data());
      BOOST_CHECK_EQUAL(stringCompare, 0);   
    }
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftCards().size(), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getToBuildCards().size(), 5);

    //Choosing out of bound keep card
    myFirstPlayer->keepCard(42);

    //Discarding the last drafted Card
    myFirstPlayer->discardCard(0,true);
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftCards().size(), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(EXPLORATION), 1);

    //Discarding out of bound card
    myFirstPlayer->discardCard(42, true);

    //Production phase with empire only
    myFirstPlayer->updateProduction();
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(ENERGY), 2);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(SCIENCE), 1);

    //Transferring the to produce resources to the possessed resources
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

    //Checking if resources of a type can be added to a card
    BOOST_CHECK_EQUAL(myFirstPlayer->isResourcePlayable(ENERGY), true);
    BOOST_CHECK_EQUAL(myFirstPlayer->isResourcePlayable(GOLD), false);

    //Constructing cards
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

    //Out of bound addResource test
    myFirstPlayer->addResource(ENERGY, 1);

    //Discarding last card of toBuild deck
    myFirstPlayer->discardCard(0, false);
    BOOST_CHECK_EQUAL(myFirstPlayer->getToBuildCards().size(), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesInEmpireUnit(), 1);

    //Discarding out of bound card
    myFirstPlayer->discardCard(42, false);

    //Recompute production
    myFirstPlayer->updateProduction();
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(MATERIAL), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(ENERGY), 2);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(SCIENCE), 2);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(GOLD), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(EXPLORATION), 3);

    //Transferring again the to produce resources to the possessed resources
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

    //Compute victory points
    int victoryPoints = myFirstPlayer->computeVictoryPoint();
    BOOST_CHECK_EQUAL(victoryPoints, 17);

    //Ending the production
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

    //Testing the error return of sendResourceToEmpire
    myFirstPlayer->sendResourceToEmpire(GOLD);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(GOLD), 0);

    //Testing end the planification
    draftingDeck = {zeppelinDraft};
    myFirstPlayer->setDraftingCards(draftingDeck);
    myFirstPlayer->chooseDraftCard(0);
    stringCompare = strcmp(draftingDeck.at(0)->getName().data(), myFirstPlayer->getDraftCards().at(0)->getName().data());
    BOOST_CHECK_EQUAL(stringCompare, 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftCards().size(), 1);

    myFirstPlayer->endPlanification();
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftCards().size(), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getToBuildCards().size(), 1);

    //Test convertKrystallium
    myFirstPlayer->convertKrystallium(MATERIAL);
    BOOST_CHECK_EQUAL(myFirstPlayer->getCurrentResources().at(MATERIAL), 1);

    myFirstPlayer->convertKrystallium(COLONEL);


    //Test chooseColonel (not implemented yet)
    bool isColonel = myFirstPlayer->chooseColonelToken();
    BOOST_CHECK_EQUAL(isColonel, false);

    //Test the setter of the player's state
    myFirstPlayer->setState(PLAYING);
    BOOST_CHECK_EQUAL(PLAYING, myFirstPlayer->getState());

    //Testing different empire configuration
      //Config two
    firstResourceToProduceAZTEC = new ResourceToProduce{ResourceType::ENERGY, 4, CardType::DISCOVERY};
		productionGainAZTEC = {firstResourceToProduceAZTEC};
		victoryPointsAZTEC  = new CardVictoryPoint{2, ResourceType::FINANCIER};
		aztec = new EmpireCard("AZTEC", productionGainAZTEC, designAZTEC, victoryPointsAZTEC, productionGainB, {0}, AZTEC, designAZTEC_FaceB, true);

    myFirstPlayer->setEmpire(aztec);

    myFirstPlayer->updateProduction();
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(MATERIAL), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(ENERGY), 4);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(SCIENCE), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(GOLD), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(EXPLORATION), 3);

    victoryPoints = myFirstPlayer->computeVictoryPoint();
    BOOST_CHECK_EQUAL(victoryPoints, 16);

      //Config three
		victoryPointsAZTEC  = new CardVictoryPoint{8, ResourceType::COLONEL};
		aztec = new EmpireCard("AZTEC", productionGainAZTEC, designAZTEC, victoryPointsAZTEC, productionGainB, {0}, AZTEC, designAZTEC_FaceB, true);

    myFirstPlayer->setEmpire(aztec);

    myFirstPlayer->updateProduction();
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(MATERIAL), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(ENERGY), 4);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(SCIENCE), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(GOLD), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(EXPLORATION), 3);

    victoryPoints = myFirstPlayer->computeVictoryPoint();
    BOOST_CHECK_EQUAL(victoryPoints, 22);

          //Config four (last one)
		victoryPointsAZTEC  = new CardVictoryPoint{26, CardType::NONETYPE};
		aztec = new EmpireCard("AZTEC", productionGainAZTEC, designAZTEC, victoryPointsAZTEC, productionGainB, {0}, AZTEC, designAZTEC_FaceB, true);

    myFirstPlayer->setEmpire(aztec);

    myFirstPlayer->updateProduction();
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(MATERIAL), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(ENERGY), 4);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(SCIENCE), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(GOLD), 0);
    BOOST_CHECK_EQUAL(myFirstPlayer->getResourcesProduction().at(EXPLORATION), 3);

    victoryPoints = myFirstPlayer->computeVictoryPoint();
    BOOST_CHECK_EQUAL(victoryPoints, 40);

    //Testing getters
    (void)myFirstPlayer->getProductionGain(MATERIAL);
    (void)myFirstPlayer->getName();
    (void)myFirstPlayer->getProfilePicture();
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

    //Testing void AI functions
    myFirstPlayer->AIChooseDraftingCard();
    myFirstPlayer->AIPlanification();
    myFirstPlayer->AIUseProducedResources();

    // Delete pointers that won't be used anymore.
    delete myFirstPlayer;
  }
}

/* vim: set sw=2 sts=2 et : */