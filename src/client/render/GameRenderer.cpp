#include "GameRenderer.h"

#include "constants/GameObserversNotification.h"
#include "constants/GameConstants.h"

namespace render
{
    /// @brief Full constructor of GameRenderer
    /// @param game Game to render
    /// @param position Position of the view in the window.
    GameRenderer::GameRenderer (std::shared_ptr<state::Game> game, sf::Vector2f position) :
        game(game),
        boardMaterialTexture(constants::ResourceManager::getTexture("./resources/img/board_material.png")),
        boardEnergyTexture(constants::ResourceManager::getTexture("./resources/img/board_energy.png")),
        boardScienceTexture(constants::ResourceManager::getTexture("./resources/img/board_science.png")),
        boardGoldTexture(constants::ResourceManager::getTexture("./resources/img/board_gold.png")),
        boardExplorationTexture(constants::ResourceManager::getTexture("./resources/img/board_exploration.png")),
        boardTurnTexture(constants::ResourceManager::getTexture("./resources/img/turn_1.png"))
    {
        //Create the Font
        this->font = sf::Font();
        this->font.loadFromFile("./resources/font/arial.ttf");

        //Generate the Board Part for MATERIAL
		this->boardMaterialSprite.setTexture(this->boardMaterialTexture);
        this->boardMaterialSprite.setPosition(position+sf::Vector2f({400.f,500.f}));
        this->boardMaterialSprite.setScale({0.2f,0.2f});

        //Generate the Board Part for ENERGY
		this->boardEnergySprite.setTexture(this->boardEnergyTexture);
        this->boardEnergySprite.setPosition(position+sf::Vector2f({620.f,500.f}));
        this->boardEnergySprite.setScale({0.2f,0.2f});

        //Generate the Board Part for Science
		this->boardScienceSprite.setTexture(this->boardScienceTexture);
        this->boardScienceSprite.setPosition(position+sf::Vector2f({840.f,500.f}));
        this->boardScienceSprite.setScale({0.2f,0.2f});
        
        //Generate the Board Part for GOLD
		this->boardGoldSprite.setTexture(this->boardGoldTexture);
        this->boardGoldSprite.setPosition(position+sf::Vector2f({1060.f,500.f}));
        this->boardGoldSprite.setScale({0.2f,0.2f});

        //Generate the Board Part for EXPLORATION
		this->boardExplorationSprite.setTexture(this->boardExplorationTexture);
        this->boardExplorationSprite.setPosition(position+sf::Vector2f({1280.f,500.f}));
        this->boardExplorationSprite.setScale({0.2f,0.2f});

        //Generate the Turn Token
		this->boardTurnSprite.setTexture(this->boardTurnTexture);
        this->boardTurnSprite.setPosition(position+sf::Vector2f({900.f,400.f}));
        this->boardTurnSprite.setScale({0.2f,0.2f});

        //Generate the text for Phase
        this->phaseIndicator = new sf::Text();
        this->phaseIndicator->setFont(font);
        this->phaseIndicator->setCharacterSize(30);
        this->phaseIndicator->setFillColor(this->colorActiveResource);
        this->phaseIndicator->setPosition(position+sf::Vector2f({1000.f,400.f}));
    }

    /// @brief Destructor of the game renderer.
    GameRenderer::~GameRenderer ()
    {

    }

    /// @brief Update the GameRenderer with the current state of the game
    /// @param flags Flags that indicate what have changed in the render.
    void GameRenderer::update (long flags)
    {
        if(GAME_TURN_CHANGED & flags)
        {
            //Update the turn token
            int turn = this->game->getTurn();
            if (NUMBER_OF_TURN + 1 > turn)
            {
                this->boardTurnTexture = constants::ResourceManager::getTexture("./resources/img/turn_" + std::to_string(turn) + ".png");
                this->boardTurnSprite.setTexture(this->boardTurnTexture);
            }
        }
        
        if((GAME_PHASE_CHANGED & flags) || (GAME_RESOURCE_PRODUCING_CHANGED & flags))
        {
            //Reset the Board of Resources
            this->boardMaterialSprite.setColor(this->colorActiveResource);
            this->boardEnergySprite.setColor(this->colorActiveResource);
            this->boardScienceSprite.setColor(this->colorActiveResource);
            this->boardGoldSprite.setColor(this->colorActiveResource);
            this->boardExplorationSprite.setColor(this->colorActiveResource);

            switch (this->game->getPhase()){
                case state::DRAFT:
                    //Set the phase text during DRAFT
                    this->phaseIndicator->setString("DRAFT");
                    break;
                case state::PLANIFICATION:
                    //Set the phase text during PLANIFICATION
                    this->phaseIndicator->setString("PLANIFICATION");
                    break;
                case state::PRODUCTION:
                    //Set the phase text during PRODUCTION
                    this->phaseIndicator->setString("PRODUCTION");
                    
                    //Make the Board of Resources darker
                    this->boardMaterialSprite.setColor(this->colorUnactiveResource);
                    this->boardEnergySprite.setColor(this->colorUnactiveResource);
                    this->boardScienceSprite.setColor(this->colorUnactiveResource);
                    this->boardGoldSprite.setColor(this->colorUnactiveResource);
                    this->boardExplorationSprite.setColor(this->colorUnactiveResource);

                    // Only ligth up the board of the currently produced resource
                    switch (this->game->getResourceProducing())
                    {
                        case state::MATERIAL:
                            this->boardMaterialSprite.setColor(this->colorActiveResource);
                            break;
                        case state::ENERGY:
                            this->boardEnergySprite.setColor(this->colorActiveResource);
                            break;
                        case state::SCIENCE:
                            this->boardScienceSprite.setColor(this->colorActiveResource);
                            break;
                        case state::GOLD:
                            this->boardGoldSprite.setColor(this->colorActiveResource);
                            break;
                        case state::EXPLORATION:
                            this->boardExplorationSprite.setColor(this->colorActiveResource);
                            break;
                        default:
                            break;
                    }
                    break;
                case state::FINISHED:
                    //Set the phase text when game is ended
                    this->phaseIndicator->setString("FINISHED!");
                    break;
            }
        }
    }

    /// @brief Draw the different elements of the game on the given window.
    /// @param window Window where the game is displayed.
    void GameRenderer::draw(sf::RenderWindow& window)
    {
        window.draw(this->boardMaterialSprite);
        window.draw(this->boardEnergySprite);
        window.draw(this->boardScienceSprite);
        window.draw(this->boardGoldSprite);
        window.draw(this->boardExplorationSprite);
        window.draw(this->boardTurnSprite);
        window.draw(*this->phaseIndicator);
    }
}