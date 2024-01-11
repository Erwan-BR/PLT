#include "Game.h"

#include <algorithm>
#include <random>
#include <fstream>
#include <random>
#include <chrono>

#include "../../constants/constants/GameConstants.h"
#include "../../constants/constants/GameObserversNotification.h"

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
                this->players.push_back(std::make_shared<Player>(playerJSON));
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
                this->deck.push_back(std::make_shared<DevelopmentCard>(developmentCardJSON));
            }
        }

        this->isClockwise = jsonValue["isClockwise"].asBool();
        this->isFaceA = jsonValue["isFaceA"].asBool();
        this->resourceProducing = static_cast<ResourceType> (jsonValue["resourceProducing"].asInt());
        this->isTestingGame = jsonValue["isTestingGame"].asBool();
    }

    ///@brief Create an instance of the class Game with players specified
    ///@param players Vector of pointers which designate the players of the game
    Game::Game(std::vector<std::shared_ptr<Player>> players) :
        Observable(),
        players(players)
    {
    }

    ///@brief Create an instance of the class Game with players specified. isTestingGame passed for the creation of a testing game.
    ///@param players Vector of pointers which designate the players of the game.
    /// @param isTestingGame Define if the game is created to be played or just for testing.
    Game::Game(std::vector<std::shared_ptr<Player>> players, bool isTestingGame) :
        Observable(),
        players(players),
        isTestingGame(isTestingGame)
    {
    }

    ///@brief Destructor of the Class Game
    Game::~Game ()
    {
    }

    ///@brief Initialize the game
    void Game::initGame ()
    {
        std::vector<std::shared_ptr<EmpireCard>> empires = this->initEmpire();
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
    void Game::initPlayers (std::vector<std::shared_ptr<EmpireCard>> empires)
    {
        // Checking if the number of players is inferior of the number of empires. We should always enter inside.
        if (this->players.size() <= empires.size())
        {
            int empireIndex = 0;
            for(std::shared_ptr<Player> player : this->players)
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
        this->deck = developmentCardCreation->createAllDevelopmentCards(this->isTestingGame);
    }
        
    ///@brief Create and Initialize the Empire for the game
    std::vector<std::shared_ptr<EmpireCard>> Game::initEmpire ()
    {
        CreateAllCards empireCardCreation;
        std::vector<std::shared_ptr<EmpireCard>> empires = empireCardCreation.createAllEmpireCards(isFaceA);

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
        this->notifyObservers(GAME_PHASE_CHANGED);
    }

    ///@brief Start one of the four turn of the game
    void Game::newTurn ()
    {
        this->turn ++;
        if ((2 == this->turn && this->isTestingGame) || (5 == this->turn && ! this->isTestingGame))
        {
            this->endGame();
            return ;
        }

        // Invert the sens for the draft phase
        this->isClockwise = ! this->isClockwise;

        this->notifyObservers(GAME_TURN_CHANGED | GAME_CLOCKWISE_CHANGED);
    }

    ///@brief Initialize the Draft part of the game during which players select their cards
    void Game::initDraft ()
    {
        for(std::shared_ptr<Player> player : this->players)
        {
            // Re-Initialise the cards that will be given to the players
            std::vector<std::shared_ptr<DevelopmentCard>> draftingDeck = {};

            for(int i = 0; NUMBER_OF_CARDS_DRAFTED > i; i++)
            {
                // Add a card to draft and delete it from the deck.
                draftingDeck.push_back(this->deck.back());
                this->deck.pop_back();
            }
            
            // Send cards to players.
            player->setDraftingCards(draftingDeck);
            player->setState(PlayerState::PLAYING);
        }
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
            std::vector<std::shared_ptr<DevelopmentCard>> firstPlayerDeck = this->players[0]->getDraftingCards();

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
            std::vector<std::shared_ptr<DevelopmentCard>> lastPlayerDeck = this->players[(this->players.size()-1)]->getDraftingCards();

            // Iterating among all players (except the first one) to make the draft.
            for (long unsigned int playerIndex = (this->players.size()-1); playerIndex > 0; playerIndex--)
            {
                this->players[playerIndex]->setDraftingCards(this->players[(playerIndex - 1)]->getDraftingCards());
            }

            // Giving the deck of the first player to the last one.
            this->players[0]->setDraftingCards(lastPlayerDeck);
        }
        
        for (std::shared_ptr<Player> player : this->players)
        {
            player->setState(PlayerState::PLAYING);
        }
    }

    ///@brief End the current Draft phase
    void Game::endDraft ()
    {
        this->nextPhase();
    }

    ///@brief Initialize the Planification phase during which players choose the cards they will try to build
    void Game::initPlanification ()
    {
        for (std::shared_ptr<Player> player : this->players)
        {
            player->setState(PlayerState::PLAYING);
        }
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
        
        for (std::shared_ptr<Player> player : this->players)
        {
            player->setState(PlayerState::PLAYING);
        }
        
        this->notifyObservers(GAME_RESOURCE_PRODUCING_CHANGED);
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
        for(std::shared_ptr<Player> player : this->players)
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
            bool chooseColonel = false;
            
            if (this->players[playerIndexBiggestProduction]->isAI())
            {
                chooseColonel = this->players[playerIndexBiggestProduction]->AIChooseColonelToken();
            }
            else
            {
                chooseColonel = this->players[playerIndexBiggestProduction]->isPreferedPersonnageColonel();
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
        this->notifyObservers(GAME_PHASE_CHANGED);
    }

    ///@brief Convert the Game to a JSON format. Usefull when the game is saved.
    ///@return Readable JSON of the game.
    Json::Value Game::toJSON () const
    {
        // Instanciation of the game into a JSON format.
        Json::Value gameJSON;

        // Serialize the vector of players
        Json::Value playersArray;
        for (const std::shared_ptr<Player>& player : this->players)
        {
            playersArray.append(player->toJSON());
        }
        gameJSON["players"] = playersArray;

        gameJSON["turn"] = this->turn;
        gameJSON["phase"] = static_cast<int> (this->phase);

        // Serialize the vector of drawable cards
        Json::Value cardsArray;
        for (const std::shared_ptr<DevelopmentCard>& card : this->deck)
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
    std::vector<std::shared_ptr<Player>> Game::getPlayers () const
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

    /// @brief Retrieve winners of the game. Called only when a game is finished
    /// @return A vector containing all indices of winners.
    std::vector<int> Game::getWinners () const
    {
        // Check if a game is finished.
        if(GamePhase::FINISHED != this->phase)
        {
            return {};
        }

        int maxNumberOfPoints = -1;
        std::vector<int> winners = {};
        
        // Iterating among all players.
        for (size_t playerIndex = 0; this->players.size() > playerIndex; playerIndex++)
        {
            int currentPlayerVictoryPoints = this->players[playerIndex]->computeVictoryPoint();

            // If the current player has most of all the previous one, he is the winner.
            if (maxNumberOfPoints < this->players[playerIndex]->computeVictoryPoint())
            {
                winners.clear();
                winners.push_back(playerIndex);
                maxNumberOfPoints = currentPlayerVictoryPoints;
            }
            else if (maxNumberOfPoints == currentPlayerVictoryPoints)
            {
                // There is already winners in the vector. We have to compare the victory condition.
                // 1. The player with the most built card win.
                // 2. If there is a tie on this number, the player with the most personnages win.
                if (this->players[playerIndex]->getBuiltCards().size() > this->players[winners[0]]->getBuiltCards().size())
                {
                    winners.clear();
                    winners.push_back(playerIndex);
                }
                else if (this->players[playerIndex]->getBuiltCards().size() == this->players[winners[0]]->getBuiltCards().size())
                {
                    int numberOfPersonnagesOfWinners = this->players[winners[0]]->getQuantityPersonnages();
                    int numberOfPersonnagesOfCurrentPlayer = this->players[playerIndex]->getQuantityPersonnages();
                    if (numberOfPersonnagesOfCurrentPlayer > numberOfPersonnagesOfWinners)
                    {
                        winners.clear();
                        winners.push_back(playerIndex);
                    }
                    else if (numberOfPersonnagesOfCurrentPlayer == numberOfPersonnagesOfWinners)
                    {
                        winners.push_back(playerIndex);
                    }
                }
            }
        }
        return winners;
    }
}