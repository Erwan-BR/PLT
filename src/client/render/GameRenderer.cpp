#include "GameRenderer.h"

namespace render
{
    /// @brief  Full constructor of GameRenderer
    /// @param game Game to render
    /// @param transform Transformation to do to display it
    GameRenderer::GameRenderer (state::Game* game, sf::Transform transform)
    {
        this->game = game;

        this->font = sf::Font();
        this->font.loadFromFile("./resources/font/arial.ttf");

        this->boardMaterialTexture = new sf::Texture();
		this->boardMaterialTexture->loadFromFile("./resources/img/board_material.png");
		this->boardMaterialSprite = new sf::Sprite();
		this->boardMaterialSprite->setTexture(*(this->boardMaterialTexture));
        this->boardMaterialTransform = sf::Transform(transform).translate(400.0f,500.0f).scale(0.2f,0.2f);

        this->boardEnergyTexture = new sf::Texture();
		this->boardEnergyTexture->loadFromFile("./resources/img/board_energy.png");
		this->boardEnergySprite = new sf::Sprite();
		this->boardEnergySprite->setTexture(*(this->boardEnergyTexture));
        this->boardEnergyTransform = sf::Transform(transform).translate(620.0f,500.0f).scale(0.2f,0.2f);
        
        this->boardGoldTexture = new sf::Texture();
		this->boardGoldTexture->loadFromFile("./resources/img/board_gold.png");
		this->boardGoldSprite = new sf::Sprite();
		this->boardGoldSprite->setTexture(*(this->boardGoldTexture));
        this->boardGoldTransform = sf::Transform(transform).translate(1060.0f,500.0f).scale(0.2f,0.2f);

        this->boardScienceTexture = new sf::Texture();
		this->boardScienceTexture->loadFromFile("./resources/img/board_science.png");
		this->boardScienceSprite = new sf::Sprite();
		this->boardScienceSprite->setTexture(*(this->boardScienceTexture));
        this->boardScienceTransform = sf::Transform(transform).translate(840.0f,500.0f).scale(0.2f,0.2f);

        this->boardExplorationTexture = new sf::Texture();
		this->boardExplorationTexture->loadFromFile("./resources/img/board_exploration.png");
		this->boardExplorationSprite = new sf::Sprite();
		this->boardExplorationSprite->setTexture(*(this->boardExplorationTexture));
        this->boardExplorationTransform = sf::Transform(transform).translate(1280.0f,500.0f).scale(0.2f,0.2f);

        this->boardTurnTexture = new sf::Texture();
		this->boardTurnTexture->loadFromFile("./resources/img/turn_1.png");
		this->boardTurnSprite = new sf::Sprite();
		this->boardTurnSprite->setTexture(*(this->boardTurnTexture));
        this->boardTurnTransform = sf::Transform(transform).translate(900.0f,400.0f).scale(0.2f,0.2f);

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

    /// @brief Update the render of the Renderer of Game.
    void GameRenderer::update ()
    {
        int turn = this->game->getTurn();
        if (turn < 5){
            this->boardTurnTexture->loadFromFile("./resources/img/turn_"+std::to_string(turn)+".png");
            this->boardTurnSprite->setTexture(*(this->boardTurnTexture));
        }

        this->boardMaterialSprite->setColor(sf::Color::White);
        this->boardEnergySprite->setColor(sf::Color::White);
        this->boardScienceSprite->setColor(sf::Color::White);
        this->boardGoldSprite->setColor(sf::Color::White);
        this->boardExplorationSprite->setColor(sf::Color::White);

        switch (this->game->getPhase()){
            case state::DRAFT:
                this->phaseIndicator->setString("DRAFT");
                break;
            case state::PLANIFICATION:
                this->phaseIndicator->setString("PLANIFICATION");
                break;
            case state::PRODUCTION:
                this->phaseIndicator->setString("PRODUCTION");
                switch (this->game->getResourceProducing()){
                    case state::MATERIAL:
                        this->boardMaterialSprite->setColor(sf::Color(127,127,127));
                        break;
                    case state::ENERGY:
                        this->boardEnergySprite->setColor(sf::Color(127,127,127));
                        break;
                    case state::SCIENCE:
                        this->boardScienceSprite->setColor(sf::Color(127,127,127));
                        break;
                    case state::GOLD:
                        this->boardGoldSprite->setColor(sf::Color(127,127,127));
                        break;
                    case state::EXPLORATION:
                        this->boardExplorationSprite->setColor(sf::Color(127,127,127));
                        break;
                    default:
                        break;
                }
                break;
        }
    }

    /************************************* Setters & Getters *************************************/

    sf::Sprite* GameRenderer::getBoardMaterialSprite ()
    {
        return this->boardMaterialSprite;
    }
    sf::Transform GameRenderer::getBoardMaterialTransform ()
    {
        return this->boardMaterialTransform;
    }
    sf::Sprite* GameRenderer::getBoardEnergySprite ()
    {
        return this->boardEnergySprite;
    }
    sf::Transform GameRenderer::getBoardEnergyTransform ()
    {
        return this->boardEnergyTransform;
    }
    sf::Sprite* GameRenderer::getBoardGoldSprite ()
    {
        return this->boardGoldSprite;
    }
    sf::Transform GameRenderer::getBoardGoldTransform ()
    {
        return this->boardGoldTransform;
    }
    sf::Sprite* GameRenderer::getBoardScienceSprite ()
    {
        return this->boardScienceSprite;
    }
    sf::Transform GameRenderer::getBoardScienceTransform ()
    {
        return this->boardScienceTransform;
    }
    sf::Sprite* GameRenderer::getBoardExplorationSprite ()
    {
        return this->boardExplorationSprite;
    }
    sf::Transform GameRenderer::getBoardExplorationTransform ()
    {
        return this->boardExplorationTransform;
    }
    sf::Sprite* GameRenderer::getBoardTurnSprite ()
    {
        return this->boardTurnSprite;
    }
    sf::Transform GameRenderer::getBoardTurnTransform ()
    {
        return this->boardTurnTransform;
    }
    sf::Text* GameRenderer::getPhaseIndicator ()
    {
        return this->phaseIndicator;
    }
    sf::Transform GameRenderer::getPhaseIndicatorTransform ()
    {
        return this->phaseIndicatorTransform;
    }
}