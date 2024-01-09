#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

#define CROSS_SIZE 0.01f
#define MAX_NUMBER_OF_GAME_IA 50

#include <state.h>
#include <render.h>
#include <ai.h>
#include <engine.h>

#include "../shared/state.h"
#include "render.h"

using namespace state;
using namespace render;

void next_step(int etape,Game* game,Player* p1,Player* p2,Scene* scene);
void displayMessage();
void displayInformationFromAnAI(std::string nameOfAI, std::vector<int> numberOfPoints, std::vector<int> numberOfCardsBuilt);

int main(int argc,char* argv[])
{
    if (1 == argc)
    {
        std::cout << "Not enough arguments. You can try the following commands:" << std::endl;
        displayMessage();
        return EXIT_FAILURE;
    }

    std::string userInput = argv[1];

    if ("hello" == userInput)
    {
        std::cout << "Hello World!" << std::endl;
        return EXIT_SUCCESS;
    }
	else if ("engine" == userInput)
    {
        //Print Temporary Manual Commands
        std::cout<<"**Temporary Manual Commands**" << std::endl;
        std::cout<<"*Change Window Commands*" << std::endl;
        std::cout<<"A - Main Window" << std::endl;
        std::cout<<"Z - Drafting Window" << std::endl;
        std::cout<<"E - Planification Window" << std::endl;
        std::cout<<"R - Full Info Player Window" << std::endl;
        std::cout<<"> On This Window (Player Info):" << std::endl;
        std::cout<<"> Q - Display Player 1" << std::endl;
        std::cout<<"> S - Display Player 2" << std::endl;
        std::cout<<"*Game Commands*" << std::endl;
        std::cout<<"Space - Go to the next step of the testing game" << std::endl;

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
        std::vector<state::Player*> players;
        players.push_back(player1);
        players.push_back(player2);

        //Creation of the instance of the Game class
        state::Game game = state::Game(players,true);

        game.initGame();

        //Creation of the instance of the Scene class
        Scene scene = Scene(&game,tr_scale);

        //Observable
        scene.setupObserver(&game);
        scene.setupObserver(player1);
        scene.setupObserver(player2);

        //Creation of the Font for the Texts
        sf::Font font;
        font.loadFromFile("./resources/font/arial.ttf");

        //Creation of the instance of sf::Event class that will received user's inputs.
        sf::Event event;


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
                    //std::cout<<to_string(event.key.code) << std::endl; //Debug Print the code of pressed key
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
                        next_step(etape,&game,player1,player2,&scene);    //Go to the next step
                        etape++;
                    }
                        
                }
            }

            scene.draw(window);

            //Display the new content of the window
            window.display();
        }
        std::cout << "Exit Successfully !" << std::endl;

        return EXIT_SUCCESS;
    }

    else if ("AI" == userInput)
    {
        if (3 == argc)
        {
            std::cout << "./bin/client AI <x> <y>: Will run x game played by y AI." << std::endl;
            displayMessage();
            return EXIT_FAILURE;
        }
        int numberOfGames = std::atoi(argv[2]);
        int numberOfAI = std::atoi(argv[3]);
        if (2 > numberOfAI || 5 < numberOfAI || 1 > numberOfGames || MAX_NUMBER_OF_GAME_IA < numberOfGames)
        {
            std::cout << "./bin/client AI <x> <y>: Will run x game played by y AI." << std::endl;
            std::cout << "You have to respect 1 < x < " << MAX_NUMBER_OF_GAME_IA << " and 1 < y < 6" << std::endl;
            return EXIT_FAILURE;
        }
        
        std::cout << numberOfGames << " games containing " << numberOfAI << " AI are going to be created. When they are finished, some statistics will be displayed." << std::endl << std::endl;

        std::vector<std::vector<int>> AI_numberOfPoints(numberOfAI, std::vector<int>(numberOfGames, 0));
        std::vector<std::vector<int>> AI_numberOfBuiltCards(numberOfAI, std::vector<int>(numberOfGames, 0));

        std::vector<float> numberOfWins(numberOfAI, 0);
        float numberOfTie = 0;

        for (int gameNumber = 0; gameNumber < numberOfGames; gameNumber++)
        {
            std::vector<state::Player*> ais = {};
            for (int i = 0; i < numberOfAI; i++)
            {
                //state::Player* newAI = new ai::AIRandom("dummy", -i);
                state::Player* newAI;
                if (i%2)
                {
                    newAI = new ai::AIRandom("dummy", -i-1);
                }
                else
                {
                    newAI = new ai::AIAdvanced("smart", -i-1);
                }
                //state::Player* newAI = new ai::AIAdvanced("dummy", -i-1);
                ais.push_back(newAI);
            }

            state::Game* game = new state::Game(ais);
            engine::Engine* engineOfGame = new engine::Engine(game, {});
            engineOfGame->gameRunning();

            for (int i = 0; i < numberOfAI; i++)
            {
                AI_numberOfPoints[i].push_back(game->getPlayers()[i]->computeVictoryPoint());
                AI_numberOfBuiltCards[i].push_back(game->getPlayers()[i]->getBuiltCards().size());
            }

            // Checking who won.
            std::vector<int> winners = game->getWinners();
            if (winners.size() == (size_t) numberOfAI)
            {
                numberOfTie++ ;
            }
            else
            {
                for (int winnerIndex : winners)
                {
                    numberOfWins[winnerIndex] ++;
                }
            }

            delete engineOfGame;
            std::cout << "Game " << gameNumber+1 << "/" << numberOfGames << " finished." << std::endl;
        }


        // Display stats of all games per AI.
        for (int i = 0; i < numberOfAI; i++)
        {
            std::string type;
            if (i%2)
            {
                type = "random";
            }
            else
            {
                type = "advanced";
            }
            std::string name = "AI " + std::to_string(i) + " (" + type + ")";
            displayInformationFromAnAI(name, AI_numberOfPoints[i], AI_numberOfBuiltCards[i]);
        }

        // Display global stats of all games per AI.
        for (int i = 0; i < numberOfAI; i++)
        {
            std::string type;
            if (i%2)
            {
                type = "random";
            }
            else
            {
                type = "advanced";
            }
            std::cout << "AI " << type << " " << i <<" won " << numberOfWins[i] << "/" << numberOfGames << " games, a ratio of " << 100*(numberOfWins[i] / numberOfGames) << "%." << std::endl;
        }
        std::cout << "There was a tie in " << numberOfTie << "/" << numberOfGames << " games, a ratio of " << 100*(numberOfTie / numberOfGames) << "%." << std::endl;

        return EXIT_SUCCESS;
    }
    std::cout << "Invalid argument." << std::endl;
	displayMessage();
    return EXIT_FAILURE;
}

