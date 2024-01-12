#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <thread>
#include <mutex>
#include <fstream>
#include <sstream>
#include <string>


// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

#define CROSS_SIZE 0.01f
#define MAX_NUMBER_OF_GAME_IA 5000

#include <state.h>
#include <render.h>
#include <ai.h>
#include <engine.h>

#include "../constants/constants/GameConstants.h"
#include "../constants/constants/CustomTypes.h"

#include "../shared/state.h"
#include "render.h"

sf::RenderWindow* instanciatePLTWindow();
render::Scene* instanciateRender(engine::Engine*& engineOfGame, std::shared_ptr<state::Game>& game, constants::playersList players, std::mutex& locker);

void handleOpenedWindow(sf::RenderWindow* window, render::Scene* scene, std::shared_ptr<state::Game> game, bool isTestingGame);
void next_step(int etape, std::shared_ptr<state::Game> game, std::shared_ptr<state::Player> p1, std::shared_ptr<state::Player> p2, render::Scene* scene);

void displayMessage();
void displayTemporaryCommands(bool testing);
void displayInformationFromAnAI(std::string nameOfAI, std::vector<int> numberOfPoints, std::vector<int> numberOfCardsBuilt);

void addAIToVector(constants::playersList& players, int nmberOfAIToAdd);

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
        displayTemporaryCommands(true);

        //Creation of the window
        sf::RenderWindow* window = instanciatePLTWindow();

        //Creation of testing instances of Player class
        std::shared_ptr<state::Player> player1 = std::make_shared<state::Player>("MOI",0);
        std::shared_ptr<state::Player> player2 = std::make_shared<state::Player>("TOI",1);

        //Creation of the vector players
        constants::playersList players;
        players.push_back(player1);
        players.push_back(player2);

        //Creation of the instance of the Game class
        std::shared_ptr<state::Game> game = nullptr;
        engine::Engine* engineOfGame = nullptr;
        std::mutex locker;

        render::Scene* scene = instanciateRender(engineOfGame, game, players,locker);

        // Intialization of the game
        game->initGame();

        //Main Loop active while the window is still open
        handleOpenedWindow(window, scene, game, true);

        std::cout << "Exit Successfully !" << std::endl;

        return EXIT_SUCCESS;
    }
    else if ("AI" == userInput)
    {
        if (4 != argc)
        {
            std::cout << "./bin/client AI <x> <y>: Will run x game played by y AI." << std::endl;
            return EXIT_FAILURE;
        }
        
        // Convert user inputs.
        const int numberOfGames = std::atoi(argv[2]);
        int numberOfAI = std::atoi(argv[3]);
        
        // Checking values.
        if (MIN_NUMBER_OF_PLAYERS > numberOfAI || MAX_NUMBER_OF_PLAYERS < numberOfAI || 1 > numberOfGames || MAX_NUMBER_OF_GAME_IA < numberOfGames)
        {
            std::cout << "./bin/client AI <x> <y>: Will run x game played by y AI." << std::endl;
            std::cout << "You have to respect 1 < x < " << MAX_NUMBER_OF_GAME_IA << " and 1 < y < 6" << std::endl;
            return EXIT_FAILURE;
        }
        
        std::cout << numberOfGames << " games containing " << numberOfAI << " AI are going to be created. When they are finished, some statistics will be displayed." << std::endl << std::endl;

        // Vector that contains scores, number of built cards and ties of the AI.
        std::vector<std::vector<int>> AI_numberOfPoints(numberOfAI, std::vector<int>(numberOfGames, 0));
        std::vector<std::vector<int>> AI_numberOfBuiltCards(numberOfAI, std::vector<int>(numberOfGames, 0));

        std::vector<float> numberOfWins(numberOfAI, 0);
        float numberOfTie = 0;

        // Play numberOfGames games.
        for (int gameNumber = 0; numberOfGames > gameNumber; gameNumber++)
        {
            // Construct AI (1 random, 1 advanced, 1 random, ...)
            constants::playersList ais = {};
            addAIToVector(ais, numberOfAI);

            // Construct the game and launch it.
            std::shared_ptr<state::Game> game = nullptr;
            engine::Engine* engineOfGame = nullptr;
            std::mutex locker;
            (void) instanciateRender(engineOfGame, game, ais, locker);

            engineOfGame->gameRunning(true);


            // Add scores of AI to corresponding vectors
            for (int i = 0; i < numberOfAI; i++)
            {
                AI_numberOfPoints[i].push_back(game->getPlayers()[i]->computeVictoryPoint());
                AI_numberOfBuiltCards[i].push_back(game->getPlayers()[i]->getBuiltCards().size());
            }

            // Checking who won and write it into the vector.
            std::vector<int> winners = game->getWinners();
            if (1 != winners.size())
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

            // Display for 1 game / 10 the fact that some game just finished.
            if (!((gameNumber + 1) % 10))
            {
                std::cout << "Game " << gameNumber + 1 << "/" << numberOfGames << " finished." << std::endl;
            }
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
    else if ("Player" == userInput)
    {
        if (3 != argc)
        {
            std::cout << "./bin/client Player <x> <y>: Run a game where you play! x: Number of opponents." << std::endl;
            return EXIT_FAILURE;
        }

        // Convert user inputs.
        const int numberOfOpponents = std::atoi(argv[2]);
        
        // Checking values.
        if ((MIN_NUMBER_OF_PLAYERS-1) > numberOfOpponents || (MAX_NUMBER_OF_PLAYERS-1) < numberOfOpponents)
        {
            std::cout << "./bin/client Player <x>: Run a game where you play! x: Number of opponents." << std::endl;
            std::cout << "You have to respect" << (MIN_NUMBER_OF_PLAYERS-1) << " < x < "   << (MAX_NUMBER_OF_PLAYERS-1) << std::endl;
            return EXIT_FAILURE;
        }

        //Creation of the window
        sf::RenderWindow* window = instanciatePLTWindow();

        // Creation of the player, adding it to the vector and then create all AI to add them to the game.
        std::shared_ptr<state::Player> realPlayer = std::make_shared<state::Player>("You!", 10);
        constants::playersList players;
        players.push_back(realPlayer);
        addAIToVector(players, numberOfOpponents);

        std::shared_ptr<state::Game> game = nullptr;
        engine::Engine* engineOfGame = nullptr;
        std::mutex locker;
        render::Scene* scene = instanciateRender(engineOfGame, game, players, locker);

        game->initGame();

        // Creating the thread that contains the engine that does not require to launch the game.
        std::thread initThread(&engine::Engine::gameRunning, engineOfGame, false);

        // Main Loop active while the window is still open
        handleOpenedWindow(window, scene, game, false);

        // Wait the end of the engine thread to exit.
        initThread.join();

        std::cout << "Game exited with success!" << std::endl;
        return EXIT_SUCCESS;
    }
    else if ("reload" == userInput)
    {
        // Instantiation of a fstream object which is a file.
        std::ifstream readingFile;

        // Opening the file in reading mode.
        readingFile.open("./bin/save.json", std::ios::in);

        // Checking if the file is correctly opened.
        if (! readingFile.is_open())
        {
            perror("Error opening the saved game");
            return EXIT_FAILURE;
        }

        std::string jsonData((std::istreambuf_iterator<char>(readingFile)), std::istreambuf_iterator<char>());

        // Create a Json::CharReaderBuilder
        Json::CharReaderBuilder readerBuilder;

        // Parse the JSON data into a Json::Value
        Json::Value root;
        std::istringstream jsonStream(jsonData);
        Json::parseFromStream(readerBuilder, jsonStream, &root, nullptr);

        //Creation of the window
        sf::RenderWindow* window = instanciatePLTWindow();

        std::shared_ptr<state::Game> game = std::make_shared<state::Game>(root);
        std::mutex locker;
        engine::Engine* engineOfGame = new engine::Engine(game, locker);
        render::Scene* scene = new render::Scene(game, locker, engineOfGame);

        //Observable
        scene->setupObserver(game);
        for (std::shared_ptr<state::Player> player : game->getPlayers())
        {
            scene->setupObserver(player);
        }
        game->notifyObservers(4095);

        // Creating the thread that contains the engine that does not require to launch the game.
        std::thread initThread(&engine::Engine::gameRunning, engineOfGame, false);

        //Main Loop active while the window is still open
        handleOpenedWindow(window, scene, game, false);

        initThread.join();

        std::cout << "Game exited with sucess!" << std::endl;
        return EXIT_SUCCESS;

    }
    std::cout << "Invalid argument." << std::endl;
	displayMessage();
    return EXIT_FAILURE;
}

void addAIToVector(constants::playersList& players, int nmberOfAIToAdd)
{
    for (int i = 0; i < nmberOfAIToAdd; i++)
    {
        std::shared_ptr<state::Player> newAI;
        if (i%2)
        {
            newAI = std::make_shared<ai::AIRandom>("random", -i-1);
        }
        else
        {
            newAI = std::make_shared<ai::AIAdvanced>("advanced", -i-1);
        }
        players.push_back(newAI);
    }
}

void handleOpenedWindow(sf::RenderWindow* window, render::Scene* scene, std::shared_ptr<state::Game> game, bool isTestingGame)
{
    //Creation of the instance of sf::Event class that will received user's inputs.
    sf::Event event;

    // Index of the step we are playing
    int etape = 0;

    //Main Loop active while the window is still open
    while (window->isOpen())
    {
        //Clear the content of the window
        window->clear();

        //Test if an event happens and save it in "event"
        while (window->pollEvent(event))
        {
            //Command to close the window
            if (event.type == sf::Event::Closed){
                window->close();
            }
            if (event.type == sf::Event::MouseButtonReleased){
                scene->buttonHandle(event, *window);
            }
            if (event.type == sf::Event::KeyPressed) {
                //std::cout<<to_string(event.key.code) << std::endl; //Debug Print the code of pressed key
                if (event.key.code == sf::Keyboard::A){
                    scene->changeWindow(render::Window::MAIN_WINDOW); //Change the window to MAIN_WINDOW
                }
                if (event.key.code == sf::Keyboard::Z){
                    scene->changeWindow(render::Window::DRAFTING_WINDOW); //Change the window to DRAFTING_WINDOW
                }
                if (event.key.code == sf::Keyboard::E){
                    scene->changeWindow(render::Window::PLANIFICATION_WINDOW); //Change the window to PLAYER_INFO
                }
                if (event.key.code == sf::Keyboard::R){
                    scene->changeWindow(render::Window::PLAYER_INFO); //Change the window to PLAYER_INFO
                }
                if (isTestingGame && event.key.code == sf::Keyboard::Q and scene->getWindow() == render::Window::PLAYER_INFO){
                    scene->changePlayerInfoPlayer(0,render::PLAYER_INFO);
                }
                if (isTestingGame && event.key.code == sf::Keyboard::S and scene->getWindow() == render::Window::PLAYER_INFO){
                    scene->changePlayerInfoPlayer(1,render::PLAYER_INFO);
                }
                if (isTestingGame && event.key.code == sf::Keyboard::Space){
                    next_step(etape,game,game->getPlayers()[0],game->getPlayers()[1],scene);    //Go to the next step
                    etape++;
                } 
            }
        }

        scene->draw(*window);

        //Display the new content of the window
        window->display();
    }
}

sf::RenderWindow* instanciatePLTWindow()
{
    int win_length = 1920;
    int win_heigth = 1080;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(win_length, win_heigth), "It's a Wonderful World!", sf::Style::Default);

    return window;
}

