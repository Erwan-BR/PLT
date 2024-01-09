#include <boost/test/unit_test.hpp>

#include "../../src/client/render/Scene.h"

using namespace ::render;
using namespace std;

BOOST_AUTO_TEST_CASE(SceneTest){	//First Test : Test Game & Scene methods
  {				
	//Creation of testing instances of Player class
	state::Player* player1 = new state::Player("MOI",1);
	state::Player* player2 = new state::Player("TOI",2);

	//Creation of the vector players
	std::vector<state::Player*> players;
	players.push_back(player1);
	players.push_back(player2);

	//Creation of the instance of the Game class
	state::Game game = state::Game(players,true);
	game.initGame();

	//Creation of the instance of the Scene class
	Scene* myscene = new Scene(&game,sf::Transform());

	// Test setWindow
	Window w = PLAYER_INFO;
	myscene->changeWindow(w);

	// Test getWindow
	Window w2 = myscene->getWindow();
	BOOST_CHECK_EQUAL(w, w2);

	//Test setupObserver
	myscene->setupObserver(&game);

	//Test changePlayerInfoPlayer
	myscene->changePlayerInfoPlayer(1);

	//Test update
	myscene->update();

	//Test draw & update on all Windows
	sf::RenderWindow window(sf::VideoMode(10,10),"Test",0);
	myscene->changeWindow(MAIN_WINDOW);
	myscene->draw(window);
	myscene->update();
	myscene->changeWindow(DRAFTING_WINDOW);
	myscene->draw(window);
	myscene->update();
	myscene->changeWindow(PLANIFICATION_WINDOW);
	myscene->draw(window);
	myscene->update();
	myscene->changeWindow(PLAYER_INFO);
	myscene->draw(window);
	myscene->update();
	myscene->changeWindow(NONE);
	myscene->draw(window);
	myscene->update();

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
	myscene->update();
	myscene->changeWindow(MAIN_WINDOW);
	myscene->draw(window);

	//Pass through all Phase 
	game.nextPhase();
	myscene->update();
	game.nextPhase();
	myscene->update();
	game.nextProduction();
	myscene->update();
	game.nextProduction();
	myscene->update();
	game.nextProduction();
	myscene->update();
	game.nextProduction();
	myscene->update();
	game.nextProduction();
	myscene->update();
	game.endGame();
	myscene->update();

	// Delete pointers
	delete myscene;
  }
}

BOOST_AUTO_TEST_CASE(DestructorTest){	//Second Test Destruction of Renderer
  {
	//PlayerRenderer
	state::Player* player = new state::Player("TestPlayer",1);
	PlayerRenderer* pR = new PlayerRenderer(player,sf::Transform(),MAIN_WINDOW);
	delete pR;
	//PlayerRenderer with invalid Window
	PlayerRenderer* pR2 = new PlayerRenderer(player,sf::Transform(),NONE);
	delete pR2;

	//GameRenderer
	std::vector<state::Player*> players;
	players.push_back(player);
	players.push_back(player);
	state::Game* game = new state::Game(players);
	GameRenderer* gR = new GameRenderer(game,sf::Transform());
	delete gR;

	//Player Renderer with cards
	game->initGame();
	player->chooseDraftCard(0);
	PlayerRenderer* pR3 = new PlayerRenderer(player,sf::Transform(),DRAFTING_WINDOW);
	pR3->update();
	delete pR3;

	//DevellopementCardRenderer
	state::DevelopmentCard* card = new state::DevelopmentCard("Empty Card",{},{},state::STRUCTURE,0,{new state::ResourceToPay{state::ResourceType::SCIENCE, false}},{},state::FINANCIER);
	DevelopmentCardRenderer* cR = new DevelopmentCardRenderer(card,sf::Transform(),0.f);
	delete cR;

	//Delete others pointer
	delete player;
	delete game;
	delete card;
  }
}

/* vim: set sw=2 sts=2 et : */

