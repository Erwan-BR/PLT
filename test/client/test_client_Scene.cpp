#include <boost/test/unit_test.hpp>

#include "../../src/client/render/Scene.h"

using namespace ::render;
using namespace std;

BOOST_AUTO_TEST_CASE(SceneTest)
{
  {
	sf::Texture* t = new sf::Texture();
	sf::Texture* t2 = new sf::Texture();
	//Creation of testing instances of Player class
	t->loadFromFile("./resources/img/pfp_1.png");
	state::Player* player1 = new state::Player("MOI",0,t);
	t2->loadFromFile("./resources/img/pfp_2.png");
	state::Player* player2 = new state::Player("TOI",1,t2);

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

	//Test changePlayerInfoPlayer
	myscene->changePlayerInfoPlayer(1);

	//Test update
	myscene->update();

	//Test draw
	sf::RenderWindow window(sf::VideoMode(10,10),"Test",0);
	myscene->draw(window);

	// Delete pointers
	delete myscene;
  }
}

/* vim: set sw=2 sts=2 et : */

