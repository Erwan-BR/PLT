#include "Game.h"
#include <algorithm>
#include <random>
#include <fstream>

namespace state {
	///@brief Create an instance of the class Game
	Game::Game() :
		Observable(),
		players()
	{
	}

	///@brief Create an instance of the class Game with players specified
	///@param players Vector of pointers which designate the players of the game
	Game::Game(std::vector<Player*> players) :
		Observable(),
		players(players)
	{
	}

	///@brief Destructor of the Class Game
	Game::~Game ()
	{
		// Delete all cards from the deck.
		for (DevelopmentCard* card : this->deck)
		{
			delete card;
		}
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
		this->createCards();
		auto rng = std::default_random_engine {};
		std::shuffle(std::begin(deck), std::end(deck), rng);
	}

	/// @brief Create all cards of the game and add them to the deck.
	void Game::createCards()
	{
		for(int i = 0;i<14;i++)
		{
			DevelopmentCard* createdCard = new DevelopmentCard();
			this->deck.push_back(createdCard);
		}
		return;

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

		this->notifyObservers();
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

		this->notifyObservers();
	}

	///@brief Initialize the Draft part of the game during which players select their cards
	void Game::initDraft ()
	{
		// Deck of cards to send to a player.
		std::vector<DevelopmentCard*> draftingDeck;

		for(Player* player : this->players)
		{
			// Re-Initialise the cards that will be given to the players
			draftingDeck = {};

			for(int i = 0; i < 7; i++)
			{
				// Add a card to draft and delete it from the deck.
				draftingDeck.push_back(this->deck.back());
				this->deck.pop_back();
			}
			
			// Send cards to players.
			player->setDraftingCards(draftingDeck);
		}
		this->notifyObservers();
	}

	///@brief Launch the next draft.
	void Game::nextDraft ()
	{
		int n = (int) (this->draftDeck[0]).size();

		if(n == 0)
		{
			endDraft();
		}
		int i = 0;
		int m = players.size(); 
		for(Player* player : this->players)
		{
			if(this->isClockwise)
			{
				player->setDraftingCards(this->draftDeck[(i-(m-n))%m]);
				i++;
			}
			else
			{
				player->setDraftingCards(this->draftDeck[((m-n)-i)%m]);
				i++;
			}
		}

		this->notifyObservers();
	}

	///@brief End the current Draft phase
	void Game::endDraft ()
	{
		nextPhase();
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
		int playerProduction;

		// Two integers to find the players that win the most of a resources to give him a bonus.
		int playerIndexBiggestProduction = -1;
		int biggestProduction = -1;
		bool multipleBiggestProduction = false;

		int index = 0;

		// Iterating among all players.
		for(Player* player : this->players)
		{
			playerProduction = player->getProductionGain(toProduceResource);

			player->receiveResources(toProduceResource, playerProduction);

			if (playerProduction > biggestProduction)
			{
				// Updating who won the most of the current produced ressource.
				playerIndexBiggestProduction = index;
				biggestProduction = playerProduction;
				multipleBiggestProduction = false;
			}
			else if (playerProduction > biggestProduction)
			{
				playerIndexBiggestProduction = -1;
				multipleBiggestProduction = true;
			}
			index++;
		}

		// Checking who won's the most of this resources for the bonus.
		if (!multipleBiggestProduction)
		{
			// Send the financier token
			if (ResourceType::MATERIAL == toProduceResource || ResourceType::GOLD == toProduceResource)
			{
				this->players[playerIndexBiggestProduction]->receiveResource(ResourceType::FINANCIER);
			}
			// Send the colonel token
			else if (ResourceType::ENERGY == toProduceResource || ResourceType::EXPLORATION == toProduceResource)
			{
				this->players[playerIndexBiggestProduction]->receiveResource(ResourceType::COLONEL);
			}
			// Send the token choosen by the player
			else
			{
				// Retrieve which token the player wants to get.
				bool chooseColonel = this->players[playerIndexBiggestProduction]->chooseColonelToken();

				if (chooseColonel)
				{
					this->players[playerIndexBiggestProduction]->receiveResource(ResourceType::COLONEL);
				}
				else
				{
					this->players[playerIndexBiggestProduction]->receiveResource(ResourceType::FINANCIER);
				}
			}
		}
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

	///@brief Debug method to check the state of the instance of Game
	///@return String explaining the state of Game
	std::string Game::toString () const
	{
		return "";
	}

    /************************************* Setters & Getters *************************************/

	/// @brief Get Players in the game.
	/// @return All players inside the game.
	std::vector<Player*> Game::getPlayers () const
	{
		return this->players;
	}

    /// @brief Get the number of the turn (1 to 4)
    /// @return Number of the turn.
    int Game::getTurn () const
	{
		return this->turn;
	}

    /// @brief Get the phase of the game (planificiation, production, draft)
    /// @return Current phase of the game.
    GamePhase Game::getPhase () const
	{
		return this->phase;
	}
}