void displayInformationFromAnAI(std::string nameOfAI, std::vector<int> numberOfPoints, std::vector<int> numberOfCardsBuilt)
{
    auto maxScoreElement = std::max_element(numberOfPoints.begin(), numberOfPoints.end());
    double meanScore = std::accumulate(numberOfPoints.begin(), numberOfPoints.end(), 0.0) / numberOfPoints.size();

    auto maxCardElement = std::max_element(numberOfCardsBuilt.begin(), numberOfCardsBuilt.end());
    double meanCardBuilt = std::accumulate(numberOfCardsBuilt.begin(), numberOfCardsBuilt.end(), 0.0) / numberOfCardsBuilt.size();
    
    std::cout << "Max number of points of " << nameOfAI << ":       " << *maxScoreElement << std::endl;
    std::cout << "Mean number of points of " << nameOfAI << ":      " << meanScore << std::endl;
    std::cout << "Max number of built cards by " << nameOfAI << ":  " << *maxCardElement << std::endl;
    std::cout << "Mean number of built cards by " << nameOfAI << ": " << meanCardBuilt << std::endl << std::endl;
}

void displayMessage()
{
	std::cout << "./bin/client hello:  Display a hello world message, that shows that everything worked." << std::endl;
	std::cout << "./bin/client engine: Will show a testing game, which is a game in one turn." << std::endl;
	std::cout << "./bin/client AI <x> <y>: Will run x game played by y random AI. We highly recommand to have x*y < 100." << std::endl;
}

