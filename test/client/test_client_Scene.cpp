#include <boost/test/unit_test.hpp>

#include "../../src/client/render/Scene.h"

using namespace ::render;

BOOST_AUTO_TEST_CASE(SceneTest)
{
  {
	// Creation of the instance of Game
    Scene* myScene = new Scene();

	// Test getBackground()
	(void)myScene->getBackground();

	// Test getPlayerRenderer
	(void)myScene->getPlayerRenderer(0);

	// Test setWindow
	Window w = PLAYER_INFO;
	myScene->changeWindow(w);

	// Test getWindow
	Window w2 = myScene->getWindow();
	BOOST_CHECK_EQUAL(w, w2);

	// Delete pointers
	delete myScene;
  }
}

/* vim: set sw=2 sts=2 et : */

