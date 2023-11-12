#include <boost/test/unit_test.hpp>

#include "../../src/client/render/Scene.h"

using namespace ::render;

BOOST_AUTO_TEST_CASE(SceneTest)
{
  {
	// Creation of the instance of Game
    Scene* myScene = new Scene();

	// Test getBackground()
	sf::Sprite* sprite = myScene->getBackground();
	BOOST_CHECK_EQUAL(1, 1);

	// Test getPlayerRenderer
	PlayerRenderer* renderer = myScene->getPlayerRenderer(1);
	BOOST_CHECK_EQUAL(1, 1);

	// Test setWindow
	Window w = PLAYER_INFO;
	myScene->setWindow(w);

	// Test getWindow
	Window w2 = myScene->getWindow();
	BOOST_CHECK_EQUAL(w, w2);

	// Delete pointers
	delete myScene;
	delete sprite;
	delete renderer;
  }
}

/* vim: set sw=2 sts=2 et : */

