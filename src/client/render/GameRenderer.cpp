#include "GameRenderer.h"

namespace render
{
    /// @brief  Full constructor of GameRenderer
    /// @param game 
    /// @param transform 
    GameRenderer::GameRenderer (state::Game* game, sf::Transform transform)
    {
        this->game = game;

        this->boardMaterialTexture = new sf::Texture();
		this->boardMaterialTexture->loadFromFile("./resources/img/board_material.png");
		this->boardMaterialSprite = new sf::Sprite();
		this->boardMaterialSprite->setTexture(*(this->boardTexture));
        this->boardMaterialTransform = sf::Transform(transform).translate(400.0f,500.0f).scale(0.1f,0.1f);

        this->boardEnergyTexture = new sf::Texture();
		this->boardEnergyTexture->loadFromFile("./resources/img/board_energy.png");
		this->boardEnergySprite = new sf::Sprite();
		this->boardEnergySprite->setTexture(*(this->boardTexture));
        this->boardEnergyTransform = sf::Transform(transform).translate(600.0f,500.0f).scale(0.1f,0.1f);
        
        this->boardGoldTexture = new sf::Texture();
		this->boardGoldTexture->loadFromFile("./resources/img/board_gold.png");
		this->boardGoldSprite = new sf::Sprite();
		this->boardGoldSprite->setTexture(*(this->boardTexture));
        this->boardGoldTransform = sf::Transform(transform).translate(800.0f,500.0f).scale(0.1f,0.1f);

        this->boardScienceTexture = new sf::Texture();
		this->boardScienceTexture->loadFromFile("./resources/img/board_science.png");
		this->boardScienceSprite = new sf::Sprite();
		this->boardScienceSprite->setTexture(*(this->boardTexture));
        this->boardScienceTransform = sf::Transform(transform).translate(1000.0f,500.0f).scale(0.1f,0.1f);

        this->boardExplorationTexture = new sf::Texture();
		this->boardExplorationTexture->loadFromFile("./resources/img/board_exploration.png");
		this->boardExplorationSprite = new sf::Sprite();
		this->boardExplorationSprite->setTexture(*(this->boardTexture));
        this->boardExplorationTransform = sf::Transform(transform).translate(1200.0f,500.0f).scale(0.1f,0.1f);

        this->boardTurnTexture = new sf::Texture();
		this->boardTurnTexture->loadFromFile("./resources/img/turn_1.png");
		this->boardTurnSprite = new sf::Sprite();
		this->boardTurnSprite->setTexture(*(this->boardTexture));
        this->boardTurnTransform = sf::Transform(transform).translate(800.0f,400.0f).scale(0.2f,0.2f);

        
    }

    /// @brief Destructor of the game renderer.
    GameRenderer::~GameRenderer ()
    {

    }

    /// @brief Update the render of the Renderer of Game.
    void GameRenderer::update ()
    {
        
    }
}