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

	//Creation of token indicating the resource production
	sf::CircleShape token = sf::CircleShape(25.0f,100);
	token.setFillColor(sf::Color::White);
	token.setPosition(685.0f,585.0f);

	//Creation of token's Transform
	sf::Transform tr_token = sf::Transform(tr_scale);

	//Creation of Transform (Own PlayerRenderer Position)
	sf::Transform tr_renderer_p1 = sf::Transform(tr_scale).translate(525.0f,780.0f);

	//Creation of PlayerRenderer for the user
	PlayerRenderer* renderer_p1 = new PlayerRenderer(tr_renderer_p1);

	//Creation of Transform (Own PlayerRenderer Position)
	sf::Transform tr_renderer_p2 = sf::Transform(tr_scale).translate(525.0f,0.0f);

	//Creation of PlayerRenderer for the user
	PlayerRenderer* renderer_p2 = new PlayerRenderer(tr_renderer_p2);

	//Creation of the instance of sf::Event class that will received user's inputs.
	sf::Event event;

	int i;

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
			window.draw(token,tr_token);						//Token

			for (i = 0; i < renderer_p1->getNumberDrawable();i++){
				window.draw(*(renderer_p1->getSprite(i)),renderer_p1->getTransform(i));
			}
			for (i = 0; i < renderer_p2->getNumberDrawable();i++){
				window.draw(*(renderer_p2->getSprite(i)),renderer_p2->getTransform(i));
			}


			//Display the new content of the window
			window.display();
		}
    cout << "It worked !" << endl;

    return 0;
}
