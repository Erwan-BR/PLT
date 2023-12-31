#include "Game.h"
#include <algorithm>
#include <random>
#include <fstream>
#include <random>
#include <chrono>

namespace state {
    ///@brief Create a game from a json file.
    Game::Game(Json::Value jsonValue) :
        Observable()
    {
        // Retrieve Players from the JSON.
        this->players = {};
        if (jsonValue["players"].isArray())
        {
            const Json::Value playersArray = jsonValue["players"];
        
            for (const Json::Value& playerJSON : playersArray)
            {
                this->players.push_back(new Player(playerJSON));
            }
        }

        this->turn = jsonValue["turn"].asInt();
        this->phase = static_cast<GamePhase> (jsonValue["phase"].asInt());

        // Retrieve drawable cards from the JSON.
        this->deck = {};
        if (jsonValue["deck"].isArray())
        {
            const Json::Value deckArray = jsonValue["deck"];
        
            for (const Json::Value& developmentCardJSON : deckArray)
            {
                this->deck.push_back(new DevelopmentCard(developmentCardJSON));
            }
        }

        this->isClockwise = jsonValue["isClockwise"].asBool();
        this->isFaceA = jsonValue["isFaceA"].asBool();
        this->resourceProducing = static_cast<ResourceType> (jsonValue["resourceProducing"].asInt());
        this->isTestingGame = jsonValue["isTestingGame"].asBool();
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

    ///@brief Create an instance of the class Game with players specified. isTestingGame passed for the creation of a testing game.
    ///@param players Vector of pointers which designate the players of the game.
    /// @param isTestingGame Define if the game is created to be played or just for testing.
    Game::Game(std::vector<Player*> players, bool isTestingGame) :
        Observable(),
        players(players),
        isTestingGame(isTestingGame)
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

        // Shuffle the cards only if the game is not for testing purpose.
        if (! this->isTestingGame)
        {
            // Time-base seed to shuffle cards.
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine randomness(seed);
            std::shuffle(this->deck.begin(), this->deck.end(), randomness);
        }
    }

    /// @brief Distributes the empires to the players
    void Game::initPlayers (std::vector<EmpireCard*> empires)
    {
        // Checking if the number of players is inferior of the number of empires. We should always enter inside.
        if (this->players.size() <= empires.size())
        {
            int empireIndex = 0;
            for(Player* player : this->players)
            {
                // Initialise the empires that will be given to the players
                player->setEmpire(empires[empireIndex]);
                empireIndex++;
            }
        }
    }

    /// @brief Create all cards of the game and add them to the deck.
    void Game::createCards()
    {
        CreateAllCards* developmentCardCreation = new CreateAllCards;
        this->deck = developmentCardCreation->createAllDevelopmentCards();
    }
        
