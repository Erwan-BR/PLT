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
		// Delete all cards from the deck.
		for (DevelopmentCard* card : this->deck)
		{
			delete card;
		}
	}

	///@brief Initialize the game
	void Game::initGame ()
	{
		std::vector<EmpireCard*> empires = this->initEmpire();
		this->initCards();
		this->initPlayers(empires);
		this->startGame();
	}

	///@brief Create and Initialize the Cards for the game
	void Game::initCards ()
	{
		this->createCards();
		auto rng = std::default_random_engine {};
		std::shuffle(std::begin(deck), std::end(deck), rng);
	}

	/// @brief Distributes the empires to the players
	void Game::initPlayers (std::vector<EmpireCard*> empires)
	{
		// Checking if the number of players is inferior of the number of empires. We should always enter inside.
		if (this->players.size() <= empires.size())
		{
			for(Player* player : this->players)
			{
				// Initialise the empires that will be given to the players
				int empireIndex = 0;
				player->setEmpire(empires[empireIndex]);
				empireIndex++;
			}
		}
	}

	/// @brief Create all cards of the game and add them to the deck.
	void Game::createCards()
	{
		// To-Do : modify once cards are correctly scanned.
		for(int i = 0; i < 150; i++)
		{
			DevelopmentCard* createdCard = new DevelopmentCard();
			this->deck.push_back(createdCard);
		}
	}

	///@brief Create and Initialize the Empire for the game
	std::vector<EmpireCard*> Game::initEmpire ()
	{	
		// face B
		ResourceToProduce* firstResourceToProduce = new ResourceToProduce{ResourceType::MATERIAL, 2, state::CardType::NONETYPE};
    	ResourceToProduce* secondResourceToProduce = new ResourceToProduce{ResourceType::ENERGY, 1, state::CardType::NONETYPE};
    	ResourceToProduce* thirdResourceToProduce = new ResourceToProduce{ResourceType::SCIENCE, 1, state::CardType::NONETYPE};
		std::vector<ResourceToProduce*> productionGainB = {firstResourceToProduce,secondResourceToProduce,thirdResourceToProduce};		

		// empire AFRICA
		ResourceToProduce* firstResourceToProduceAFRICA = new ResourceToProduce{ResourceType::MATERIAL, 2, state::CardType::NONETYPE};
    	ResourceToProduce* secondResourceToProduceAFRICA = new ResourceToProduce{ResourceType::SCIENCE, 2, state::CardType::NONETYPE};
		std::vector<ResourceToProduce*> productionGainAFRICA = {firstResourceToProduceAFRICA,secondResourceToProduceAFRICA};
		sf::Texture designAFRICA;
   		CardVictoryPoint* victoryPointsAFRICA  = new CardVictoryPoint{2,state::CardType::RESEARCH};
		EmpireCard* africa = new EmpireCard("AFRICA", productionGainAFRICA, designAFRICA, victoryPointsAFRICA, productionGainB, {0}, AFRICA);
	
		// empire NORAM
		ResourceToProduce* firstResourceToProduceNORAM = new ResourceToProduce{ResourceType::MATERIAL, 3, state::CardType::NONETYPE};
    	ResourceToProduce* secondResourceToProduceNORAM = new ResourceToProduce{ResourceType::GOLD, 1, state::CardType::NONETYPE};
		std::vector<ResourceToProduce*> productionGainNORAM = {firstResourceToProduceNORAM,secondResourceToProduceNORAM};
		sf::Texture designNORAM;
   		CardVictoryPoint* victoryPointsNORAM  = new CardVictoryPoint{1,state::ResourceType::FINANCIER};
		EmpireCard* noram = new EmpireCard("NORAM", productionGainNORAM, designNORAM, victoryPointsNORAM, productionGainB, {0}, NORAM);
		
		// empire ASIA
		ResourceToProduce* firstResourceToProduceASIA = new ResourceToProduce{ResourceType::MATERIAL, 1, state::CardType::NONETYPE};
    	ResourceToProduce* secondResourceToProduceASIA = new ResourceToProduce{ResourceType::GOLD, 2, state::CardType::NONETYPE};
		std::vector<ResourceToProduce*> productionGainASIA = {firstResourceToProduceASIA,secondResourceToProduceASIA};
		sf::Texture designASIA;
   		CardVictoryPoint* victoryPointsASIA  = new CardVictoryPoint{2,state::CardType::PROJECT};
		EmpireCard* asia = new EmpireCard("ASIA", productionGainASIA, designASIA, victoryPointsASIA, productionGainB, {0}, ASIA);
		
		// empire EUROPE
		ResourceToProduce* firstResourceToProduceEUROPE = new ResourceToProduce{ResourceType::MATERIAL, 2, state::CardType::NONETYPE};
    	ResourceToProduce* secondResourceToProduceEUROPE = new ResourceToProduce{ResourceType::ENERGY, 1, state::CardType::NONETYPE};
    	ResourceToProduce* thirdResourceToProduceEUROPE = new ResourceToProduce{ResourceType::SCIENCE, 1, state::CardType::NONETYPE};
		std::vector<ResourceToProduce*> productionGainEUROPE = {firstResourceToProduceEUROPE,secondResourceToProduceEUROPE,thirdResourceToProduceEUROPE};
		sf::Texture designEUROPE;
   		CardVictoryPoint* victoryPointsEUROPE  = new CardVictoryPoint{1,state::ResourceType::COLONEL};
		EmpireCard* europe = new EmpireCard("EUROPE", productionGainEUROPE, designEUROPE, victoryPointsEUROPE, productionGainB, {0}, EUROPE);
		
		// empire AZTEC
		ResourceToProduce* firstResourceToProduceAZTEC = new ResourceToProduce{ResourceType::ENERGY, 2, state::CardType::NONETYPE};
    	ResourceToProduce* secondResourceToProduceAZTEC = new ResourceToProduce{ResourceType::EXPLORATION, 1, state::CardType::NONETYPE};
		std::vector<ResourceToProduce*> productionGainAZTEC = {firstResourceToProduceAZTEC,secondResourceToProduceAZTEC};
		sf::Texture designAZTEC;
   		CardVictoryPoint* victoryPointsAZTEC  = new CardVictoryPoint{3,state::CardType::DISCOVERY};
		EmpireCard* aztec = new EmpireCard("AZTEC", productionGainAZTEC, designAZTEC, victoryPointsAZTEC, productionGainB, {0}, AZTEC);

		std::vector<EmpireCard*> empires = {africa,noram,asia,europe,aztec};
		auto rng = std::default_random_engine {};
		std::shuffle(std::begin(empires), std::end(empires), rng);
		
    return(empires);
	}

	///@brief Start the game
	void Game::startGame ()
	{
		this->nextPhase();
	}

	///@brief Manage the progress of the game and start the next phase among Draft, Planification and Production
	void Game::nextPhase ()
	{
		if(GamePhase::DRAFT == this->phase)
		{
			this->phase = GamePhase::PLANIFICATION;
			this->initPlanification();
		}
		else if(GamePhase::PLANIFICATION == this->phase)
		{
			this->phase = GamePhase::PRODUCTION;
			this->initProduction();
		}
		else if(GamePhase::PRODUCTION == this->phase)
		{
			this->newTurn();
			this->phase = GamePhase::DRAFT;
			this->initDraft();
		}
		this->notifyObservers();
	}

	///@brief Start one of the four turn of the game
	void Game::newTurn ()
	{
		this->turn= (this->turn + 1);
		if(1 == this->turn)
		{
			this->endGame();
		}

		// Invert the sens for the draft phase
		this->isClockwise = ! this->isClockwise;

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
		this->nextDraft ();
	}

	///@brief Launch the next draft.
	void Game::nextDraft ()
	{
		// Retrieve the number of cards to draft.
		int numberOfCardsToDraft = this->players[0]->getDraftingCards().size();

		// If there is no cards left, we can continue to play.
		if(0 == numberOfCardsToDraft)
		{
			this->endDraft();
		}

		// According of how we are turning cards, behaviour are differents.
		if (this->isClockwise)
		{
			// Memorize the first player deck to give it to the last player.
			std::vector<DevelopmentCard*> firstPlayerDeck = this->players[0]->getDraftingCards();

			// Iterating among all players (except the last one) to make the draft.
			for (long unsigned int playerIndex = 0; playerIndex < this->players.size() - 1; playerIndex++)
			{
				this->players[playerIndex]->setDraftingCards(this->players[(playerIndex + 1)]->getDraftingCards());
			}

			// Giving the deck of the first player to the last one.
			this->players[this->players.size()-1]->setDraftingCards(firstPlayerDeck);
		}
		else
		{
			// Memorize the last player deck to give it to the first player.
			std::vector<DevelopmentCard*> lastPlayerDeck = this->players[(this->players.size()-1)]->getDraftingCards();

			// Iterating among all players (except the first one) to make the draft.
			for (long unsigned int playerIndex = (this->players.size()-1); playerIndex > 0; playerIndex--)
			{
				this->players[playerIndex]->setDraftingCards(this->players[(playerIndex - 1)]->getDraftingCards());
			}

			// Giving the deck of the first player to the last one.
			this->players[0]->setDraftingCards(lastPlayerDeck);
		}

		// Notify observers that the draft is done.
		this->notifyObservers();
	}

	///@brief End the current Draft phase
	void Game::endDraft ()
	{
		this->nextPhase();
	}

	///@brief Initialize the Planification phase during which players choose the cards they will try to build
	void Game::initPlanification ()
	{
		//to do
		this->endPlanification();
	}

	/// @brief End the planification phase to start the next phase.
	void Game::endPlanification ()
	{
		this->nextPhase();
	}

	/// @brief Init the production phase.
	void Game::initProduction ()
	{
		this->resourceProducing = ResourceType::MATERIAL;
		this->notifyObservers();
		this->nextProduction();
	}

	/// @brief Launch the next production phase if a production phase arrives, launch the next draft phase if not.
	void Game::nextProduction ()
	{
		if (ResourceType::MATERIAL == this->resourceProducing)
		{
			this->produceResource();
			this->resourceProducing = ResourceType::ENERGY;
			this->notifyObservers();
			this->nextProduction ();
		}
		else if (ResourceType::ENERGY == this->resourceProducing)
		{
			this->produceResource();
			this->resourceProducing = ResourceType::SCIENCE;
			this->notifyObservers();
			this->nextProduction ();
		}
		else if (ResourceType::SCIENCE == this->resourceProducing)
		{
			this->produceResource();
			this->resourceProducing = ResourceType::GOLD;
			this->notifyObservers();
			this->nextProduction ();
		}
		else if (ResourceType::GOLD == this->resourceProducing)
		{
			this->produceResource();
			this->resourceProducing = ResourceType::EXPLORATION;
			this->notifyObservers();
			this->nextProduction ();
		}
		else
		{
			this->produceResource();
			this->resourceProducing = ResourceType::KRYSTALLIUM;
			this->notifyObservers();
			this->endProduction();
		}
	}

	///@brief Manage the phase of production for all player and one resource
	void Game::produceResource ()
	{
		// Production of the player in the following loop.
		int playerProduction;

		// Two integers to find the players that win the most of a resources to give him a bonus.
		int playerIndexBiggestProduction = -1;
		int biggestProduction = -1;
		
		bool multipleBiggestProduction = false;

		// Current index of the loop - to update the plkayer with the biggest production
		int index = 0;

		// Iterating among all players.
		for(Player* player : this->players)
		{
			playerProduction = player->getProductionGain(this->resourceProducing);

			player->receiveResources(this->resourceProducing, playerProduction);

			if (playerProduction > biggestProduction)
			{
				// Updating who won the most of the current produced ressource.
				playerIndexBiggestProduction = index;
				biggestProduction = playerProduction;
				multipleBiggestProduction = false;
			}
			else if (playerProduction == biggestProduction)
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
			if (ResourceType::MATERIAL == this->resourceProducing || ResourceType::GOLD == this->resourceProducing)
			{
				this->players[playerIndexBiggestProduction]->receiveResources(ResourceType::FINANCIER,1);
			}
			// Send the colonel token
			else if (ResourceType::ENERGY == this->resourceProducing || ResourceType::EXPLORATION == this->resourceProducing)
			{
				this->players[playerIndexBiggestProduction]->receiveResources(ResourceType::COLONEL,1);
			}
			// Send the token choosen by the player
			else
			{
				// Retrieve which token the player wants to get.
				bool chooseColonel = this->players[playerIndexBiggestProduction]->chooseColonelToken();

				if (chooseColonel)
				{
					//this->players[playerIndexBiggestProduction]->receiveResources(ResourceType::COLONEL,1);
				}
				else
				{
					this->players[playerIndexBiggestProduction]->receiveResources(ResourceType::FINANCIER,1);
				}
			}
		}
	}

	/// @brief End the production phase.
	void Game::endProduction ()
	{
		this->nextPhase();
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

	/// @brief Allows to get the resource that is produced. Returns Krystallium if production is finished.
	/// @return Resource produced / Next one to be produced according to the moment.
	ResourceType Game::getResourceProducing () const
	{
		return this->resourceProducing;
	}
}