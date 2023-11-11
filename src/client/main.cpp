#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>


void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>
#include <render.h>
#include "../shared/state.h"

using namespace std;
using namespace state;
using namespace render;

int main(int argc,char* argv[])
{
	/*//Creation of testing instances of Player class
	state::Player* player1 = new state::Player();
	state::Player* player2 = new state::Player();

	//Creation of the vector players
	vector<state::Player*> players;
	players.push_back(player1);
	players.push_back(player2);*/

	//Creation of the instance of the Game class
	//state::Game* game = new state::Game(players);

	//Creation of Cards
	CardRenderer* c1 = new CardRenderer("card1.png");
	CardRenderer* c2 = new CardRenderer("card2.png");
	CardRenderer* c3 = new CardRenderer("card3.png");
	CardRenderer* c4 = new CardRenderer("card4.png");
	CardRenderer* c5 = new CardRenderer("card5.png");
	CardRenderer* c6 = new CardRenderer("card6.png");

	//Creation of Transform (Card Slots)
	sf::Transform tr_car_1 = sf::Transform().translate(30.f,30.f).scale(0.2f, 0.2f);
	sf::Transform tr_car_2 = sf::Transform().translate(160.f,30.f).scale(0.2f, 0.2f);;
	sf::Transform tr_car_3 = sf::Transform().translate(270.f,30.f).scale(0.2f, 0.2f);;
	sf::Transform tr_car_4 = sf::Transform().translate(30.f,330.f).scale(0.2f, 0.2f);;
	sf::Transform tr_car_5 = sf::Transform().translate(160.f,330.f).scale(0.2f, 0.2f);;
	sf::Transform tr_car_6 = sf::Transform().translate(270.f,330.f).scale(0.2f, 0.2f);;




	//Creation of the instance of the Scene class
	Scene scene = Scene(/*game*/);

	//Creation of the window
	sf::RenderWindow window(sf::VideoMode(1820,980),"It's a Wonderful World!",sf::Style::Titlebar|sf::Style::Close);

	//Creation of the instance of sf::Event class that will received user's inputs.
	sf::Event event;

	//Main Loop active while the window is still open
	while (window.isOpen())
		{
			//Clear the content of the window
			window.clear();

			//Test if an event happens and save it in "event"
			while (window.pollEvent(event))
			{
				//Command to close the window
				if (event.type == sf::Event::Closed){
					window.close();}
				//TODO USER INPUT
				 //if (event.type == sf::Event::KeyPressed) {
					//c = event.text.unicode;
					//if (event.key.code <= 36){
	                //input += KEY_NAMES[event.key.code];}
			}

			//Draw the differents sprite in the window
			window.draw(scene.getBackground());
			window.draw(c1->getSprite(),tr_car_1);
			window.draw(c2->getSprite(),tr_car_2);
			window.draw(c3->getSprite(),tr_car_3);
			window.draw(c4->getSprite(),tr_car_4);
			window.draw(c5->getSprite(),tr_car_5);
			window.draw(c6->getSprite(),tr_car_6);

			//Display the new content of the window
			window.display();
		}
    cout << "It worked !" << endl;

    return 0;
}