    ///@brief Create and Initialize the Empire for the game
    std::vector<EmpireCard*> Game::initEmpire ()
    {
        CreateAllCards empireCardCreation;
        std::vector<EmpireCard*> empires = empireCardCreation.createAllEmpireCards(isFaceA);

        // Shuffle if not a testing game.
        if (! this->isTestingGame)
        {
            // Time-base seed to shuffle cards.
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine randomness(seed);
            std::shuffle(empires.begin(), empires.end(), randomness);
        }

        return empires;
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
            if (GamePhase::FINISHED != this->phase)
            {
                this->phase = GamePhase::DRAFT;
                this->initDraft();
            }
        }
        this->notifyObservers();
    }

    ///@brief Start one of the four turn of the game
    void Game::newTurn ()
    {
        this->turn = this->turn + 1;
        if ((2 == this->turn && this->isTestingGame) || (5 == this->turn && ! this->isTestingGame))
        {
            this->endGame();
            return ;
        }

        // Invert the sens for the draft phase
        this->isClockwise = ! this->isClockwise;

        this->notifyObservers();
    }

    ///@brief Initialize the Draft part of the game during which players select their cards
    void Game::initDraft ()
    {
        for(Player* player : this->players)
        {
            // Re-Initialise the cards that will be given to the players
            std::vector<DevelopmentCard*> draftingDeck = {};

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
        return ;
    }

    /// @brief End the planification phase to start the next phase.
    void Game::endPlanification ()
    {
        this->nextPhase();
    }

    /// @brief Init the production phase.
    void Game::initProduction ()
    {
        this->resourceProducing = ResourceType::FINANCIER;
        this->notifyObservers();
        this->nextProduction();
    }

    /// @brief Launch the next production phase if a production phase arrives, launch the next draft phase if not.
    void Game::nextProduction ()
    {
        // Financier = Init; krystallium = ended.
        const static std::vector<ResourceType> tableOfResources = {ResourceType::FINANCIER, ResourceType::MATERIAL, ResourceType::ENERGY, ResourceType::SCIENCE, ResourceType::GOLD, ResourceType::EXPLORATION, ResourceType::KRYSTALLIUM};

        auto indexOfResource = std::find(tableOfResources.begin(), tableOfResources.end(), this->resourceProducing);
        this->resourceProducing = *(indexOfResource + 1);

        // Resource producing is 'Kystallium'. It means that there is no more resource to produce.
        if (ResourceType::KRYSTALLIUM == this->resourceProducing)
        {
            this->endProduction();
            return;
        }

        this->produceResource();
        this->notifyObservers();
    }

    ///@brief Manage the phase of production for all player and one resource
    void Game::produceResource ()
    {
        // Two integers to find the players that win the most of a resources to give him a bonus.
        int playerIndexBiggestProduction = -1;
        int biggestProduction = -1;
        
        bool multipleBiggestProduction = false;

        // Current index of the loop - to update the player with the biggest production
        int index = 0;

        // Iterating among all players.
        for(Player* player : this->players)
        {
            int playerProduction = player->getProductionGain(this->resourceProducing);

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
            this->sendTokenToMostProducer(playerIndexBiggestProduction);
        }
    }

    /// @brief Function called by produceResource if only one player produce the most of the current resources. Send the corresponding token.
    /// @param playerIndexBiggestProduction Index of the player (unique) that produces the most of the current resources.
    void Game::sendTokenToMostProducer (int playerIndexBiggestProduction)
    {
        // Send the financier token
        if (ResourceType::MATERIAL == this->resourceProducing || ResourceType::GOLD == this->resourceProducing)
        {
            this->players[playerIndexBiggestProduction]->receiveResources(ResourceType::FINANCIER, 1);
        }
        // Send the colonel token
        else if (ResourceType::ENERGY == this->resourceProducing || ResourceType::EXPLORATION == this->resourceProducing)
        {
            this->players[playerIndexBiggestProduction]->receiveResources(ResourceType::COLONEL, 1);
        }
        // Send the token choosen by the player
        else
        {
            // Retrieve which token the player wants to get, the player can also be an AI.
            bool chooseColonel ;
            
            if (this->players[playerIndexBiggestProduction]->isAI())
            {
                chooseColonel = this->players[playerIndexBiggestProduction]->AIChooseColonelToken();
            }
            else
            {
                chooseColonel = this->players[playerIndexBiggestProduction]->chooseColonelToken();
            }

            if (chooseColonel)
            {
                this->players[playerIndexBiggestProduction]->receiveResources(ResourceType::COLONEL, 1);
            }
            else
            {
                this->players[playerIndexBiggestProduction]->receiveResources(ResourceType::FINANCIER, 1);
            }
        }
    }

    /// @brief End the production phase.
    void Game::endProduction ()
    {
        this->nextPhase();
    }

    /// @brief Ends the game.
    void Game::endGame ()
    {
        this->phase = GamePhase::FINISHED;
        this->notifyObservers();
    }

    ///@brief Convert the Game to a JSON format. Usefull when the game is saved.
    ///@return Readable JSON of the game.
    Json::Value Game::toJSON () const
    {
        // Instanciation of the game into a JSON format.
        Json::Value gameJSON;

        // Serialize the vector of players
        Json::Value playersArray;
        for (const Player* player : this->players)
        {
            playersArray.append(player->toJSON());
        }
        gameJSON["players"] = playersArray;

        gameJSON["turn"] = this->turn;
        gameJSON["phase"] = static_cast<int> (this->phase);

        // Serialize the vector of drawable cards
        Json::Value cardsArray;
        for (const DevelopmentCard* card : this->deck)
        {
            cardsArray.append(card->toJSON());
        }
        gameJSON["deck"] = cardsArray;

        gameJSON["isClockwise"] = this->isClockwise;
        gameJSON["isFaceA"] = this->isFaceA;
        gameJSON["resourceProducing"] = static_cast<int> (this->resourceProducing);
        gameJSON["isTestingGame"] = this->isTestingGame;


        return gameJSON;
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