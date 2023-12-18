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
#include "render.h"

using namespace std;
using namespace state;
using namespace render;

void next_step(int etape,Game* game,Player* p1,Player* p2,Scene* scene);

int main(int argc,char* argv[])
{
	//Print Temporary Manual Commands
	cout<<"**Temporary Manual Commands**"<<endl;
	cout<<"*Change Window Commands*"<<endl;
	cout<<"A - Main Window"<<endl;
	cout<<"Z - Drafting Window"<<endl;
	cout<<"E - Player Full Window"<<endl;


	//Creation of the window
	int win_length = 1820;
	int win_heigth = 800;
	sf::RenderWindow window(sf::VideoMode(win_length,win_heigth),"It's a Wonderful World!",sf::Style::Titlebar|sf::Style::Close);

	//Creation of Transform (Scale adjusting to the window size)
	float win_length_scale = (win_length*1.0f)/(1920.0f);
	float win_heigth_scale = (win_heigth*1.0f)/(1080.0f);
	sf::Transform tr_scale = sf::Transform().scale(win_length_scale, win_heigth_scale);


	sf::Texture* t = new sf::Texture();
	sf::Texture* t2 = new sf::Texture();
	//Creation of testing instances of Player class
	t->loadFromFile("./resources/img/pfp_1.png");
	state::Player* player1 = new state::Player("MOI",0,t);
	t2->loadFromFile("./resources/img/pfp_2.png");
	state::Player* player2 = new state::Player("TOI",1,t2);

	//Creation of the vector players
	vector<state::Player*> players;
	players.push_back(player1);
	players.push_back(player2);

	//Creation of the instance of the Game class
	state::Game game = state::Game(players,true);

	game.initGame();
	//endDraft - endPlanification - 
	int i,j,k;

	//Creation of the instance of the Scene class
	Scene scene = Scene(&game,tr_scale);

	//Observable
	game.addObserver(scene.getGameRenderer());
	for(i=0;i<(int) game.getPlayers().size();i++){
		game.addObserver(scene.getPlayerRenderer(i));
	}
	game.addObserver(scene.getHandRenderer());


	//Creation of the Font for the Texts
	sf::Font font;
	font.loadFromFile("./resources/font/arial.ttf");

	//Creation of the instance of sf::Event class that will received user's inputs.
	sf::Event event;

	//scene.changeWindow(DRAFTING_WINDOW);
	PlayerRenderer* pRenderer;
	DevelopmentCardRenderer* cRenderer;
	GameRenderer* gRenderer;
	DraftingHandRenderer* hRenderer;

    int etape = 0;

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
					if (event.key.code == sf::Keyboard::A){
						scene.changeWindow(MAIN_WINDOW); //Change the window to MAIN_WINDOW
					}
					if (event.key.code == sf::Keyboard::Z){
						scene.changeWindow(DRAFTING_WINDOW); //Change the window to DRAFTING_WINDOW
					}
					if (event.key.code == sf::Keyboard::E){
						scene.changeWindow(PLANIFICATION_WINDOW); //Change the window to PLAYER_INFO
					}
					if (event.key.code == sf::Keyboard::R){
						scene.changeWindow(PLAYER_INFO); //Change the window to PLAYER_INFO
					}
                    if (event.key.code == sf::Keyboard::Space){
						next_step(etape,&game,player1,player2,&scene);
                        etape++;
					}
						
				}
			}

			//Draw the differents sprite in the window
			switch (scene.getWindow()){
			case MAIN_WINDOW:
				window.draw(scene.getBackground(),tr_scale);		//Background
				//Display GameRenderer
				gRenderer = scene.getGameRenderer();
				window.draw(*(gRenderer->getBoardMaterialSprite()),gRenderer->getBoardMaterialTransform());
				window.draw(*(gRenderer->getBoardEnergySprite()),gRenderer->getBoardEnergyTransform());
				window.draw(*(gRenderer->getBoardScienceSprite()),gRenderer->getBoardScienceTransform());
				window.draw(*(gRenderer->getBoardGoldSprite()),gRenderer->getBoardGoldTransform());
				window.draw(*(gRenderer->getBoardExplorationSprite()),gRenderer->getBoardExplorationTransform());
				window.draw(*(gRenderer->getBoardTurnSprite()),gRenderer->getBoardTurnTransform());
				window.draw(*(gRenderer->getPhaseIndicator()),gRenderer->getPhaseIndicatorTransform());
				
				for (i=0; i < 2; i++){
					pRenderer =	scene.getPlayerRenderer(i);
					for (j = 0; j < pRenderer->getNumberSprite() ;j++){
						window.draw(*(pRenderer->getSprite(j)),pRenderer->getSpriteTransform(j));
					}
					for (j = 0; j < pRenderer->getNumberText() ;j++){
						window.draw(*(pRenderer->getText(j)),pRenderer->getTextTransform(j));
					}
					for (j = 0; j < pRenderer->getNumberCardRenderer() ;j++){
						cRenderer = pRenderer->getCardRenderer(j);
						window.draw(*(cRenderer->getSprite()),cRenderer->getTransform());
						for(k = 0; k<(int) cRenderer->getVectorOfCrossesSprite().size();k++){
							window.draw(*(cRenderer->getVectorOfCrossesSprite()[k]),cRenderer->getVectorOfCrossesTransform()[k]);
						}
					}
				}
				break;
			case DRAFTING_WINDOW:
				for (i=2; i < 4; i++){
					pRenderer =	scene.getPlayerRenderer(i);
					for (j = 0; j < pRenderer->getNumberSprite() ;j++){
						window.draw(*(pRenderer->getSprite(j)),pRenderer->getSpriteTransform(j));
					}
					for (j = 0; j < pRenderer->getNumberText() ;j++){
						window.draw(*(pRenderer->getText(j)),pRenderer->getTextTransform(j));
					}
					for (j = 0; j < pRenderer->getNumberCardRenderer() ;j++){
						cRenderer = pRenderer->getCardRenderer(j);
						window.draw(*(cRenderer->getSprite()),cRenderer->getTransform());
						for(k = 0; k<(int) cRenderer->getVectorOfCrossesSprite().size();k++){
							window.draw(*(cRenderer->getVectorOfCrossesSprite()[k]),cRenderer->getVectorOfCrossesTransform()[k]);
						}
					}
				}
				hRenderer = scene.getHandRenderer();
				for (j = 0; j < hRenderer->getNumberSprite() ;j++){
					window.draw(*(hRenderer->getSprite(j)),hRenderer->getSpriteTransform(j));
				}
				for (j = 0; j < hRenderer->getNumberText() ;j++){
					window.draw(*(hRenderer->getText(j)),hRenderer->getTextTransform(j));
				}
				for (j = 0; j < hRenderer->getNumberCardRenderer() ;j++){
					cRenderer = hRenderer->getCardRenderer(j);
					window.draw(*(cRenderer->getSprite()),cRenderer->getTransform());
					for(k = 0; k<(int) cRenderer->getVectorOfCrossesSprite().size();k++){
						window.draw(*(cRenderer->getVectorOfCrossesSprite()[k]),cRenderer->getVectorOfCrossesTransform()[k]);
					}
				}
				break;
			case PLAYER_INFO:
				pRenderer =	scene.getPlayerRenderer(4);
				for (j = 0; j < pRenderer->getNumberSprite() ;j++){
					window.draw(*(pRenderer->getSprite(j)),(pRenderer->getSpriteTransform(j)));
				}
				for (j = 0; j < pRenderer->getNumberText() ;j++){
					window.draw(*(pRenderer->getText(j)),pRenderer->getTextTransform(j));
				}
				for (j = 0; j < pRenderer->getNumberCardRenderer() ;j++){
					cRenderer = pRenderer->getCardRenderer(j);
					window.draw(*(cRenderer->getSprite()),cRenderer->getTransform().translate(0.f,-780.f));
					for(k = 0; k<(int) cRenderer->getVectorOfCrossesSprite().size();k++){
						window.draw(*(cRenderer->getVectorOfCrossesSprite()[k]),cRenderer->getVectorOfCrossesTransform()[k].translate(0.f,-780.f));
					}
				}
				break;
			case PLANIFICATION_WINDOW:
				window.draw(scene.getBackground(),tr_scale);
				pRenderer =	scene.getPlayerRenderer(0);
				for (j = 0; j < pRenderer->getNumberSprite() ;j++){
					window.draw(*(pRenderer->getSprite(j)),pRenderer->getSpriteTransform(j).translate(0.f,-780.f));
				}
				for (j = 0; j < pRenderer->getNumberText() ;j++){
					window.draw(*(pRenderer->getText(j)),pRenderer->getTextTransform(j).translate(0.f,-780.f));
				}
				for (j = 0; j < pRenderer->getNumberCardRenderer() ;j++){
					cRenderer = pRenderer->getCardRenderer(j);
					window.draw(*(cRenderer->getSprite()),cRenderer->getTransform().translate(0.f,-780.f));
					for(k = 0; k<(int) cRenderer->getVectorOfCrossesSprite().size();k++){
						window.draw(*(cRenderer->getVectorOfCrossesSprite()[k]),cRenderer->getVectorOfCrossesTransform()[k].translate(0.f,-780.f));
					}
				}
				pRenderer =	scene.getPlayerRenderer(5);
				for (j = 0; j < pRenderer->getNumberSprite() ;j++){
					window.draw(*(pRenderer->getSprite(j)),pRenderer->getSpriteTransform(j));
				}
				for (j = 0; j < pRenderer->getNumberText() ;j++){
					window.draw(*(pRenderer->getText(j)),pRenderer->getTextTransform(j));
				}
				for (j = 0; j < pRenderer->getNumberCardRenderer() ;j++){
					cRenderer = pRenderer->getCardRenderer(j);
					window.draw(*(cRenderer->getSprite()),cRenderer->getTransform());
					for(k = 0; k<(int) cRenderer->getVectorOfCrossesSprite().size();k++){
						window.draw(*(cRenderer->getVectorOfCrossesSprite()[k]),cRenderer->getVectorOfCrossesTransform()[k]);
					}
				}
				break;
			default:
				break;
			}


			//Display the new content of the window
			window.display();
		}
    cout << "Exit Successfully !" << endl;

    return 0;
}

