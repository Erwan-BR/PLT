#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Player.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(firstPlayerTest)
{
  {
    // Testing the empty contructor of Player
    Player* myFirstPlayer = new Player();

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
    DevelopmentCard* cardTest1 = new DevelopmentCard ("CardTest1", resourceProd1, sf::Texture(), victoryPoints1, STRUCTURE, 1, resourcePay1, instantGain1, GOLD);

    std::vector<ResourceToProduce*> resourceProd2;
    ResourceToProduce* production2 = new ResourceToProduce{ENERGY, 1, STRUCTURE};
    resourceProd2.push_back(production2);
    std::vector<ResourceToPay*> resourcePay2;
    ResourceToPay* paiement2 = new ResourceToPay{EXPLORATION, false};
    resourcePay2.push_back(paiement2);
    std::vector<ResourceType> instantGain2;
    instantGain2.push_back(GOLD);
    CardVictoryPoint* victoryPoints2 = new CardVictoryPoint{1,FINANCIER};
    DevelopmentCard* cardTest2 = new DevelopmentCard ("CardTest2", resourceProd2, sf::Texture(), victoryPoints2, PROJECT, 2, resourcePay2, instantGain2, SCIENCE);
    
    
    std::vector<ResourceToProduce*> resourceProd3;
    ResourceToProduce* production3 = new ResourceToProduce{ENERGY, 1, STRUCTURE};
    resourceProd3.push_back(production3);
    std::vector<ResourceToPay*> resourcePay3;
    ResourceToPay* paiement3 = new ResourceToPay{EXPLORATION, true};
    resourcePay3.push_back(paiement3);
    std::vector<ResourceType> instantGain3;
    instantGain3.push_back(GOLD);
    CardVictoryPoint* victoryPoints3 = new CardVictoryPoint{1,FINANCIER};
    DevelopmentCard* cardTest3 = new DevelopmentCard ("CardTest3", resourceProd3, sf::Texture(), victoryPoints3, PROJECT, 2, resourcePay3, instantGain3, SCIENCE);
    
    
    std::vector<ResourceToProduce*> resourceProd4;
    ResourceToProduce* production4 = new ResourceToProduce{ENERGY, 1, STRUCTURE};
    resourceProd4.push_back(production4);
    std::vector<ResourceToPay*> resourcePay4;
    ResourceToPay* paiement4 = new ResourceToPay{EXPLORATION, true};
    resourcePay4.push_back(paiement4);
    std::vector<ResourceType> instantGain4;
    instantGain4.push_back(GOLD);
    CardVictoryPoint* victoryPoints4 = new CardVictoryPoint{1,COLONEL};
    DevelopmentCard* cardTest4 = new DevelopmentCard ("CardTest4", resourceProd4, sf::Texture(), victoryPoints4, STRUCTURE, 2, resourcePay4, instantGain4, SCIENCE);
    
    DevelopmentCard* cardTest5 = new DevelopmentCard ("CardTest5", resourceProd3, sf::Texture(), victoryPoints3, PROJECT, 2, resourcePay3, instantGain3, SCIENCE);
    DevelopmentCard* cardTest6 = new DevelopmentCard ("CardTest6", resourceProd3, sf::Texture(), victoryPoints3, PROJECT, 2, resourcePay3, instantGain3, SCIENCE);
    DevelopmentCard* cardTest7 = new DevelopmentCard ("CardTest6", resourceProd3, sf::Texture(), victoryPoints3, PROJECT, 2, resourcePay3, instantGain3, SCIENCE);
 
    CardVictoryPoint* victoryPoints8 = new CardVictoryPoint{1,STRUCTURE};
    DevelopmentCard* cardTest8 = new DevelopmentCard ("CardTest6", resourceProd3, sf::Texture(), victoryPoints8, PROJECT, 2, resourcePay3, instantGain3, SCIENCE);

    std::vector<DevelopmentCard*> draftingDeck;
    draftingDeck.push_back(cardTest1);
    draftingDeck.push_back(cardTest2);
    draftingDeck.push_back(cardTest3);
    draftingDeck.push_back(cardTest4);
    draftingDeck.push_back(cardTest5);
    draftingDeck.push_back(cardTest6);
    draftingDeck.push_back(cardTest7);
    draftingDeck.push_back(cardTest8);


    //Testing method setDraftinCards :
    myFirstPlayer->setDraftingCards(draftingDeck);


    //Testing method setEmpire :
		ResourceToProduce* firstResourceToProduceAFRICA = new ResourceToProduce{ResourceType::MATERIAL, 2, state::CardType::NONETYPE};
    ResourceToProduce* secondResourceToProduceAFRICA = new ResourceToProduce{ResourceType::EXPLORATION, 1, state::CardType::STRUCTURE};
		std::vector<ResourceToProduce*> productionGainAFRICA = {firstResourceToProduceAFRICA,secondResourceToProduceAFRICA};
		sf::Texture designAFRICA;
   	CardVictoryPoint* victoryPointsAFRICA  = new CardVictoryPoint{3,state::CardType::DISCOVERY};
		EmpireCard* africa = new EmpireCard("AFRICA", productionGainAFRICA, designAFRICA, victoryPointsAFRICA, {/*prob face B*/}, {/*victorypoints face B*/}, AFRICA); 
    myFirstPlayer->setEmpire(africa);


    //Testing method chooseDraftCard :
    myFirstPlayer->chooseDraftCard(cardTest1);
    myFirstPlayer->chooseDraftCard(cardTest2);
    myFirstPlayer->chooseDraftCard(cardTest3);
    myFirstPlayer->chooseDraftCard(cardTest4);
    myFirstPlayer->chooseDraftCard(cardTest5);
    myFirstPlayer->chooseDraftCard(cardTest6);
    myFirstPlayer->chooseDraftCard(cardTest8);


    //Testing method keepCard :
    myFirstPlayer->keepCard(cardTest1);
    myFirstPlayer->keepCard(cardTest2);
    myFirstPlayer->keepCard(cardTest3);
    myFirstPlayer->keepCard(cardTest4);
    myFirstPlayer->keepCard(cardTest8);


    //Testing method discardCard :
    myFirstPlayer->discardCard(cardTest2);
    myFirstPlayer->discardCard(cardTest6);


    //Testing method addResource :
    myFirstPlayer->addResource(MATERIAL, cardTest1);


    //Testing method construct :
    myFirstPlayer->construct(cardTest1);
    myFirstPlayer->construct(cardTest3);
    myFirstPlayer->construct(cardTest4);
    myFirstPlayer->construct(cardTest8);


    //Testing method receiveResource and receiveResources:
    myFirstPlayer->receiveResources(GOLD,3);
    myFirstPlayer->receiveResource(GOLD);
     


    //Testing method chooseColonelToken :
    (void)myFirstPlayer->chooseColonelToken();


    //Testing method computeVictoryPoint :
    (void)myFirstPlayer->computeVictoryPoint();

    victoryPointsAFRICA  = new CardVictoryPoint{1,state::ResourceType::COLONEL};
		africa = new EmpireCard("AFRICA", productionGainAFRICA, designAFRICA, victoryPointsAFRICA, {/*prob face B*/}, {/*victorypoints face B*/}, AFRICA); 
		myFirstPlayer->setEmpire(africa);
    (void)myFirstPlayer->computeVictoryPoint();

    victoryPointsAFRICA  = new CardVictoryPoint{1,state::ResourceType::FINANCIER};
		africa = new EmpireCard("AFRICA", productionGainAFRICA, designAFRICA, victoryPointsAFRICA, {/*prob face B*/}, {/*victorypoints face B*/}, AFRICA); 
		myFirstPlayer->setEmpire(africa);
    (void)myFirstPlayer->computeVictoryPoint();

    victoryPointsAFRICA  = new CardVictoryPoint{1,state::CardType::NONETYPE};
		africa = new EmpireCard("AFRICA", productionGainAFRICA, designAFRICA, victoryPointsAFRICA, {/*prob face B*/}, {/*victorypoints face B*/}, AFRICA); 
		myFirstPlayer->setEmpire(africa);
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

    //Testing method getProductionGain :
    (void)myFirstPlayer->getProductionGain(MATERIAL);

    // Delete pointers that won't be used anymore.
    delete africa;
    delete victoryPointsAFRICA;
    delete firstResourceToProduceAFRICA;
    delete secondResourceToProduceAFRICA;
    for(ResourceToProduce* resource : productionGainAFRICA)
    {
      delete resource;
    }

    delete cardTest6;
    delete cardTest5;
    delete cardTest4;
    delete cardTest3;
    delete victoryPoints3;
    delete paiement3;
    delete production3;

    delete cardTest2;
    delete victoryPoints2;
    delete paiement2;
    delete production2;

    delete cardTest1;
    delete victoryPoints1;
    delete paiement1;
    delete production1;
  }
}

/* vim: set sw=2 sts=2 et : */