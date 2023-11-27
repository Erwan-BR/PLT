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

	//Print Temporary Manual Commands

	cout<<"**Temporary Manual Commands**"<<endl;
	cout<<"*Change Window Commands*"<<endl;
	cout<<"A - Main Window"<<endl;
	cout<<"Z - Drafting Window"<<endl;
	cout<<"E - Player Full Window"<<endl;
	cout<<"*Main Window Commands*"<<endl;
	cout<<"K/M - Change position of Token"<<endl;
	cout<<"O/L - Change Turn"<<endl;
	cout<<"*Player Info Commands*"<<endl;
	cout<<"Q - Display Player 1"<<endl;
	cout<<"S - Display Player 2"<<endl;

	//Creation of testing instances of Player class
	state::Player* player1 = new state::Player();
	state::Player* player2 = new state::Player();

	//Creation of the vector players
	vector<state::Player*> players;
	players.push_back(player1);
	players.push_back(player2);

	//Creation of the instance of the Game class
	state::Game* game = new state::Game(players);

	int i,j;

	//Creation of the instance of the Scene class
	Scene scene = Scene(game);

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
	font.loadFromFile("./resources/font/arial.ttf");

	//Creation of the instance of sf::Event class that will received user's inputs.
	sf::Event event;

	PlayerRenderer* pRenderer;

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
					if (event.key.code == 0){		//Key A
						scene.changeWindow(MAIN_WINDOW); //Change the window to MAIN_WINDOW
					}
					if (event.key.code == 25){		//Key Z
						scene.changeWindow(DRAFTING_WINDOW); //Change the window to DRAFTING_WINDOW
					}
					if (event.key.code == 4){		//Key E
						scene.changeWindow(PLAYER_INFO); //Change the window to PLAYER_INFO
					}					
				}
			}

			//Draw the differents sprite in the window
			switch (scene.getWindow()){
			case MAIN_WINDOW:
				window.draw(scene.getBackground(),tr_scale);		//Background
				//TODO Display GameRenderer
				
				for (i=0; i < (scene.getPlayerRenderer().size()-1)/2; i++){
					pRenderer =	scene.getPlayerRenderer()[i];
					for (j = 0; j < pRenderer->getNumberSprite() ;j++){
						window.draw(*(pRenderer->getSprite(i)),pRenderer->getSpriteTransform(i));
					}
					for (j = 0; j < pRenderer->getNumberText() ;j++){
						window.draw(*(pRenderer->getText(i)),pRenderer->getTextTransform(i));
					}
					for (j = 0; j < pRenderer->getNumberCardRenderer() ;j++){
						cRenderer = getCardRenderer(i);
						window.draw(*(cRenderer->),pRenderer->getCardRendererTransform(i));
					}
				}
				break;
			case DRAFTING_WINDOW:
				for (i = 0; i < renderer_p1_d->getNumberSprite();i++){
					window.draw(*(renderer_p1_d->getSprite(i)),renderer_p1_d->getSpriteTransform(i));
				}
				for (i = 0; i < renderer_p2_d->getNumberSprite();i++){
					window.draw(*(renderer_p2_d->getSprite(i)),renderer_p2_d->getSpriteTransform(i));
				}
				for (i = 0; i < renderer_p1_d->getNumberText();i++){
					window.draw(*(renderer_p1_d->getText(i)),renderer_p1_d->getTextTransform(i));
				}
				for (i = 0; i < renderer_p2_d->getNumberText();i++){
					window.draw(*(renderer_p2_d->getText(i)),renderer_p2_d->getTextTransform(i));
				}
				for (i = 0; i < renderer_d->getNumberSprite();i++){
					window.draw(*(renderer_d->getSprite(i)),renderer_d->getSpriteTransform(i));
				}
				for (i = 0; i < renderer_d->getNumberText();i++){
					window.draw(*(renderer_d->getText(i)),renderer_d->getTextTransform(i));
				}
				break;
			case PLAYER_INFO:
				for (i = 0; i < renderer_f->getNumberSprite();i++){
					window.draw(*(renderer_f->getSprite(i)),renderer_f->getSpriteTransform(i));
				}
				for (i = 0; i < renderer_f->getNumberText();i++){
					window.draw(*(renderer_f->getText(i)),renderer_f->getTextTransform(i));
				}
			default:
				break;
			}


			//Display the new content of the window
			window.display();
		}
    cout << "Exit Successfully !" << endl;

    return 0;
}
