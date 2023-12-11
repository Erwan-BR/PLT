#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Player.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(firstPlayerTest)
{
  {
    // Testing the empty contructor of Player
    Player* myFirstPlayer = new Player();
    myFirstPlayer = new Player("Maxime", 1, sf::Texture());

    //Elements to test the methods :
    std::vector<ResourceToProduce*> resourceProd1;
    ResourceToProduce* production1 = new ResourceToProduce{MATERIAL, 2, NONETYPE};
    resourceProd1.push_back(production1);
    std::vector<ResourceToPay*> resourcePay1;
    ResourceToPay* paiement1 = new ResourceToPay{MATERIAL, false};
    resourcePay1.push_back(paiement1);
    std::vector<ResourceType> instantGain1;
    instantGain1.push_back(SCIENCE);
    CardVictoryPoint* victoryPoints1 = new CardVictoryPoint{2,NONETYPE};
    DevelopmentCard* cardTest1 = new DevelopmentCard("CardTest1", resourceProd1, sf::Texture(), victoryPoints1, STRUCTURE, 1, resourcePay1, instantGain1, GOLD);

    std::vector<ResourceToProduce*> resourceProd2;
    ResourceToProduce* production2 = new ResourceToProduce{ENERGY, 1, STRUCTURE};
    resourceProd2.push_back(production2);
    std::vector<ResourceToPay*> resourcePay2;
    ResourceToPay* paiement2 = new ResourceToPay{EXPLORATION, false};
    resourcePay2.push_back(paiement2);
    std::vector<ResourceType> instantGain2;
    instantGain2.push_back(GOLD);
    CardVictoryPoint* victoryPoints2 = new CardVictoryPoint{1,FINANCIER};
    DevelopmentCard* cardTest2 = new DevelopmentCard("CardTest2", resourceProd2, sf::Texture(), victoryPoints2, PROJECT, 2, resourcePay2, instantGain2, SCIENCE);
    
    
    std::vector<ResourceToProduce*> resourceProd3;
    ResourceToProduce* production3 = new ResourceToProduce{ENERGY, 1, STRUCTURE};
    resourceProd3.push_back(production3);
    std::vector<ResourceToPay*> resourcePay3;
    ResourceToPay* paiement3 = new ResourceToPay{EXPLORATION, true};
    resourcePay3.push_back(paiement3);
    std::vector<ResourceType> instantGain3;
    instantGain3.push_back(GOLD);
    CardVictoryPoint* victoryPoints3 = new CardVictoryPoint{1,FINANCIER};
    DevelopmentCard* cardTest3 = new DevelopmentCard("CardTest3", resourceProd3, sf::Texture(), victoryPoints3, PROJECT, 2, resourcePay3, instantGain3, SCIENCE);
  
    std::vector<ResourceToProduce*> resourceProd4;
    ResourceToProduce* production4 = new ResourceToProduce{ENERGY, 1, STRUCTURE};
    resourceProd4.push_back(production4);
    std::vector<ResourceToPay*> resourcePay4;
    ResourceToPay* paiement4 = new ResourceToPay{EXPLORATION, true};
    resourcePay4.push_back(paiement4);
    std::vector<ResourceType> instantGain4;
    instantGain4.push_back(GOLD);
    CardVictoryPoint* victoryPoints4 = new CardVictoryPoint{1,COLONEL};
    DevelopmentCard* cardTest4 = new DevelopmentCard("CardTest4", resourceProd4, sf::Texture(), victoryPoints4, STRUCTURE, 2, resourcePay4, instantGain4, SCIENCE);
      
    std::vector<ResourceToProduce*> resourceProd5;
    ResourceToProduce* production5 = new ResourceToProduce{ENERGY, 1, STRUCTURE};
    resourceProd5.push_back(production5);
    std::vector<ResourceToPay*> resourcePay5;
    ResourceToPay* paiement5 = new ResourceToPay{EXPLORATION, true};
    resourcePay5.push_back(paiement5);
    std::vector<ResourceType> instantGain5;
    instantGain5.push_back(GOLD);
    CardVictoryPoint* victoryPoints5 = new CardVictoryPoint{1,FINANCIER};
    DevelopmentCard* cardTest5 = new DevelopmentCard("CardTest5", resourceProd5, sf::Texture(), victoryPoints5, PROJECT, 2, resourcePay5, instantGain5, SCIENCE);
    
    std::vector<ResourceToProduce*> resourceProd6;
    ResourceToProduce* production6 = new ResourceToProduce{ENERGY, 1, STRUCTURE};
    resourceProd6.push_back(production6);
    std::vector<ResourceToPay*> resourcePay6;
    ResourceToPay* paiement6 = new ResourceToPay{EXPLORATION, true};
    resourcePay6.push_back(paiement6);
    std::vector<ResourceType> instantGain6;
    instantGain6.push_back(GOLD);
    CardVictoryPoint* victoryPoints6 = new CardVictoryPoint{1,FINANCIER};
    DevelopmentCard* cardTest6 = new DevelopmentCard("CardTest6", resourceProd6, sf::Texture(), victoryPoints6, PROJECT, 2, resourcePay6, instantGain6, SCIENCE);
    
    std::vector<ResourceToProduce*> resourceProd7;
    ResourceToProduce* production7 = new ResourceToProduce{ENERGY, 1, STRUCTURE};
    resourceProd7.push_back(production7);
    std::vector<ResourceToPay*> resourcePay7;
    ResourceToPay* paiement7 = new ResourceToPay{EXPLORATION, true};
    resourcePay7.push_back(paiement7);
    std::vector<ResourceType> instantGain7;
    instantGain7.push_back(GOLD);
    CardVictoryPoint* victoryPoints7 = new CardVictoryPoint{1,FINANCIER};
    DevelopmentCard* cardTest7 = new DevelopmentCard("CardTest7", resourceProd7, sf::Texture(), victoryPoints7, PROJECT, 2, resourcePay7, instantGain7, SCIENCE);
 
    std::vector<ResourceToProduce*> resourceProd9;
    ResourceToProduce* production9 = new ResourceToProduce{ENERGY, 1, STRUCTURE};
    resourceProd9.push_back(production9);
    std::vector<ResourceToPay*> resourcePay9;
    ResourceToPay* paiement9 = new ResourceToPay{EXPLORATION, true};
    resourcePay9.push_back(paiement9);
    std::vector<ResourceType> instantGain9;
    instantGain9.push_back(GOLD);
    CardVictoryPoint* victoryPoints9 = new CardVictoryPoint{1,STRUCTURE};
    DevelopmentCard* cardTest9 = new DevelopmentCard("CardTest9", resourceProd9, sf::Texture(), victoryPoints9, PROJECT, 2, resourcePay9, instantGain9, SCIENCE);

    std::vector<ResourceToProduce*> resourceProd8;
    ResourceToProduce* production8 = new ResourceToProduce{ENERGY, 1, STRUCTURE};
    resourceProd8.push_back(production8);
    std::vector<ResourceToPay*> resourcePay8;
    ResourceToPay* paiement8 = new ResourceToPay{EXPLORATION, true};
    resourcePay8.push_back(paiement8);
    std::vector<ResourceType> instantGain8;
    instantGain8.push_back(GOLD);
    CardVictoryPoint* victoryPoints8 = new CardVictoryPoint{1,STRUCTURE};
    DevelopmentCard* cardTest8 = new DevelopmentCard("CardTest8", resourceProd8, sf::Texture(), victoryPoints8, PROJECT, 2, resourcePay8, instantGain8, SCIENCE);

    std::vector<DevelopmentCard*> draftingDeck;
    draftingDeck.push_back(cardTest1);
    draftingDeck.push_back(cardTest2);
    draftingDeck.push_back(cardTest3);
    draftingDeck.push_back(cardTest4);
    draftingDeck.push_back(cardTest5);
    draftingDeck.push_back(cardTest6);
    draftingDeck.push_back(cardTest7);
    draftingDeck.push_back(cardTest8);
    draftingDeck.push_back(cardTest9);
    

    //Testing method setDraftinCards :
    myFirstPlayer->setDraftingCards(draftingDeck);
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftingCards().size(), draftingDeck.size());


    //Testing method setEmpire :
		ResourceToProduce* firstResourceToProduceAFRICA = new ResourceToProduce{ResourceType::MATERIAL, 2, state::CardType::NONETYPE};
    ResourceToProduce* secondResourceToProduceAFRICA = new ResourceToProduce{ResourceType::EXPLORATION, 1, state::CardType::STRUCTURE};
		std::vector<ResourceToProduce*> productionGainAFRICA = {firstResourceToProduceAFRICA,secondResourceToProduceAFRICA};
		sf::Texture designAFRICA;
   	CardVictoryPoint* victoryPointsAFRICA  = new CardVictoryPoint{3,state::CardType::DISCOVERY};
		EmpireCard* africa = new EmpireCard("AFRICA", productionGainAFRICA, designAFRICA, victoryPointsAFRICA, {/*prob face B*/}, {/*victorypoints face B*/}, AFRICA); 
    myFirstPlayer->setEmpire(africa);
    BOOST_CHECK_EQUAL(myFirstPlayer->getEmpire(), africa);



    //Testing method chooseDraftCard :
    myFirstPlayer->chooseDraftCard(cardTest1);
    myFirstPlayer->chooseDraftCard(cardTest2);
    myFirstPlayer->chooseDraftCard(cardTest3);
    myFirstPlayer->chooseDraftCard(cardTest4);
    myFirstPlayer->chooseDraftCard(cardTest5);
    myFirstPlayer->chooseDraftCard(cardTest6);
    myFirstPlayer->chooseDraftCard(cardTest8);
    myFirstPlayer->chooseDraftCard(cardTest9);


    //Testing method keepCard :
    myFirstPlayer->keepCard(cardTest1);
    myFirstPlayer->keepCard(cardTest2);
    myFirstPlayer->keepCard(cardTest3);
    myFirstPlayer->keepCard(cardTest4);
    myFirstPlayer->keepCard(cardTest8);
    myFirstPlayer->keepCard(cardTest9);
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftCards().size(), 2);
    BOOST_CHECK_EQUAL(myFirstPlayer->getToBuildCards().size(), 6);


    //Testing method discardCard :
    myFirstPlayer->discardCard(cardTest6);
    myFirstPlayer->discardCard(cardTest9);
    BOOST_CHECK_EQUAL(myFirstPlayer->getDraftCards().size(), 1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getToBuildCards().size(), 5);



    //Testing method addResource :
    myFirstPlayer->addResource(MATERIAL, cardTest1);
    BOOST_CHECK_EQUAL(myFirstPlayer->getToBuildCards().size(), 4);
    BOOST_CHECK_EQUAL(myFirstPlayer->getBuiltCards().size(), 1);


    //Testing method construct :
    myFirstPlayer->construct(cardTest3);
    myFirstPlayer->construct(cardTest4);
    myFirstPlayer->construct(cardTest8);
    BOOST_CHECK_EQUAL(myFirstPlayer->getBuiltCards().size(), 4);


    //Testing method receiveResource and receiveResources:
    myFirstPlayer->receiveResources(GOLD,3);


    //Testing method chooseColonelToken :
    (void)myFirstPlayer->chooseColonelToken();


    //Testing method computeVictoryPoint :
    (void)myFirstPlayer->computeVictoryPoint();

    victoryPointsAFRICA  = new CardVictoryPoint{1,state::ResourceType::COLONEL};
		africa = new EmpireCard("AFRICA", productionGainAFRICA, designAFRICA, victoryPointsAFRICA, {}, {}, AFRICA); 
		myFirstPlayer->setEmpire(africa);
    BOOST_CHECK_EQUAL(myFirstPlayer->getEmpire(), africa);
    (void)myFirstPlayer->computeVictoryPoint();

    victoryPointsAFRICA  = new CardVictoryPoint{1,state::ResourceType::FINANCIER};
		africa = new EmpireCard("AFRICA", productionGainAFRICA, designAFRICA, victoryPointsAFRICA, {}, {}, AFRICA); 
		myFirstPlayer->setEmpire(africa);
    BOOST_CHECK_EQUAL(myFirstPlayer->getEmpire(), africa);
    (void)myFirstPlayer->computeVictoryPoint();

    victoryPointsAFRICA  = new CardVictoryPoint{1,state::CardType::NONETYPE};
		africa = new EmpireCard("AFRICA", productionGainAFRICA, designAFRICA, victoryPointsAFRICA, {}, {}, AFRICA); 
		myFirstPlayer->setEmpire(africa);
    BOOST_CHECK_EQUAL(myFirstPlayer->getEmpire(), africa);
    (void)myFirstPlayer->computeVictoryPoint();


    //Testing method sendResourceToEmpire :
    myFirstPlayer->sendResourceToEmpire(MATERIAL);
    myFirstPlayer->sendResourceToEmpire(MATERIAL);
    myFirstPlayer->sendResourceToEmpire(MATERIAL);
    myFirstPlayer->sendResourceToEmpire(MATERIAL);
    myFirstPlayer->sendResourceToEmpire(MATERIAL);


    //Testing method convertToKrystallium :
    myFirstPlayer->convertToKrystallium();

    //Testing method updateProduction :
    myFirstPlayer->updateProduction();

    //Testing method toString :
    (void)myFirstPlayer->toString();

    myFirstPlayer->setState(PENDING);
    BOOST_CHECK_EQUAL(myFirstPlayer->getState(), PENDING);

    //Testing getters:
    (void)myFirstPlayer->getProductionGain(MATERIAL);
    (void)myFirstPlayer->getName();
    (void)myFirstPlayer->getProfilePicture();
    (void)myFirstPlayer->getEmpire();
    (void)myFirstPlayer->getBuiltCards();
    (void)myFirstPlayer->getToBuildCards();
    (void)myFirstPlayer->getDraftingCards();
    (void)myFirstPlayer->getDraftCards();
    (void)myFirstPlayer->getState();
    (void)myFirstPlayer->getFinancierTokensUnit();
    (void)myFirstPlayer->getColonelTokensUnit();
    (void)myFirstPlayer->getKrystalliumTokensUnit();
    (void)myFirstPlayer->getCurrentResources();
    (void)myFirstPlayer->getResourcesInEmpireUnit();
    (void)myFirstPlayer->getResourcesProduction();
    (void)myFirstPlayer->getCardsTypeList();


    // Delete pointers that won't be used anymore.
    delete myFirstPlayer;
  }
}

/* vim: set sw=2 sts=2 et : */