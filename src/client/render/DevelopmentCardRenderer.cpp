#include "DevelopmentCardRenderer.h"

namespace render
{
    /// @brief Constructor of the card renderer.
    /// @param card Card to render.
    DevelopmentCardRenderer::DevelopmentCardRenderer (state::DevelopmentCard* card) :
        card(card)
    {
        this->sprite->setTexture(*(this->texture));
        
        this->texture = new sf::Texture();
        this->texture = &(this->card->getDesign());
        this->vectorOfCrossesSprite = {};

        // Creating textures for paid and not paid resources.
        this->paidTexture = new sf::Texture();
		this->paidTexture->loadFromFile("./resources/img/resourcesPaid.png");
        this->notPaidTexture = new sf::Texture();
		this->notPaidTexture->loadFromFile("./resources/img/resourcesNotPaid.png");

        long unsigned int numberOfSprites = this->card->getCostToBuild().size();

        for (long unsigned int index = 0; index < numberOfSprites; index++)
        {
            vectorOfCrossesSprite.push_back(new sf::Sprite());
            vectorOfCrossesSprite[index]->setTexture(*(this->notPaidTexture));
        }
    }

    /// @brief Destructor of the card renderer.
    DevelopmentCardRenderer::~DevelopmentCardRenderer ()
    {

    }

    /// @brief Update the render of the Renderer of Card.
    void DevelopmentCardRenderer::update ()
    {
        // Coordinate of the current cross to put.
        int xPosition;
        int yPosition;

        // Iterating among all resource that needs to be paid.
        for (state::ResourceToPay* resourceToPay : this->card->getCostToBuild())
        {
            ;
        }
    }
}