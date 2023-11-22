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
        sf::Texture cardDesign = this->card->getDesign();
        this->texture = &cardDesign;

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
        // Retrieve the elements to pay.
        std::vector<state::ResourceToPay*> vectorOfElementsToPay = this->card->getCostToBuild();
        
        // Iterating among all resources that needs to be paid.
        for (long unsigned int index = 0; index < vectorOfCrossesSprite.size(); index++)
        {
            if (vectorOfElementsToPay[index]->isPaid)
            {
                this->vectorOfCrossesSprite[index]->setTexture(*(this->paidTexture));
            }
        }
    }

    /************************************* Setters & Getters *************************************/

    std::vector<sf::Sprite*> DevelopmentCardRenderer::getVectorOfCrossesSprite () const
    {
        return this->vectorOfCrossesSprite;
    }
}