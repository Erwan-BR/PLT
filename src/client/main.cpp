#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

#define CROSS_SIZE 0.01f

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
	cout<<"E - Planification Window"<<endl;
	cout<<"R - Full Info Player Window"<<endl;
	cout<<"> On This Window:"<<endl;
	cout<<">Q - Display Player 1"<<endl;
	cout<<">S - Display Player 2"<<endl;

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

	int i,j,k;

	//Creation of the instance of the Scene class
	Scene scene = Scene(&game,tr_scale);

	//Observable
	game.addObserver(scene.getGameRenderer());
	for(i=0;i<scene.getNumberPlayerRenderer();i++){
		game.addObserver(scene.getPlayerRenderer(i));
	}
	game.addObserver(scene.getHandRenderer());

	player1->addObserver(scene.getGameRenderer());
	for(i=0;i<scene.getNumberPlayerRenderer();i++){
		player1->addObserver(scene.getPlayerRenderer(i));
	}
	player1->addObserver(scene.getHandRenderer());

	player2->addObserver(scene.getGameRenderer());
	for(i=0;i<scene.getNumberPlayerRenderer();i++){
		player2->addObserver(scene.getPlayerRenderer(i));
	}
	player2->addObserver(scene.getHandRenderer());

	//Creation of the Font for the Texts
	sf::Font font;
	font.loadFromFile("./resources/font/arial.ttf");

	//Creation of the instance of sf::Event class that will received user's inputs.
	sf::Event event;

	//Creation of pointer
	PlayerRenderer* pRenderer;
	DevelopmentCardRenderer* cRenderer;
	GameRenderer* gRenderer;
	DraftingHandRenderer* hRenderer;

	//Creation of an int that indicates the step of the test game
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
					if (event.key.code == sf::Keyboard::Q and scene.getWindow() == PLAYER_INFO){
						scene.changePlayerInfoPlayer(0);
					}
					if (event.key.code == sf::Keyboard::S and scene.getWindow() == PLAYER_INFO){
						scene.changePlayerInfoPlayer(1);
					}
                    if (event.key.code == sf::Keyboard::Space){
						next_step(etape,&game,player1,player2,&scene);	//Go to the next step
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
				
				//Display players
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
						window.draw(*(cRenderer->getSprite()),cRenderer->getTransform().scale(0.2f,0.2f).scale(1.f,(431.f/375.f)));
						for(k = 0; k<(int) cRenderer->getVectorOfCrossesSprite().size();k++){
							window.draw(*(cRenderer->getVectorOfCrossesSprite()[k]),cRenderer->getVectorOfCrossesTransform()[k].scale(CROSS_SIZE,CROSS_SIZE));
						}
					}
				}
				break;
			case DRAFTING_WINDOW:
				//Display players
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
						window.draw(*(cRenderer->getSprite()),cRenderer->getTransform().scale(0.35f,0.35f).scale(1.f,(431.f/375.f)));
						for(k = 0; k<(int) cRenderer->getVectorOfCrossesSprite().size();k++){
							window.draw(*(cRenderer->getVectorOfCrossesSprite()[k]),cRenderer->getVectorOfCrossesTransform()[k].scale(CROSS_SIZE,CROSS_SIZE));
						}
					}
				}
				//Display Drafting Hand
				hRenderer = scene.getHandRenderer();
				for (j = 0; j < hRenderer->getNumberSprite() ;j++){
					window.draw(*(hRenderer->getSprite(j)),hRenderer->getSpriteTransform(j));
				}
				for (j = 0; j < hRenderer->getNumberText() ;j++){
					window.draw(*(hRenderer->getText(j)),hRenderer->getTextTransform(j));
				}
				for (j = 0; j < hRenderer->getNumberCardRenderer() ;j++){
					cRenderer = hRenderer->getCardRenderer(j);
					window.draw(*(cRenderer->getSprite()),cRenderer->getTransform().scale(0.35f,0.35f).scale(1.f,(431.f/375.f)));
					for(k = 0; k<(int) cRenderer->getVectorOfCrossesSprite().size();k++){
						window.draw(*(cRenderer->getVectorOfCrossesSprite()[k]),cRenderer->getVectorOfCrossesTransform()[k].scale(CROSS_SIZE,CROSS_SIZE));
					}
				}
				break;
			case PLAYER_INFO:
				//Display Player
				pRenderer =	scene.getPlayerRenderer(4);
				for (j = 0; j < pRenderer->getNumberSprite() ;j++){
					window.draw(*(pRenderer->getSprite(j)),(pRenderer->getSpriteTransform(j)));
				}
				for (j = 0; j < pRenderer->getNumberText() ;j++){
					window.draw(*(pRenderer->getText(j)),pRenderer->getTextTransform(j));
				}
				for (j = 0; j < pRenderer->getNumberCardRenderer() ;j++){
					cRenderer = pRenderer->getCardRenderer(j);
					window.draw(*(cRenderer->getSprite()),cRenderer->getTransform().scale(0.3f,0.3f));
					for(k = 0; k<(int) cRenderer->getVectorOfCrossesSprite().size();k++){
						window.draw(*(cRenderer->getVectorOfCrossesSprite()[k]),cRenderer->getVectorOfCrossesTransform()[k].scale(0.01f,0.01f));
					}
				}
				break;
			case PLANIFICATION_WINDOW:
				window.draw(scene.getBackground(),tr_scale);

				//Display Player
				pRenderer =	scene.getPlayerRenderer(0);
				for (j = 0; j < pRenderer->getNumberSprite() ;j++){
					window.draw(*(pRenderer->getSprite(j)),pRenderer->getSpriteTransform(j).translate(0.f,-780.f));
				}
				for (j = 0; j < pRenderer->getNumberText() ;j++){
					window.draw(*(pRenderer->getText(j)),pRenderer->getTextTransform(j).translate(0.f,-780.f));
				}
				for (j = 0; j < pRenderer->getNumberCardRenderer() ;j++){
					cRenderer = pRenderer->getCardRenderer(j);
					window.draw(*(cRenderer->getSprite()),cRenderer->getTransform().translate(0.f,-780.f).scale(0.2f,0.2f).scale(1.f,(431.f/375.f)));
					for(k = 0; k<(int) cRenderer->getVectorOfCrossesSprite().size();k++){
						window.draw(*(cRenderer->getVectorOfCrossesSprite()[k]),cRenderer->getVectorOfCrossesTransform()[k].translate(0.f,-780.f).scale(CROSS_SIZE,CROSS_SIZE));
					}
				}
				//Display Drafted Hand
				pRenderer =	scene.getPlayerRenderer(5);
				for (j = 0; j < pRenderer->getNumberSprite() ;j++){
					window.draw(*(pRenderer->getSprite(j)),pRenderer->getSpriteTransform(j));
				}
				for (j = 0; j < pRenderer->getNumberText() ;j++){
					window.draw(*(pRenderer->getText(j)),pRenderer->getTextTransform(j));
				}
				for (j = 0; j < pRenderer->getNumberCardRenderer() ;j++){
					cRenderer = pRenderer->getCardRenderer(j);
					window.draw(*(cRenderer->getSprite()),cRenderer->getTransform().scale(0.35f,0.35f).scale(1.f,(431.f/375.f)));
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
            p1->chooseDraftCard(5);		//P1 Choose Tresor de Barbe Noire
            p2->chooseDraftCard(5);		//P2 Choose Ile d'Avalon
			game->nextDraft();
			
            break;
        case 1:         //DRAFT 2eme carte
			scene->changeWindow(DRAFTING_WINDOW);
            p1->chooseDraftCard(5);		//P1 Choose Zeppelin
            p2->chooseDraftCard(0);		//P2 Choose Zeppelin
			game->nextDraft();
			
            break;
        case 2:         //DRAFT 3eme carte
			scene->changeWindow(DRAFTING_WINDOW);
            p1->chooseDraftCard(4);		//P1 Choose Tour géante
            p2->chooseDraftCard(4);		//P2 Choose Centre de la Terre
			game->nextDraft();
			
            break;
        case 3:         //DRAFT 4eme carte
			scene->changeWindow(DRAFTING_WINDOW);
            p1->chooseDraftCard(0);		//P1 Choose Juggernaut
            p2->chooseDraftCard(0);		//P2 Choose Brise-blaces
			game->nextDraft();
			
            break;
        case 4:         //DRAFT 5eme carte
			scene->changeWindow(DRAFTING_WINDOW);
            p1->chooseDraftCard(0);
            p2->chooseDraftCard(0);
			game->nextDraft();
			
            break;
        case 5:         //DRAFT 6eme carte
			scene->changeWindow(DRAFTING_WINDOW);
            p1->chooseDraftCard(0);
            p2->chooseDraftCard(0);
			game->nextDraft();
			
            break;
        case 6:         //DRAFT 7eme carte
			scene->changeWindow(DRAFTING_WINDOW);
            p1->chooseDraftCard(0);
            p2->chooseDraftCard(0);
			game->nextDraft();
			
            break;
        case 7:         //PLANIFICATION p1 1ere carte
			scene->changeWindow(PLANIFICATION_WINDOW);
			p1->keepCard(0);	//P1 Keep Tresor de Barbe Noire
			
			break;
        case 8:         //PLANIFICATION 1-2
			scene->changeWindow(PLANIFICATION_WINDOW);
			p1->keepCard(1);	//P1 Keep Tour Géante
			
			break;
        case 9:         //PLANIFICATION 1-3
			scene->changeWindow(PLANIFICATION_WINDOW);
			p1->discardCard(0,true);				//Discard Exploration for Tresor
			p1->addResource(state::EXPLORATION,0);
			
			break;
        case 10:         //PLANIFICATION 1-4
			scene->changeWindow(PLANIFICATION_WINDOW);
			p1->discardCard(0,true);				//Discard Material for Tour
			p1->addResource(state::MATERIAL,1);
			
			break;
        case 11:         //PLANIFICATION 1-5
			scene->changeWindow(PLANIFICATION_WINDOW);
			p1->discardCard(0,true);				//Discard Exploration for Tresor
			p1->addResource(state::EXPLORATION,0);
			
			break;
        case 12:         //PLANIFICATION 1-6
			scene->changeWindow(PLANIFICATION_WINDOW);
			p1->discardCard(0,true);				//Discard Exploration for Tresor
			p1->addResource(state::EXPLORATION,0);	//Tresor built
			
			break;
		case 13:		//PLANIFICATION 1-7
			scene->changeWindow(PLANIFICATION_WINDOW);
			p1->discardCard(0,true);				//Discard Exploration in Empire
			p1->sendResourceToEmpire(state::EXPLORATION);
			
			break;
		case 14:         //PLANIFICATION p2 1ere carte
			scene->changePlayerInfoPlayer(1);
			scene->changeWindow(PLAYER_INFO);
			p2->keepCard(0);	//P2 Keep Ile d'Avalon
			
			break;
        case 15:         //PLANIFICATION 2-2
			scene->changeWindow(PLAYER_INFO);
			p2->keepCard(2);	//P2 Keep Zeppelin
			
			break;
        case 16:         //PLANIFICATION 2-3
			scene->changeWindow(PLAYER_INFO);
			p2->keepCard(1);	//P2 Keep Centre de la Terre
			
			break;
        case 17:         //PLANIFICATION 2-4
			scene->changeWindow(PLAYER_INFO);
			p2->discardCard(0,true);				//Discard Exploration for Avalon
			p2->addResource(state::EXPLORATION,0);
			
			break;
        case 18:         //PLANIFICATION 2-5
			scene->changeWindow(PLAYER_INFO);
			p2->discardCard(0,true);				//Discard Exploration for Avalon
			p2->addResource(state::EXPLORATION,0);
			
			break;
        case 19:         //PLANIFICATION 2-6
			scene->changeWindow(PLAYER_INFO);
			p2->discardCard(0,true);				//Discard Exploration for Avalon
			p2->addResource(state::EXPLORATION,0);
			
			break;
		case 20:		//PLANIFICATION 2-7
			scene->changeWindow(PLAYER_INFO);
			p2->discardCard(0,true);				//Discard Exploration for Centre
			p2->addResource(state::EXPLORATION,2);
			game->endPlanification();
			break;
		case 21: 		//PROD INIT
			scene->changeWindow(MAIN_WINDOW);
			game->initProduction();
		break;
		case 22: 		//PROD MATERIAL
			scene->changeWindow(MAIN_WINDOW);
			game->nextProduction();
			p1->addResource(state::MATERIAL,0);		//P1 Give 1 Material to Tour
			break;
		case 23:		//PROD ENERGY
			scene->changeWindow(MAIN_WINDOW);
			p1->endPlanification();
			p2->endPlanification();
			game->nextProduction();
			p2->addResource(state::ENERGY,1);		//P2 build Zepellin with 2 Energy
			p2->addResource(state::ENERGY,1);
			break;
		case 24:		//PROD SCIENCE
			scene->changeWindow(MAIN_WINDOW);
			p1->endPlanification();
			p2->endPlanification();
			game->nextProduction();
			p2->sendResourceToEmpire(state::SCIENCE);	//P2 discard 1 Science
			//p1->addResource(state::SCIENCE,0);
			break;
		case 25:		//PROD GOLD
			scene->changeWindow(MAIN_WINDOW);
			p1->endPlanification();
			p2->endPlanification();
			game->nextProduction();
			p1->addResource(state::GOLD,0);			//P1 Finish Tour with 3 Gold and 1 Financier
			p1->addResource(state::GOLD,0);
			p1->addResource(state::GOLD,0);
			p1->addResource(state::FINANCIER,0);
			//p1->addResource(state::GOLD,0);
			break;
		case 26:		//PROD EXPLORATION
			scene->changeWindow(MAIN_WINDOW);
			p1->endPlanification();
			p2->endPlanification();
			game->nextProduction();
			p1->sendResourceToEmpire(state::EXPLORATION);	//P1 Discard 1 Exploration
			p2->addResource(state::EXPLORATION,0);	//P2 Finish Avalon
			p2->addResource(state::EXPLORATION,0);
			//p1->addResource(state::EXPLORATION,0);
			break;
		case 27:		//FINISHED
			p1->endPlanification();
			p2->endPlanification();
			game->endGame();
			break;
        default:
			break;
    }

}