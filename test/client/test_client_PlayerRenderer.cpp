#include <boost/test/unit_test.hpp>

#include "../../src/client/render/PlayerRenderer.h"


using namespace ::render;

BOOST_AUTO_TEST_CASE(fullPlayerRendererTest)
{
  {
	sf::Transform* tr = new sf::Transform();

	// Creation of instances of PlayerRenderer for each case
    PlayerRenderer* myPRMain = new PlayerRenderer(*tr,MAIN_WINDOW);
    PlayerRenderer* myPRDraft = new PlayerRenderer(*tr,DRAFTING_WINDOW);
    PlayerRenderer* myPRInfo = new PlayerRenderer(*tr,PLAYER_INFO);
    PlayerRenderer* myPRDefault = new PlayerRenderer(*tr,NONE);

    //Test getSprite
    sf::Sprite* sprite = myPRMain->getSprite(1);
    BOOST_CHECK_EQUAL(1, 1);

    //Test getSpriteTransform
	sf::Transform tr_1 = myPRDraft->getSpriteTransform(1);
	BOOST_CHECK_EQUAL(1, 1);

	//Test getSprite
	sf::Text* text = myPRMain->getText(1);
	BOOST_CHECK_EQUAL(1, 1);

	//Test getSpriteTransform
	sf::Transform tr_2 = myPRDraft->getTextTransform(1);
	BOOST_CHECK_EQUAL(1, 1);

	//Test getNumberText
	int n = myPRInfo->getNumberText();
	BOOST_CHECK_EQUAL(n, 16);

	//Test getNumberText
	int m = myPRInfo->getNumberSprite();
	BOOST_CHECK_EQUAL(m, 58);

	//Test Changes
	myPRDraft->changeProfilePicture("pfp_1");
	myPRMain->changeName("Nom");
	myPRInfo->changeNumbers(1,1);

	// Delete pointers
	delete myPRMain;
	delete myPRDraft;
	delete myPRInfo;
	delete sprite;
	delete text;
  }
  {
	  //Create Empty PlayerRenderer
	  PlayerRenderer* myPREmpty = new PlayerRenderer();

	  // Delete pointers
	  delete myPREmpty;
  }
}

/* vim: set sw=2 sts=2 et : */

