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
		return ;
	}

	///@brief Create and Initialize the Cards for the game
	void Game::initCards ()
	{
		return ;
	}

	/// @brief Import all Cards from the CSV file.
	void Game::importCardsFromCsv ()
	{
		return ;
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
		
    return(empires);
	}

	///@brief Start the game
	void Game::startGame ()
	{
		nextPhase();
	}

	///@brief Manage the progress of the game and start the next phase among Draft, Planification and Production
	void Game::nextPhase ()
	{
		return ;
	}

	///@brief Start one of the four turn of the game
	void Game::newTurn ()
	{
		return ;
	}

	///@brief Initialize the Draft part of the game during which players select their cards
	void Game::initDraft ()
	{
		std::vector<std::vector<DevelopmentCard*>> draftDeck;
		int i,j=0;

		for(Player* player : this->players)
		{
			// Initialise the cards that will be given to the players
			std::vector<DevelopmentCard*> draft;
			for(i=0;i<8;i++)
			{
				draft.push_back(deck.back());
				deck.pop_back();
			}
			draftDeck.push_back(draft);
			player->setDraftingCards(draftDeck[j]);
			j++;
		}
	}

	///@brief Start a Draft
	void Game::nextDraft ()
	{
		int n = draftDeck[0].size();
		int m = players.size(); 
		if(n == 0)
		{
			endDraft();
		}
		int i=0;
		for(Player* player : this->players)
		{
			if(this->isClockwise)
			{
				player->setDraftingCards(draftDeck[(i-(m-n))%m]);
				i++;
			}
			else
			{
				player->setDraftingCards(draftDeck[((m-n)-i)%m]);
				i++;
			}
			
		}
	}

	///@brief End the current Draft phase
	void Game::endDraft ()
	{
		return ;
	}

	///@brief Initialize the Planification phase during which players choose the cards they will try to build
	void Game::initPlanification ()
	{
		return;
	}

	///@brief Manage the phase of production for all player and one resource
	///@param toProduceResource Pointer which designate the type of resource currently to produce
	void Game::produceResource (ResourceType toProduceResource)
	{
		std::vector<int> playerProduction;
		for(Player* player : this->players)
			{
				playerProduction.push_back(player->computeProduction(toProduceResource));
			}
		return;
	}

	///@brief Send a resource earned by a player to let him use it
	///@param resource Pointer which designate the type of resource sent
	///@param player Pointer which designate the player who receive the resource
	void Game::sendResourceToPlayer (Resource* resource, Player* player) const
	{
			for(Player* player : this->players)
		{
			int i=0;
			//player->set playerProduction(i);
			i++;
		}
	}

	///@brief Debug method to check the state of the instance of Game
	///@return String explaining the state of Game
	std::string Game::toString () const
	{
		return "";
	}

	/// @brief Distributes the empires to the players
	void Game::initPlayers (std::vector<EmpireCard*> empires)
	{
		for(Player* player : this->players)
		{
			// Initialise the cards that will be given to the players
			int i = 0;
			player->setEmpire(empires[i]);
			i++;
		}
		return;
	}

	/// @brief Ends the game, counts every player's victory points and compares them to give a podium
	void Game::endGame ()
	{
		std::vector<int> points;
		for(Player* player : this->players)
		{
			points.push_back(player->computeVictoryPoint());
		}
	}
}