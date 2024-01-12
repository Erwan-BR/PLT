#include <boost/test/unit_test.hpp>

#include "../../src/client/render/Scene.h"

#include "../../src/shared/state/CreateAllCards.h"
#include "../../src/constants/constants/CustomTypes.h"


using namespace ::render;
using namespace std;

BOOST_AUTO_TEST_CASE(SceneTest){	//First Test : Test Game & Scene methods
  {				
	//Creation of testing instances of Player class
	std::shared_ptr<state::Player> player1 = std::make_shared<state::Player>("MOI",1);
	std::shared_ptr<state::Player> player2 = std::make_shared<state::Player>("TOI",2);

	//Creation of the vector players
	constants::playersList players;
	players.push_back(player1);
	players.push_back(player2);

	//Creation of the instance of the Game class
	std::shared_ptr<state::Game> game = std::make_shared<state::Game>(players,true);
	game->initGame();

	std::mutex locker;

	//Creation of the instance of the Scene class
	Scene* myscene = new Scene(game, locker, nullptr);

	// Test setWindow
	Window w = PLAYER_INFO;
	myscene->changeWindow(w);

	// Test getWindow
	Window w2 = myscene->getWindow();
	BOOST_CHECK_EQUAL(w, w2);

	//Test setupObserver
	myscene->setupObserver(game);

	//Test changePlayerInfoPlayer
	myscene->changePlayerInfoPlayer(1,MAIN_WINDOW);
	myscene->changePlayerInfoPlayer(1,PLAYER_INFO);
	myscene->changePlayerInfoPlayer(1,DRAFTING_WINDOW);

	//Test update
	myscene->update(0);

	//Test draw & update on all Windows
	sf::RenderWindow window(sf::VideoMode(10,10),"Test",0);
	myscene->changeWindow(MAIN_WINDOW);
	myscene->draw(window);
	myscene->update(0);
	myscene->changeWindow(DRAFTING_WINDOW);
	myscene->draw(window);
	myscene->update(0);
	myscene->changeWindow(PLANIFICATION_WINDOW);
	myscene->draw(window);
	myscene->update(0);
	myscene->changeWindow(PLAYER_INFO);
	myscene->draw(window);
	myscene->update(0);
	myscene->changeWindow(NONE);
	myscene->draw(window);
	myscene->update(0);

	//Test Cards in all Player's vector
	//Player took 3 Zeppelin from draft hand to drafted
	player1->chooseDraftCard(0);
	player1->chooseDraftCard(0);
	player1->chooseDraftCard(0);
	//Player took 2 Zeppelin from drafted to toBuild
	player1->keepCard(0);
	player1->keepCard(0);
	//Player Built
	for(state::ResourceToPay* r : player1->getToBuildCards()[0]->getCostToBuild()){
		state::ResourceType res = r->type;
		player1->receiveResources(res,1);
		player1->addResource(res,0);
	}
	
	//Update
	myscene->update(0);
	myscene->changeWindow(MAIN_WINDOW);
	myscene->draw(window);

	//Pass through all Phase 
	game->nextPhase();
	myscene->update(0);
	game->nextPhase();
	myscene->update(0);
	game->nextProduction();
	myscene->update(0);
	game->nextProduction();
	myscene->update(0);
	game->nextProduction();
	myscene->update(0);
	game->nextProduction();
	myscene->update(0);
	game->nextProduction();
	myscene->update(0);
	game->endGame();
	myscene->update(0);

	// Delete pointers
	delete myscene;
  }
}

BOOST_AUTO_TEST_CASE(DestructorTest){	//Second Test Destruction of Renderer
  {
	//PlayerRenderer
	std::shared_ptr<state::Player> player = std::make_shared<state::Player>("TestPlayer",1);
	
	PlayerRenderer* pR = new PlayerRenderer(player,{0.f,0.f},MAIN_WINDOW);
	
	delete pR;
	
	//PlayerRenderer with invalid Window
	std::shared_ptr<state::Player> player2 = std::make_shared<state::Player>("TestPlayer",1);
	PlayerRenderer* pR2 = new PlayerRenderer(player2,{0.f,0.f},NONE);
	delete pR2;

	//GameRenderer
	constants::playersList players;
	players.push_back(player);
	players.push_back(player2);
	std::shared_ptr<state::Game> game = std::make_shared<state::Game>(players);
	GameRenderer* gR = new GameRenderer(game,{0.f,0.f});
	delete gR;

	//Player Renderer with cards
	game->initGame();
	player->chooseDraftCard(0);
	PlayerRenderer* pR3 = new PlayerRenderer(player,{0.f,0.f},DRAFTING_WINDOW);
	pR3->update(0);
	delete pR3;

	//DevellopementCardRenderer
	std::shared_ptr<state::DevelopmentCard> card(new state::DevelopmentCard("Empty Card",{},{},state::STRUCTURE,0,{new state::ResourceToPay{state::ResourceType::SCIENCE, false}},{},state::FINANCIER));
	
	DevelopmentCardRenderer* cR = new DevelopmentCardRenderer(card,{0.f,0.f},0.f);
	
	delete cR;
  }
}

/* vim: set sw=2 sts=2 et : */

