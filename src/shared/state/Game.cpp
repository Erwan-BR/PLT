//Written by Adrien MILLASSEAU and Onur DEMIRBAS

#include "Game.h"
#include <algorithm>
#include <random>
#include <fstream>

namespace state {
	///@brief Create an instance of the class Game
	Game::Game() :
		players(),
		turn(0),
		phase(PRODUCTION),
		deck(),
		isClockwise(true)
	{

	}

	///@brief Create an instance of the class Game with players specified
	///@param players Vector of pointers which designate the players of the game
	Game::Game(std::vector<Player*> players) :
		players(players),
		turn(0),
		phase(PRODUCTION),
		deck(),
		isClockwise(true)
	{

	}

	///@brief Destructor of the Class Game
	Game::~Game ()
	{

	}

	///@brief Initialize the game
	void Game::initGame ()
	{
		std::vector<EmpireCard*> empires = initEmpire();
		initCards();
		initPlayers(empires);
		startGame();
	}

	///@brief Create and Initialize the Cards for the game
	void Game::initCards ()
	{
		// To do: Create the deck with all the cards
		auto rng = std::default_random_engine {};
		std::shuffle(std::begin(deck), std::end(deck), rng);
	}

	/// @brief Import all Cards from the CSV file.
	void Game::importCardsFromCsv ()
	{
		// Instantiation of a fstream object which is a file.
		std::fstream readingFile;

		// Opening the file in reading mode.
		readingFile.open("listAllDevelopmentCards.csv", std::ios::in);

		// Checking if the file is correctly opened.
		if (readingFile.is_open())
		{
			// Instantiation of a string that will represent the successive lines.
			std::string currentLine;

			// Looping while we can get the following line (while another exists in fact).
			while(getline(readingFile, currentLine))
			{
				// Call a private function that add a developmentCard to the deck.
				this->addSingleCardToDeck(currentLine);
			}
			// Closing the file because we do not need it anymore.
			readingFile.close();
		}
	}

	/// @brief Add a card to the deck, from a line of the CSV file.
	/// @param lineFromCsvFile Line from the CSV that contains data of a DevelopmentCard.
	void Game::addSingleCardToDeck (std::string lineFromCsvFile)
	{
		return ;
	}

	///@brief Create and Initialize the Empire for the game
	std::vector<EmpireCard*> Game::initEmpire ()
	{	
		// empire AFRICA
		ResourceToProduce* firstResourceToProduceAFRICA = new ResourceToProduce{ResourceType::MATERIAL, 2, state::CardType::NONETYPE};
    	ResourceToProduce* secondResourceToProduceAFRICA = new ResourceToProduce{ResourceType::EXPLORATION, 1, state::CardType::NONETYPE};
		std::vector<ResourceToProduce*> productionGainAFRICA = {firstResourceToProduceAFRICA,secondResourceToProduceAFRICA};
		sf::Texture designAFRICA;
   		CardVictoryPoint* victoryPointsAFRICA  = new CardVictoryPoint{3,state::CardType::DISCOVERY};
		EmpireCard* africa = new EmpireCard("AFRICA", productionGainAFRICA, designAFRICA, victoryPointsAFRICA, {/*prob face B*/}, {/*victorypoints face B*/}, AFRICA);
	
		// empire NORAM
		ResourceToProduce* firstResourceToProduceNORAM = new ResourceToProduce{ResourceType::MATERIAL, 3, state::CardType::NONETYPE};
    	ResourceToProduce* secondResourceToProduceNORAM = new ResourceToProduce{ResourceType::GOLD, 1, state::CardType::NONETYPE};
		std::vector<ResourceToProduce*> productionGainNORAM = {firstResourceToProduceNORAM,secondResourceToProduceNORAM};
		sf::Texture designNORAM;
   		CardVictoryPoint* victoryPointsNORAM  = new CardVictoryPoint{1,state::ResourceType::FINANCIER};
		EmpireCard* noram = new EmpireCard("NORAM", productionGainNORAM, designNORAM, victoryPointsNORAM, {/*prob face B*/}, {/*victorypoints face B*/}, NORAM);
		
		// empire ASIA
		ResourceToProduce* firstResourceToProduceASIA = new ResourceToProduce{ResourceType::MATERIAL, 1, state::CardType::NONETYPE};
    	ResourceToProduce* secondResourceToProduceASIA = new ResourceToProduce{ResourceType::GOLD, 2, state::CardType::NONETYPE};
		std::vector<ResourceToProduce*> productionGainASIA = {firstResourceToProduceASIA,secondResourceToProduceASIA};
		sf::Texture designASIA;
   		CardVictoryPoint* victoryPointsASIA  = new CardVictoryPoint{2,state::CardType::PROJECT};
		EmpireCard* asia = new EmpireCard("ASIA", productionGainASIA, designASIA, victoryPointsASIA, {/*prob face B*/}, {/*victorypoints face B*/}, ASIA);
		
		// empire EUROPE
		ResourceToProduce* firstResourceToProduceEUROPE = new ResourceToProduce{ResourceType::MATERIAL, 2, state::CardType::NONETYPE};
    	ResourceToProduce* secondResourceToProduceEUROPE = new ResourceToProduce{ResourceType::ENERGY, 1, state::CardType::NONETYPE};
    	ResourceToProduce* thirdResourceToProduceEUROPE = new ResourceToProduce{ResourceType::SCIENCE, 1, state::CardType::NONETYPE};
		std::vector<ResourceToProduce*> productionGainEUROPE = {firstResourceToProduceEUROPE,secondResourceToProduceEUROPE,thirdResourceToProduceEUROPE};
		sf::Texture designEUROPE;
   		CardVictoryPoint* victoryPointsEUROPE  = new CardVictoryPoint{1,state::ResourceType::COLONEL};
		EmpireCard* europe = new EmpireCard("EUROPE", productionGainEUROPE, designEUROPE, victoryPointsEUROPE, {/*prob face B*/}, {/*victorypoints face B*/}, EUROPE);
		
		// empire AZTEC
		ResourceToProduce* firstResourceToProduceAZTEC = new ResourceToProduce{ResourceType::MATERIAL, 2, state::CardType::NONETYPE};
    	ResourceToProduce* secondResourceToProduceAZTEC = new ResourceToProduce{ResourceType::SCIENCE, 2, state::CardType::NONETYPE};
		std::vector<ResourceToProduce*> productionGainAZTEC = {firstResourceToProduceAZTEC,secondResourceToProduceAZTEC};
		sf::Texture designAZTEC;
   		CardVictoryPoint* victoryPointsAZTEC  = new CardVictoryPoint{2,state::CardType::RESEARCH};
		EmpireCard* aztec = new EmpireCard("AZTEC", productionGainAZTEC, designAZTEC, victoryPointsAZTEC, {/*prob face B*/}, {/*victorypoints face B*/}, AZTEC);

		std::vector<EmpireCard*> empires = {africa,noram,asia,europe,aztec};
		auto rng = std::default_random_engine {};
		std::shuffle(std::begin(empires), std::end(empires), rng);
	}

