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
	/* TODO Solve problem of compatibility between state and render to use this
	//Creation of testing instances of Player class
	state::Player* player1 = new state::Player();
	state::Player* player2 = new state::Player();

	//Creation of the vector players
	vector<state::Player*> players;
	players.push_back(player1);
	players.push_back(player2);

	//Creation of the instance of the Game class
	state::Game* game = new state::Game(players);*/

	//Creation of the instance of the Scene class
	Scene scene = Scene(/*game*/);

	//Creation of the window
	int win_length = 1820;
	int win_heigth = 800;
	sf::RenderWindow window(sf::VideoMode(win_length,win_heigth),"It's a Wonderful World!",sf::Style::Titlebar|sf::Style::Close);

	//Creation of Transform (Scale adjusting to the window size)
	float win_length_scale = (win_length*1.0f)/(1920.0f);
	float win_heigth_scale = (win_heigth*1.0f)/(1080.0f);
	sf::Transform tr_scale = sf::Transform().scale(win_length_scale, win_heigth_scale);

	//Creation of PlayerRenderer for the user
	PlayerRenderer* own_renderer = new PlayerRenderer();

	//Creation of Transform (Own PlayerRenderer Position)
	sf::Transform tr_own_renderer = sf::Transform(tr_scale).translate(525.0f,780.0f);

	//Creation of Cards
	CardRenderer* c1 = new CardRenderer("card1.png");
	CardRenderer* c2 = new CardRenderer("card2.png");
	CardRenderer* c3 = new CardRenderer("card3.png");
	CardRenderer* c4 = new CardRenderer("card4.png");
	CardRenderer* c5 = new CardRenderer("card5.png");
	CardRenderer* c6 = new CardRenderer("card6.png");

	//Creation of Transform (Card Slots)
	sf::Transform tr_car_1 = sf::Transform(tr_own_renderer).translate(350.f,48.f).scale(0.2f, 0.2f);
	sf::Transform tr_car_2 = sf::Transform(tr_own_renderer).translate(420.f,48.f).scale(0.2f, 0.2f);;
	sf::Transform tr_car_3 = sf::Transform(tr_own_renderer).translate(490.f,48.f).scale(0.2f, 0.2f);;
	sf::Transform tr_car_4 = sf::Transform(tr_own_renderer).translate(560.f,48.f).scale(0.2f, 0.2f);;
	sf::Transform tr_car_5 = sf::Transform(tr_own_renderer).translate(630.f,48.f).scale(0.2f, 0.2f);;
	sf::Transform tr_car_6 = sf::Transform(tr_own_renderer).translate(700.f,48.f).scale(0.2f, 0.2f);;

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
			window.draw(scene.getBackground(),tr_scale);		//Background
			window.draw(own_renderer->getSprite(),tr_own_renderer); //own renderer
			window.draw(c1->getSprite(),tr_car_1);			//Card 1
			window.draw(c2->getSprite(),tr_car_2);			//Card 2
			window.draw(c3->getSprite(),tr_car_3);			//Card 3
			window.draw(c4->getSprite(),tr_car_4);			//Card 4
			window.draw(c5->getSprite(),tr_car_5);			//Card 5
			window.draw(c6->getSprite(),tr_car_6);			//Card 6

			//Display the new content of the window
			window.display();
		}
    cout << "It worked !" << endl;

    return 0;
}