void next_step(int etape,Game* game,Player* p1,Player* p2,Scene* scene){
    switch(etape){
        case 0:         //DRAFT 1ere carte
			scene->changeWindow(DRAFTING_WINDOW);
            p1->chooseDraftCard(5);		//Tresor
            p2->chooseDraftCard(5);		//Avalon
			game->nextDraft();
			scene->update();
            break;
        case 1:         //DRAFT 2eme carte
			scene->changeWindow(DRAFTING_WINDOW);
            p1->chooseDraftCard(5);		//Zeppelin
            p2->chooseDraftCard(0);		//Zeppelin
			game->nextDraft();
			scene->update();
            break;
        case 2:         //DRAFT 3eme carte
			scene->changeWindow(DRAFTING_WINDOW);
            p1->chooseDraftCard(4);		//Tour géante
            p2->chooseDraftCard(4);		//Centre Terre
			game->nextDraft();
			scene->update();
            break;
        case 3:         //DRAFT 4eme carte
			scene->changeWindow(DRAFTING_WINDOW);
            p1->chooseDraftCard(0);
            p2->chooseDraftCard(0);
			game->nextDraft();
			scene->update();
            break;
        case 4:         //DRAFT 5eme carte
			scene->changeWindow(DRAFTING_WINDOW);
            p1->chooseDraftCard(0);
            p2->chooseDraftCard(0);
			game->nextDraft();
			scene->update();
            break;
        case 5:         //DRAFT 6eme carte
			scene->changeWindow(DRAFTING_WINDOW);
            p1->chooseDraftCard(0);
            p2->chooseDraftCard(0);
			game->nextDraft();
			scene->update();
            break;
        case 6:         //DRAFT 7eme carte
			scene->changeWindow(DRAFTING_WINDOW);
            p1->chooseDraftCard(0);
            p2->chooseDraftCard(0);
			game->nextDraft();
			scene->update();
            break;
        case 7:         //PLANIFICATION p1 1ere carte
			scene->changeWindow(PLANIFICATION_WINDOW);
			p1->keepCard(0);	//Tresor
			scene->update();
			break;
        case 8:         //PLANIFICATION 1-2
			scene->changeWindow(PLANIFICATION_WINDOW);
			p1->keepCard(1);	//Tour
			scene->update();
			break;
        case 9:         //PLANIFICATION 1-3
			scene->changeWindow(PLANIFICATION_WINDOW);
			p1->discardCard(0,true);
			p1->addResource(state::EXPLORATION,0);
			scene->update();
			break;
        case 10:         //PLANIFICATION 1-4
			scene->changeWindow(PLANIFICATION_WINDOW);
			p1->discardCard(0,true);
			p1->addResource(state::EXPLORATION,0);
			scene->update();
			break;
        case 11:         //PLANIFICATION 1-5
			scene->changeWindow(PLANIFICATION_WINDOW);
			p1->discardCard(0,true);
			p1->addResource(state::EXPLORATION,0);
			scene->update();
			break;
        case 12:         //PLANIFICATION 1-6
			scene->changeWindow(PLANIFICATION_WINDOW);
			p1->discardCard(0,true);
			p1->sendResourceToEmpire(state::EXPLORATION);
			scene->update();
			break;
		case 13:
			scene->changeWindow(PLANIFICATION_WINDOW);
			p1->discardCard(0,true);
			p1->sendResourceToEmpire(state::EXPLORATION);
			scene->update();
			break;
        default:
			break;
    }

}