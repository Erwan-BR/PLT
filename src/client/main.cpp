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
	/* TODO Solve problem of compatibility between state and render to use this --Observer???
	//Creation of testing instances of Player class
	state::Player* player1 = new state::Player();
	state::Player* player2 = new state::Player();

	//Creation of the vector players
	vector<state::Player*> players;
	players.push_back(player1);
	players.push_back(player2);

	//Creation of the instance of the Game class
	state::Game* game = new state::Game(players);*/

	int i;

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

	//Creation of the Font for the Texts
	sf::Font font;
	font.loadFromFile("../resources/font/arial.ttf");

	//Creation of token indicating the resource production (with its Transform)
	sf::CircleShape token = sf::CircleShape(25.0f,100);
	token.setFillColor(sf::Color::White);
	token.setPosition(685.0f,585.0f);
	int token_offset = 0;
	sf::Transform tr_token = sf::Transform(tr_scale);

	//Creation of the Text indicating the turn (with its Transform)
	sf::Text turn_indicator = sf::Text();
	int turn = 1;
	turn_indicator.setFont(font);
	turn_indicator.setString("TURN "+to_string(turn)+" \nDraft");
	turn_indicator.setCharacterSize(30);
	turn_indicator.setFillColor(sf::Color::White);
	sf::Transform tr_turn_indicator = sf::Transform(tr_scale).translate(810.f,430.0f);

	//Creation of symbol of turn (with its Transform)
	sf::Texture texture_turn_even;texture_turn_even.loadFromFile("../resources/img/evenarrow.png");
	sf::Texture texture_turn_odd;texture_turn_odd.loadFromFile("../resources/img/oddarrow.png");
	sf::Sprite turn_symbol;turn_symbol.setTexture(texture_turn_odd);
	sf::Transform tr_turn_symbol = sf::Transform(tr_scale).translate(1030.f,420.0f).scale(0.8f,0.8f);

	//Creation of Transform (Own PlayerRenderer Position)
	sf::Transform tr_renderer_p1 = sf::Transform(tr_scale).translate(525.0f,780.0f);

	//Creation of PlayerRenderer for the user
	PlayerRenderer* renderer_p1 = new PlayerRenderer(tr_renderer_p1);

	//Creation of Transform (Own PlayerRenderer Position)
	sf::Transform tr_renderer_p2 = sf::Transform(tr_scale).translate(525.0f,0.0f);

	//Creation of PlayerRenderer for the user
	PlayerRenderer* renderer_p2 = new PlayerRenderer(tr_renderer_p2);

	//Change the default values of Renderers
	renderer_p1->changeName("Joueur 1");
	renderer_p1->changeProfilePicture("pfp_1");
	renderer_p2->changeName("Joueur 2");
	renderer_p2->changeProfilePicture("pfp_2");
	for(i=0;i<13;i++){
		renderer_p1->changeNumbers(i,i);
		renderer_p2->changeNumbers(i,(7*i)%3);
	}


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
					window.close();
				}
				if (event.type == sf::Event::KeyPressed) {
					//cout<<to_string(event.key.code)<<endl; //Debug Print the code of pressed key
					if (event.key.code == 10){		//Key K
						if (token_offset != 0){token_offset--;}		//Decrease toke_offset if not minimal
						tr_token = sf::Transform(tr_scale).translate(125.0f*token_offset,0.0f);		//Update Transform
					}
					if (event.key.code == 12){		//Key M
						if (token_offset != 4){token_offset++;}		//Increase token_offset if not maximal
						tr_token = sf::Transform(tr_scale).translate(125.0f*token_offset,0.0f);		//Update Transform
					}
					if (event.key.code == 11){		//Key L
						if (turn != 1){turn--;}		//Decrease turn if not minimal
						turn_indicator.setString("TURN "+to_string(turn)+" \nDraft");		//Update Text
						if (turn%2){turn_symbol.setTexture(texture_turn_odd);}				//Update Symbol
						else {turn_symbol.setTexture(texture_turn_even);}
					}
					if (event.key.code == 14){		//Key O
						if (turn != 4){turn++;}		//Increase turn if not maximal
						turn_indicator.setString("TURN "+to_string(turn)+" \nDraft");		//Update Text
						if (turn%2){turn_symbol.setTexture(texture_turn_odd);}			//Update Symbol
						else {turn_symbol.setTexture(texture_turn_even);}
					}
				}
			}

			//Draw the differents sprite in the window
			window.draw(scene.getBackground(),tr_scale);		//Background
			window.draw(token,tr_token);						//Token
			window.draw(turn_indicator,tr_turn_indicator);		//Turn Text
			window.draw(turn_symbol,tr_turn_symbol);			//Turn Symbol

			for (i = 0; i < renderer_p1->getNumberSprite();i++){
				window.draw(*(renderer_p1->getSprite(i)),renderer_p1->getSpriteTransform(i));
			}
			for (i = 0; i < renderer_p2->getNumberSprite();i++){
				window.draw(*(renderer_p2->getSprite(i)),renderer_p2->getSpriteTransform(i));
			}
			for (i = 0; i < renderer_p1->getNumberText();i++){
				window.draw(*(renderer_p1->getText(i)),renderer_p1->getTextTransform(i));
			}
			for (i = 0; i < renderer_p2->getNumberText();i++){
				window.draw(*(renderer_p2->getText(i)),renderer_p2->getTextTransform(i));
			}


			//Display the new content of the window
			window.display();
		}
    cout << "It worked !" << endl;

    return 0;
}