	///@brief Start the game
	void Game::startGame ()
	{
		nextPhase();
	}

	///@brief Manage the progress of the game and start the next phase among Draft, Planification and Production
	void Game::nextPhase ()
	{
		if(DRAFT == this->phase)
		{
			this->phase = PLANIFICATION;
			initPlanification();
		}
		else if(PLANIFICATION == this->phase)
		{
			this->phase = PRODUCTION;
		}
		else if(PRODUCTION == this->phase)
		{
			newTurn();
			this->phase = DRAFT;
			initDraft();
		}		
	}

	///@brief Start one of the four turn of the game
	void Game::newTurn ()
	{
		turn = turn + 1;
		if(turn == 5)
		{
			endGame();
		}

		if (turn%2 == 1)
		{
			isClockwise = true;
		}
		else
		{
			isClockwise = false;
		}
		

	}

	///@brief Initialize the Draft part of the game during which players select their cards
	void Game::initDraft ()
	{
		for(Player* player : this->players)
		{
			// Initialise the cards that will be given to the players
			std::vector<DevelopmentCard*> draft;
			int i;
			for(i=0;i<6;i++)
			{
				draft.push_back(deck.back());
				deck.pop_back();
			}
			//setDraftingCars(draft);

		}
	}

	///@brief Start a Draft
	void Game::nextDraft ()
	{
		// 7 drafted cards
		for(int i=0;i<7;i++)
		{
			for(Player* player : this->players)
			{

			}
		}
		endDraft();

	}

	///@brief End the current Draft phase
	void Game::endDraft ()
	{
		nextPhase();
	}

	///@brief Initialize the Planification phase during which players choose the cards they will try to build
	void Game::initPlanification ()
	{

	}

	///@brief Manage the phase of production for all player and one resource
	///@param toProduceResource Pointer which designate the type of resource currently to produce
	void Game::produceResource (Resource* toProduceResource)
	{


	}

	///@brief Send a resource earned by a player to let him use it
	///@param resource Pointer which designate the type of resource sent
	///@param player Pointer which designate the player who receive the resource
	void Game::sendResourceToPlayer (Resource* resource, Player* player) const
	{

	}

	///@brief Debug method to check the state of the instance of Game
	///@return String explaining the state of Game
	std::string Game::toString () const
	{
		return "";
	}

	/// @brief Distributes the empires to the players
	void initPlayers (std::vector<EmpireCard*> empires)
	{

	}

	/// @brief Ends the game, counts every player's victory points and compares them tp give a podium
	void endGame ()
	{
		return ;
	}
}