#include "GameRenderer.h"

namespace render
{
    /// @brief  Full constructor of GameRenderer
    /// @param game Game to render
    /// @param transform Transformation to do to display it
    GameRenderer::GameRenderer (state::Game* game, sf::Transform transform)
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
        this->boardMaterialTransform = sf::Transform(transform).translate(400.0f,500.0f).scale(0.2f,0.2f);

        //Generate the Board Part for ENERGY
        this->boardEnergyTexture = new sf::Texture();
		this->boardEnergyTexture->loadFromFile("./resources/img/board_energy.png");
		this->boardEnergySprite = new sf::Sprite();
		this->boardEnergySprite->setTexture(*(this->boardEnergyTexture));
        this->boardEnergyTransform = sf::Transform(transform).translate(620.0f,500.0f).scale(0.2f,0.2f);
        
        //Generate the Board Part for GOLD
        this->boardGoldTexture = new sf::Texture();
		this->boardGoldTexture->loadFromFile("./resources/img/board_gold.png");
		this->boardGoldSprite = new sf::Sprite();
		this->boardGoldSprite->setTexture(*(this->boardGoldTexture));
        this->boardGoldTransform = sf::Transform(transform).translate(1060.0f,500.0f).scale(0.2f,0.2f);

        //Generate the Board Part for Science
        this->boardScienceTexture = new sf::Texture();
		this->boardScienceTexture->loadFromFile("./resources/img/board_science.png");
		this->boardScienceSprite = new sf::Sprite();
		this->boardScienceSprite->setTexture(*(this->boardScienceTexture));
        this->boardScienceTransform = sf::Transform(transform).translate(840.0f,500.0f).scale(0.2f,0.2f);

        //Generate the Board Part for EXPLORATION
        this->boardExplorationTexture = new sf::Texture();
		this->boardExplorationTexture->loadFromFile("./resources/img/board_exploration.png");
		this->boardExplorationSprite = new sf::Sprite();
		this->boardExplorationSprite->setTexture(*(this->boardExplorationTexture));
        this->boardExplorationTransform = sf::Transform(transform).translate(1280.0f,500.0f).scale(0.2f,0.2f);

        //Generate the Turn Token
        this->boardTurnTexture = new sf::Texture();
		this->boardTurnTexture->loadFromFile("./resources/img/turn_1.png");
		this->boardTurnSprite = new sf::Sprite();
		this->boardTurnSprite->setTexture(*(this->boardTurnTexture));
        this->boardTurnTransform = sf::Transform(transform).translate(900.0f,400.0f).scale(0.2f,0.2f);

        //Generate the text for Phase
        this->phaseIndicator = new sf::Text();
        this->phaseIndicator->setFont(font);
        this->phaseIndicator->setCharacterSize(30);
        this->phaseIndicator->setFillColor(sf::Color::White);
        this->phaseIndicatorTransform = sf::Transform(transform).translate(1000.0f,400.0f);
    }

    /// @brief Destructor of the game renderer.
    GameRenderer::~GameRenderer ()
    {

    }

    /// @brief Update the GameRenderer with the current state of the game
    void GameRenderer::update ()
    {
        //Update the turn token
        int turn = this->game->getTurn();
        if (turn < 5){
            this->boardTurnTexture->loadFromFile("./resources/img/turn_"+std::to_string(turn)+".png");
            this->boardTurnSprite->setTexture(*(this->boardTurnTexture));
        }
        
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

    void GameRenderer::draw(sf::RenderWindow& window){
        window.draw(*this->boardMaterialSprite,this->boardMaterialTransform);
        window.draw(*this->boardEnergySprite,this->boardEnergyTransform);
        window.draw(*this->boardScienceSprite,this->boardScienceTransform);
        window.draw(*this->boardGoldSprite,this->boardGoldTransform);
        window.draw(*this->boardExplorationSprite,this->boardExplorationTransform);
        window.draw(*this->boardTurnSprite,this->boardTurnTransform);
        window.draw(*this->phaseIndicator,this->phaseIndicatorTransform);
    }
}