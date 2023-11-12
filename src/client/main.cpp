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

	//For MAIN_WINDOW
	//Creation of Transform (Own PlayerRenderer Position)
	sf::Transform tr_renderer_p1 = sf::Transform(tr_scale).translate(525.0f,780.0f);

	//Creation of PlayerRenderer for the user
	PlayerRenderer* renderer_p1 = new PlayerRenderer(tr_renderer_p1,MAIN_WINDOW);

	//Creation of Transform (oposent PlayerRenderer Position)
	sf::Transform tr_renderer_p2 = sf::Transform(tr_scale).translate(525.0f,0.0f);

	//Creation of PlayerRenderer for the oposent
	PlayerRenderer* renderer_p2 = new PlayerRenderer(tr_renderer_p2,MAIN_WINDOW);

	//For DRAFTING_WINDOW
	//Creation of Transform (Own PlayerRenderer Position)
	sf::Transform tr_renderer_p1_d = sf::Transform(tr_scale).translate(0.0f,720.0f);

	//Creation of PlayerRenderer for the user
	PlayerRenderer* renderer_p1_d = new PlayerRenderer(tr_renderer_p1_d,DRAFTING_WINDOW);

	//Creation of Transform (Draft Hand Position)
	sf::Transform tr_renderer_d = sf::Transform(tr_scale).translate(0.0f,900.0f);

	//Creation of PlayerRenderer for the Draft Hand
	PlayerRenderer* renderer_d = new PlayerRenderer(tr_renderer_d,DRAFTING_WINDOW);

	//Creation of Transform (Oposent PlayerRenderer Position)
	sf::Transform tr_renderer_p2_d = sf::Transform(tr_scale).translate(0.0f,0.0f);

	//Creation of PlayerRenderer for the oposent
	PlayerRenderer* renderer_p2_d = new PlayerRenderer(tr_renderer_p2_d,DRAFTING_WINDOW);

	//For PLAYER_INFO
	//Creation of Transform (Own PlayerRenderer Position)
	sf::Transform tr_renderer_f = sf::Transform(tr_scale).translate(0.0f,0.0f);

	//Creation of PlayerRenderer for the user
	PlayerRenderer* renderer_f = new PlayerRenderer(tr_renderer_f,PLAYER_INFO);

	//Change the default values of Renderers
	renderer_p1->changeName("Joueur 1");		renderer_p1_d->changeName("Joueur 1");
	renderer_p1->changeProfilePicture("pfp_1");	renderer_p1_d->changeProfilePicture("pfp_1");
	renderer_p2->changeName("Joueur 2");		renderer_p2_d->changeName("Joueur 2");
	renderer_p2->changeProfilePicture("pfp_2");	renderer_p2_d->changeProfilePicture("pfp_2");
	renderer_d->changeName("Drafting Hand");
	renderer_d->changeProfilePicture("pfp_draft");
	renderer_f->changeName("Joueur 1");
	renderer_f->changeProfilePicture("pfp_1");
	for(i=0;i<13;i++){
		renderer_p1->changeNumbers(i,i);
		renderer_p2->changeNumbers(i,(3*i)%7);
		renderer_f->changeNumbers(i,i);
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
					if (event.key.code == 0){		//Key A
						scene.changeWindow(MAIN_WINDOW); //Change the window to MAIN_WINDOW
					}
					if (event.key.code == 25){		//Key Z
						scene.changeWindow(DRAFTING_WINDOW); //Change the window to DRAFTING_WINDOW
					}
					if (event.key.code == 4){		//Key E
						scene.changeWindow(PLAYER_INFO); //Change the window to PLAYER_INFO
					}

					if (event.key.code == 10 and (scene.getWindow()==MAIN_WINDOW)){		//Key K in MAIN_WINDOW
						if (token_offset != 0){token_offset--;}		//Decrease toke_offset if not minimal
						tr_token = sf::Transform(tr_scale).translate(125.0f*token_offset,0.0f);		//Update Transform
					}
					if (event.key.code == 12 and (scene.getWindow()==MAIN_WINDOW)){		//Key M in MAIN_WINDOW
						if (token_offset != 4){token_offset++;}		//Increase token_offset if not maximal
						tr_token = sf::Transform(tr_scale).translate(125.0f*token_offset,0.0f);		//Update Transform
					}
					if (event.key.code == 11 and (scene.getWindow()==MAIN_WINDOW)){		//Key L in MAIN_WINDOW
						if (turn != 1){turn--;}		//Decrease turn if not minimal
						turn_indicator.setString("TURN "+to_string(turn)+" \nDraft");		//Update Text
						if (turn%2){turn_symbol.setTexture(texture_turn_odd);}				//Update Symbol
						else {turn_symbol.setTexture(texture_turn_even);}
					}
					if (event.key.code == 14 and (scene.getWindow()==MAIN_WINDOW)){		//Key O in MAIN_WINDOW
						if (turn != 4){turn++;}		//Increase turn if not maximal
						turn_indicator.setString("TURN "+to_string(turn)+" \nDraft");		//Update Text
						if (turn%2){turn_symbol.setTexture(texture_turn_odd);}			//Update Symbol
						else {turn_symbol.setTexture(texture_turn_even);}
					}

					if (event.key.code == 16 and (scene.getWindow()==PLAYER_INFO)){		//Key Q in PLAYER_INFO
						renderer_f->changeName("Joueur 1");						//Update Name
						renderer_f->changeProfilePicture("pfp_1");				//Update Pfp
						for(i=0;i<13;i++){renderer_f->changeNumbers(i,i);}		//Update Values
					}
					if (event.key.code == 18 and (scene.getWindow()==PLAYER_INFO)){		//Key S in PLAYER_INFO
						renderer_f->changeName("Joueur 2");						//Update Name
						renderer_f->changeProfilePicture("pfp_2");				//Update Pfp
						for(i=0;i<13;i++){renderer_f->changeNumbers(i,(3*i)%7);}		//Update Values
					}
				}
			}

			//Draw the differents sprite in the window
			switch (scene.getWindow()){
			case MAIN_WINDOW:
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
