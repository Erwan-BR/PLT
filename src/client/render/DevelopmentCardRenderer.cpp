#include "DevelopmentCardRenderer.h"

namespace render
{
    /// @brief Constructor of the card renderer.
    /// @param card Card to render.
    DevelopmentCardRenderer::DevelopmentCardRenderer (state::DevelopmentCard* card,sf::Transform transform) :
        card(card)
    {
        this->texture = new sf::Texture();
        sf::Texture* cardDesign = this->card->getDesign();
        this->texture = cardDesign;

        //this->sprite->setTexture(*(this->texture));

        this->transform = transform;

        this->vectorOfCrossesSprite = {};
        this->vectorOfCrossesTransform = {};

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
            vectorOfCrossesTransform.push_back(sf::Transform(transform).translate(0.0f,0.0f+10.0f*index));
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

    /// @brief Get the vector of sprites that shows if a resource is paid or not.
    /// @return Vector of sprites.
    std::vector<sf::Sprite*> DevelopmentCardRenderer::getVectorOfCrossesSprite () const
    {
        return this->vectorOfCrossesSprite;
    }

    sf::Sprite* DevelopmentCardRenderer::getSprite(){
        return this->sprite;
    }

    std::vector<sf::Transform> DevelopmentCardRenderer::getVectorOfCrossesTransform ()
    {
        return this->vectorOfCrossesTransform;
    }

    sf::Transform DevelopmentCardRenderer::getTransform(){
        return this->transform;
    }
}