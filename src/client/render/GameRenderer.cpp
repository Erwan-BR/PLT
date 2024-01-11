#include "GameRenderer.h"

#include "../../constants/constants/GameObserversNotification.h"

namespace render
{
    /// @brief  Full constructor of GameRenderer
    /// @param game Game to render
    /// @param transform Transformation to do to display it
    GameRenderer::GameRenderer (std::shared_ptr<state::Game> game, sf::Vector2f position)
    {
        //Store the Game Attribute
        this->game = game;

        //Create the Font
        this->font = sf::Font();
        this->font.loadFromFile("./resources/font/arial.ttf");

        //Generate the Board Part for MATERIAL
        this->boardMaterialTexture = new sf::Texture();
		this->boardMaterialTexture->loadFromFile("./resources/img/board_material.png");
		this->boardMaterialSprite = new sf::Sprite();
		this->boardMaterialSprite->setTexture(*(this->boardMaterialTexture));
        this->boardMaterialSprite->setPosition(position+sf::Vector2f({400.f,500.f}));
        this->boardMaterialSprite->setScale({0.2f,0.2f});

        //Generate the Board Part for ENERGY
        this->boardEnergyTexture = new sf::Texture();
		this->boardEnergyTexture->loadFromFile("./resources/img/board_energy.png");
		this->boardEnergySprite = new sf::Sprite();
		this->boardEnergySprite->setTexture(*(this->boardEnergyTexture));
        this->boardEnergySprite->setPosition(position+sf::Vector2f({620.f,500.f}));
        this->boardEnergySprite->setScale({0.2f,0.2f});
        
        //Generate the Board Part for GOLD
        this->boardGoldTexture = new sf::Texture();
		this->boardGoldTexture->loadFromFile("./resources/img/board_gold.png");
		this->boardGoldSprite = new sf::Sprite();
		this->boardGoldSprite->setTexture(*(this->boardGoldTexture));
        this->boardGoldSprite->setPosition(position+sf::Vector2f({1060.f,500.f}));
        this->boardGoldSprite->setScale({0.2f,0.2f});

        //Generate the Board Part for Science
        this->boardScienceTexture = new sf::Texture();
		this->boardScienceTexture->loadFromFile("./resources/img/board_science.png");
		this->boardScienceSprite = new sf::Sprite();
		this->boardScienceSprite->setTexture(*(this->boardScienceTexture));
        this->boardScienceSprite->setPosition(position+sf::Vector2f({840.f,500.f}));
        this->boardScienceSprite->setScale({0.2f,0.2f});

        //Generate the Board Part for EXPLORATION
        this->boardExplorationTexture = new sf::Texture();
		this->boardExplorationTexture->loadFromFile("./resources/img/board_exploration.png");
		this->boardExplorationSprite = new sf::Sprite();
		this->boardExplorationSprite->setTexture(*(this->boardExplorationTexture));
        this->boardExplorationSprite->setPosition(position+sf::Vector2f({1280.f,500.f}));
        this->boardExplorationSprite->setScale({0.2f,0.2f});

        //Generate the Turn Token
        this->boardTurnTexture = new sf::Texture();
		this->boardTurnTexture->loadFromFile("./resources/img/turn_1.png");
		this->boardTurnSprite = new sf::Sprite();
		this->boardTurnSprite->setTexture(*(this->boardTurnTexture));
        this->boardTurnSprite->setPosition(position+sf::Vector2f({900.f,400.f}));
        this->boardTurnSprite->setScale({0.2f,0.2f});

        //Generate the text for Phase
        this->phaseIndicator = new sf::Text();
        this->phaseIndicator->setFont(font);
        this->phaseIndicator->setCharacterSize(30);
        this->phaseIndicator->setFillColor(sf::Color::White);
        this->phaseIndicator->setPosition(position+sf::Vector2f({1000.f,400.f}));
    }

    /// @brief Destructor of the game renderer.
    GameRenderer::~GameRenderer ()
    {

    }

    /// @brief Update the GameRenderer with the current state of the game
    void GameRenderer::update (long flags)
    {
        if(GAME_TURN_CHANGED & flags){
            //Update the turn token
            int turn = this->game->getTurn();
            if (turn < 5){
                this->boardTurnTexture->loadFromFile("./resources/img/turn_"+std::to_string(turn)+".png");
                this->boardTurnSprite->setTexture(*(this->boardTurnTexture));
            }
        }
        
        if(GAME_PHASE_CHANGED & flags){
            //Reset the Board of Resources
            this->boardMaterialSprite->setColor(sf::Color::White);
            this->boardEnergySprite->setColor(sf::Color::White);
            this->boardScienceSprite->setColor(sf::Color::White);
            this->boardGoldSprite->setColor(sf::Color::White);
            this->boardExplorationSprite->setColor(sf::Color::White);


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
                    this->boardMaterialSprite->setColor(sf::Color(127,127,127));
                    this->boardEnergySprite->setColor(sf::Color(127,127,127));
                    this->boardScienceSprite->setColor(sf::Color(127,127,127));
                    this->boardGoldSprite->setColor(sf::Color(127,127,127));
                    this->boardExplorationSprite->setColor(sf::Color(127,127,127));

                    //Only ligth up the board of the currently produced resource
                    switch (this->game->getResourceProducing()){
                        case state::MATERIAL:
                            this->boardMaterialSprite->setColor(sf::Color::White);
                            break;
                        case state::ENERGY:
                            this->boardEnergySprite->setColor(sf::Color::White);
                            break;
                        case state::SCIENCE:
                            this->boardScienceSprite->setColor(sf::Color::White);
                            break;
                        case state::GOLD:
                            this->boardGoldSprite->setColor(sf::Color::White);
                            break;
                        case state::EXPLORATION:
                            this->boardExplorationSprite->setColor(sf::Color::White);
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

    void GameRenderer::draw(sf::RenderWindow& window){
        window.draw(*this->boardMaterialSprite);
        window.draw(*this->boardEnergySprite);
        window.draw(*this->boardScienceSprite);
        window.draw(*this->boardGoldSprite);
        window.draw(*this->boardExplorationSprite);
        window.draw(*this->boardTurnSprite);
        window.draw(*this->phaseIndicator);
    }
}