render::Scene* instanciateRender(engine::Engine*& engineOfGame, std::shared_ptr<state::Game>& game, constants::playersList players,std::mutex& locker)
{
    game = std::make_shared<state::Game>(players);
    
    engineOfGame = new engine::Engine(game, locker);
    render::Scene* scene = new render::Scene(game, locker, engineOfGame);
    
    for (auto player: players)
    {
        scene->setupObserver(player);
    }
    scene->setupObserver(game);

    return scene;
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
	std::cout << "./bin/client Player <x>: Run a game where you play! x: Number of opponents." << std::endl;
	std::cout << "./bin/client reload: Reload a game that has been saved. You have to previously save a game (just play 2/3 moves)" << std::endl;
}

void next_step(int etape, std::shared_ptr<state::Game> game, std::shared_ptr<state::Player> p1, std::shared_ptr<state::Player> p2, render::Scene* scene){
    switch(etape){
        case 0:         //DRAFT 1ere carte
            scene->changeWindow(render::Window::DRAFTING_WINDOW);
            p1->chooseDraftCard(0);        //P1 Choose J
            p2->chooseDraftCard(0);        //P2 Choose Z
            game->nextDraft();
            break;
        case 1:         //DRAFT 2eme carte
            scene->changeWindow(render::Window::DRAFTING_WINDOW);
            p1->chooseDraftCard(5);        //P1 Choose To
            p2->chooseDraftCard(4);        //P2 Choose Î
            game->nextDraft();
            
            break;
        case 2:         //DRAFT 3eme carte
            scene->changeWindow(render::Window::DRAFTING_WINDOW);
            p1->chooseDraftCard(0);        //P1 Choose B
            p2->chooseDraftCard(0);        //P2 Choose Z
            game->nextDraft();
            
            break;
        case 3:         //DRAFT 4eme carte
            scene->changeWindow(render::Window::DRAFTING_WINDOW);
            p1->chooseDraftCard(3);        //P1 Choose T
            p2->chooseDraftCard(2);        //P2 Choose C
            game->nextDraft();
            
            break;
        case 4:         //DRAFT 5eme carte
            scene->changeWindow(render::Window::DRAFTING_WINDOW);
            p1->chooseDraftCard(0);//B
            p2->chooseDraftCard(0);//Z
            game->nextDraft();
            
            break;
        case 5:         //DRAFT 6eme carte
            scene->changeWindow(render::Window::DRAFTING_WINDOW);
            p1->chooseDraftCard(0);//Z
            p2->chooseDraftCard(1);//Z
            game->nextDraft();
            
            break;
        case 6:         //DRAFT 7eme carte
            scene->changeWindow(render::Window::DRAFTING_WINDOW);
            p1->chooseDraftCard(0);//B
            p2->chooseDraftCard(0);//Z
            game->nextDraft();
            
            break;
        case 7:         //PLANIFICATION p1 1ere carte
            scene->changeWindow(render::Window::PLANIFICATION_WINDOW);
            p1->keepCard(3);    //P1 Keep Tresor de Barbe Noire
            
            break;
        case 8:         //PLANIFICATION 1-2
            scene->changeWindow(render::Window::PLANIFICATION_WINDOW);
            p1->keepCard(1);    //P1 Keep Tour Géante
            
            break;
        case 9:         //PLANIFICATION 1-3
            scene->changeWindow(render::Window::PLANIFICATION_WINDOW);
            p1->discardCard(1,true);                //Discard Exploration for Tresor
            p1->addResource(state::ResourceType::EXPLORATION,0);
            
            break;
        case 10:         //PLANIFICATION 1-4
            scene->changeWindow(render::Window::PLANIFICATION_WINDOW);
            p1->discardCard(0,true);                //Discard Material for Tour
            p1->addResource(state::ResourceType::MATERIAL,1);
            
            break;
        case 11:         //PLANIFICATION 1-5
            scene->changeWindow(render::Window::PLANIFICATION_WINDOW);
            p1->discardCard(0,true);                //Discard Exploration for Tresor
            p1->addResource(state::ResourceType::EXPLORATION,0);
            
            break;
        case 12:         //PLANIFICATION 1-6
            scene->changeWindow(render::Window::PLANIFICATION_WINDOW);
            p1->discardCard(0,true);                //Discard Exploration for Tresor
            p1->addResource(state::ResourceType::EXPLORATION,0);    //Tresor built
            
            break;
        case 13:        //PLANIFICATION 1-7
            scene->changeWindow(render::Window::PLANIFICATION_WINDOW);
            p1->discardCard(0,true);                //Discard Exploration in Empire
            p1->sendResourceToEmpire(state::ResourceType::EXPLORATION);
            
            break;
        case 14:         //PLANIFICATION p2 1ere carte
            scene->changePlayerInfoPlayer(1,render::PLAYER_INFO);
            scene->changeWindow(render::Window::PLAYER_INFO);
            p2->keepCard(1);    //P2 Keep Ile d'Avalon
            
            break;
        case 15:         //PLANIFICATION 2-2
            scene->changeWindow(render::Window::PLAYER_INFO);
            p2->keepCard(0);    //P2 Keep Zeppelin
            
            break;
        case 16:         //PLANIFICATION 2-3
            scene->changeWindow(render::Window::PLAYER_INFO);
            p2->keepCard(1);    //P2 Keep Centre de la Terre
            
            break;
        case 17:         //PLANIFICATION 2-4
            scene->changeWindow(render::Window::PLAYER_INFO);
            p2->discardCard(0,true);                //Discard Exploration for Avalon
            p2->addResource(state::ResourceType::EXPLORATION,0);
            
            break;
        case 18:         //PLANIFICATION 2-5
            scene->changeWindow(render::Window::PLAYER_INFO);
            p2->discardCard(0,true);                //Discard Exploration for Avalon
            p2->addResource(state::ResourceType::EXPLORATION,0);
            
            break;
        case 19:         //PLANIFICATION 2-6
            scene->changeWindow(render::Window::PLAYER_INFO);
            p2->discardCard(0,true);                //Discard Exploration for Avalon
            p2->addResource(state::ResourceType::EXPLORATION,0);
            
            break;
        case 20:        //PLANIFICATION 2-7
            scene->changeWindow(render::Window::PLAYER_INFO);
            p2->discardCard(0,true);                //Discard Exploration for Centre
            p2->addResource(state::ResourceType::EXPLORATION,2);
            game->endPlanification();
            break;
        case 21:         //PROD INIT
            scene->changeWindow(render::Window::MAIN_WINDOW);
            break;
        case 22:         //PROD MATERIAL
            scene->changeWindow(render::Window::MAIN_WINDOW);
            p1->addResource(state::ResourceType::MATERIAL,1);        //P1 Give 1 Material to Tour
            break;
        case 23:        //PROD ENERGY
            scene->changeWindow(render::Window::MAIN_WINDOW);
            p1->endProduction();
            p2->endProduction();
            game->nextProduction();
            p2->addResource(state::ResourceType::ENERGY,1);        //P2 build Zepellin with 2 Energy
            p2->addResource(state::ResourceType::ENERGY,1);
            break;
        case 24:        //PROD SCIENCE
            scene->changeWindow(render::Window::MAIN_WINDOW);
            p1->endProduction();
            p2->endProduction();
            game->nextProduction();
            p2->sendResourceToEmpire(state::ResourceType::SCIENCE);    //P2 discard 1 Science
            //p1->addResource(state::ResourceType::SCIENCE,0);
            break;
        case 25:        //PROD GOLD
            scene->changeWindow(render::Window::MAIN_WINDOW);
            p1->endProduction();
            p2->endProduction();
            game->nextProduction();
            p1->addResource(state::ResourceType::GOLD,0);            //P1 Finish Tour with 3 Gold and 1 Financier
            p1->addResource(state::ResourceType::GOLD,0);
            p1->addResource(state::ResourceType::GOLD,0);
            p1->addResource(state::ResourceType::FINANCIER,0);
            //p1->addResource(state::ResourceType::GOLD,0);
            break;
        case 26:        //PROD EXPLORATION
            scene->changeWindow(render::Window::MAIN_WINDOW);
            p1->endProduction();
            p2->endProduction();
            game->nextProduction();
            p1->sendResourceToEmpire(state::ResourceType::EXPLORATION);    //P1 Discard 1 Exploration
            p2->addResource(state::ResourceType::EXPLORATION,0);    //P2 Finish Avalon
            p2->addResource(state::ResourceType::EXPLORATION,0);
            //p1->addResource(state::ResourceType::EXPLORATION,0);
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

void displayTemporaryCommands(bool testing)
{
    //Print Temporary Manual Commands
    if(testing){
        std::cout<<"**Temporary Manual Commands**" << std::endl;
    }
    std::cout<<"*Change Window Commands*" << std::endl;
    std::cout<<"A - Main Window" << std::endl;
    std::cout<<"Z - Drafting Window" << std::endl;
    std::cout<<"E - Planification Window" << std::endl;
    std::cout<<"R - Full Info Player Window" << std::endl;
    if(testing)
    {
        std::cout<<"> On This Window (Player Info):" << std::endl;
        std::cout<<"> Q - Display Player 1" << std::endl;
        std::cout<<"> S - Display Player 2" << std::endl;
        std::cout<<"*Game Commands*" << std::endl;
        std::cout<<"Space - Go to the next step of the testing game" << std::endl;
    }
}