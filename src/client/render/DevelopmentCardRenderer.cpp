#include "DevelopmentCardRenderer.h"

namespace render
{
    /// @brief Constructor of the card renderer.
    /// @param card Card to render.
    DevelopmentCardRenderer::DevelopmentCardRenderer (state::DevelopmentCard* card,sf::Transform transform,float scale) :
        card(card)
    {
        //Get the Texture form Card
        this->texture = new sf::Texture();
        sf::Texture* cardDesign = this->card->getDesign();
        this->texture = cardDesign;

        //Generate Sprite
        this->sprite = new sf::Sprite();
        this->sprite->setTexture(*(this->texture));

        //Store transform
        this->transform = sf::Transform(transform).scale(scale,scale);

        //Initialize Vecotor
        this->vectorOfCrossesSprite = {};
        this->vectorOfCrossesTransform = {};

        // Creating textures for paid and not paid resources.
        this->paidTexture = new sf::Texture();
		this->paidTexture->loadFromFile("./resources/img/resourcesPaid.png");
        this->notPaidTexture = new sf::Texture();
		this->notPaidTexture->loadFromFile("./resources/img/resourcesNotPaid.png");

        //Get number of crosses (ie number of resources to build)
        long unsigned int numberOfSprites = this->card->getCostToBuild().size();

        //Create the Sprite using the notPaid Texture
        for (long unsigned int index = 0; index < numberOfSprites; index++)
        {
            vectorOfCrossesSprite.push_back(new sf::Sprite());
            vectorOfCrossesSprite[index]->setTexture(*(this->notPaidTexture));
            vectorOfCrossesTransform.push_back(sf::Transform(transform).scale(scale,scale).translate(30.0f,10.0f+35.0f*index).scale(0.035f,0.035f));
        }
    }

    /// @brief Destructor of the card renderer.
    DevelopmentCardRenderer::~DevelopmentCardRenderer ()
    {
        free(this->paidTexture);
        free(this->notPaidTexture);
        for(sf::Sprite* s : this->vectorOfCrossesSprite){
            free(s);
        }
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

    void DevelopmentCardRenderer::draw(sf::RenderWindow& window){
        window.draw(*this->sprite,this->transform);
        for(int i=0;i<(int) this->vectorOfCrossesSprite.size();i++){
            window.draw(*(this->vectorOfCrossesSprite[i]),this->vectorOfCrossesTransform[i]);
        }
    }
}