void next_step(int etape,Game* game,Player* p1,Player* p2,Scene* scene){
    switch(etape){
        case 0:         //DRAFT 1ere carte
            scene->changeWindow(DRAFTING_WINDOW);
            p1->chooseDraftCard(0);        //P1 Choose J
            p2->chooseDraftCard(0);        //P2 Choose Z
            game->nextDraft();
            break;
        case 1:         //DRAFT 2eme carte
            scene->changeWindow(DRAFTING_WINDOW);
            p1->chooseDraftCard(5);        //P1 Choose To
            p2->chooseDraftCard(4);        //P2 Choose Î
            game->nextDraft();
            
            break;
        case 2:         //DRAFT 3eme carte
            scene->changeWindow(DRAFTING_WINDOW);
            p1->chooseDraftCard(0);        //P1 Choose B
            p2->chooseDraftCard(0);        //P2 Choose Z
            game->nextDraft();
            
            break;
        case 3:         //DRAFT 4eme carte
            scene->changeWindow(DRAFTING_WINDOW);
            p1->chooseDraftCard(3);        //P1 Choose T
            p2->chooseDraftCard(2);        //P2 Choose C
            game->nextDraft();
            
            break;
        case 4:         //DRAFT 5eme carte
            scene->changeWindow(DRAFTING_WINDOW);
            p1->chooseDraftCard(0);//B
            p2->chooseDraftCard(0);//Z
            game->nextDraft();
            
            break;
        case 5:         //DRAFT 6eme carte
            scene->changeWindow(DRAFTING_WINDOW);
            p1->chooseDraftCard(0);//Z
            p2->chooseDraftCard(1);//Z
            game->nextDraft();
            
            break;
        case 6:         //DRAFT 7eme carte
            scene->changeWindow(DRAFTING_WINDOW);
            p1->chooseDraftCard(0);//B
            p2->chooseDraftCard(0);//Z
            game->nextDraft();
            
            break;
        case 7:         //PLANIFICATION p1 1ere carte
            scene->changeWindow(PLANIFICATION_WINDOW);
            p1->keepCard(3);    //P1 Keep Tresor de Barbe Noire
            
            break;
        case 8:         //PLANIFICATION 1-2
            scene->changeWindow(PLANIFICATION_WINDOW);
            p1->keepCard(1);    //P1 Keep Tour Géante
            
            break;
        case 9:         //PLANIFICATION 1-3
            scene->changeWindow(PLANIFICATION_WINDOW);
            p1->discardCard(1,true);                //Discard Exploration for Tresor
            p1->addResource(state::EXPLORATION,0);
            
            break;
        case 10:         //PLANIFICATION 1-4
            scene->changeWindow(PLANIFICATION_WINDOW);
            p1->discardCard(0,true);                //Discard Material for Tour
            p1->addResource(state::MATERIAL,1);
            
            break;
        case 11:         //PLANIFICATION 1-5
            scene->changeWindow(PLANIFICATION_WINDOW);
            p1->discardCard(0,true);                //Discard Exploration for Tresor
            p1->addResource(state::EXPLORATION,0);
            
            break;
        case 12:         //PLANIFICATION 1-6
            scene->changeWindow(PLANIFICATION_WINDOW);
            p1->discardCard(0,true);                //Discard Exploration for Tresor
            p1->addResource(state::EXPLORATION,0);    //Tresor built
            
            break;
        case 13:        //PLANIFICATION 1-7
            scene->changeWindow(PLANIFICATION_WINDOW);
            p1->discardCard(0,true);                //Discard Exploration in Empire
            p1->sendResourceToEmpire(state::EXPLORATION);
            
            break;
        case 14:         //PLANIFICATION p2 1ere carte
            scene->changePlayerInfoPlayer(1);
            scene->changeWindow(PLAYER_INFO);
            p2->keepCard(1);    //P2 Keep Ile d'Avalon
            
            break;
        case 15:         //PLANIFICATION 2-2
            scene->changeWindow(PLAYER_INFO);
            p2->keepCard(0);    //P2 Keep Zeppelin
            
            break;
        case 16:         //PLANIFICATION 2-3
            scene->changeWindow(PLAYER_INFO);
            p2->keepCard(1);    //P2 Keep Centre de la Terre
            
            break;
        case 17:         //PLANIFICATION 2-4
            scene->changeWindow(PLAYER_INFO);
            p2->discardCard(0,true);                //Discard Exploration for Avalon
            p2->addResource(state::EXPLORATION,0);
            
            break;
        case 18:         //PLANIFICATION 2-5
            scene->changeWindow(PLAYER_INFO);
            p2->discardCard(0,true);                //Discard Exploration for Avalon
            p2->addResource(state::EXPLORATION,0);
            
            break;
        case 19:         //PLANIFICATION 2-6
            scene->changeWindow(PLAYER_INFO);
            p2->discardCard(0,true);                //Discard Exploration for Avalon
            p2->addResource(state::EXPLORATION,0);
            
            break;
        case 20:        //PLANIFICATION 2-7
            scene->changeWindow(PLAYER_INFO);
            p2->discardCard(0,true);                //Discard Exploration for Centre
            p2->addResource(state::EXPLORATION,2);
            game->endPlanification();
            break;
        case 21:         //PROD INIT
            scene->changeWindow(MAIN_WINDOW);
            game->initProduction();
        break;
        case 22:         //PROD MATERIAL
            scene->changeWindow(MAIN_WINDOW);
            p1->addResource(state::MATERIAL,1);        //P1 Give 1 Material to Tour
            break;
        case 23:        //PROD ENERGY
            scene->changeWindow(MAIN_WINDOW);
            p1->endProduction();
            p2->endProduction();
            game->nextProduction();
            p2->addResource(state::ENERGY,1);        //P2 build Zepellin with 2 Energy
            p2->addResource(state::ENERGY,1);
            break;
        case 24:        //PROD SCIENCE
            scene->changeWindow(MAIN_WINDOW);
            p1->endProduction();
            p2->endProduction();
            game->nextProduction();
            p2->sendResourceToEmpire(state::SCIENCE);    //P2 discard 1 Science
            //p1->addResource(state::SCIENCE,0);
            break;
        case 25:        //PROD GOLD
            scene->changeWindow(MAIN_WINDOW);
            p1->endProduction();
            p2->endProduction();
            game->nextProduction();
            p1->addResource(state::GOLD,0);            //P1 Finish Tour with 3 Gold and 1 Financier
            p1->addResource(state::GOLD,0);
            p1->addResource(state::GOLD,0);
            p1->addResource(state::FINANCIER,0);
            //p1->addResource(state::GOLD,0);
            break;
        case 26:        //PROD EXPLORATION
            scene->changeWindow(MAIN_WINDOW);
            p1->endProduction();
            p2->endProduction();
            game->nextProduction();
            p1->sendResourceToEmpire(state::EXPLORATION);    //P1 Discard 1 Exploration
            p2->addResource(state::EXPLORATION,0);    //P2 Finish Avalon
            p2->addResource(state::EXPLORATION,0);
            //p1->addResource(state::EXPLORATION,0);
            break;
        case 27:        //FINISHED
            p1->endProduction();
            p2->endProduction();
            game->nextProduction();
            break;
        default:
            break;
    }

}