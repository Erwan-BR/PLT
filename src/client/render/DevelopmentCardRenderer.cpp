#include "DevelopmentCardRenderer.h"

namespace render
{
    /// @brief Constructor of the card renderer.
    /// @param card Card to render.
    DevelopmentCardRenderer::DevelopmentCardRenderer (state::DevelopmentCard* card,sf::Vector2f position,float scale) :
        card(card)
    {
        //Get the Texture form Card
        this->texture = new sf::Texture();
        this->texture->loadFromFile(this->card->getRelativePathToTexture());

        //Generate Sprite
        this->sprite = new sf::Sprite();
        this->sprite->setTexture(*(this->texture));
        this->sprite->setPosition(position);
        this->sprite->setScale(scale,scale);

        this->hitbox = sf::FloatRect(this->sprite->getGlobalBounds());

        //Initialize Vecotor
        this->vectorOfCrossesSprite = {};

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
            vectorOfCrossesSprite[index]->setScale(scale*0.035f,scale*0.035f);
            vectorOfCrossesSprite[index]->setPosition(position+sf::Vector2f(25.f,7.0f+35.0f*index)*(scale));
        }
    }

    /// @brief Destructor of the card renderer.
    DevelopmentCardRenderer::~DevelopmentCardRenderer ()
    {
        free(this->paidTexture);
        free(this->notPaidTexture);
        for(sf::Sprite* s : this->vectorOfCrossesSprite){
            delete s;
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

    /// @brief Draw the card on the screen
    /// @param window Window were the card has to be displayed.
    void DevelopmentCardRenderer::draw(sf::RenderWindow& window){
        window.draw(*this->sprite);
        for(int i=0;i<(int) this->vectorOfCrossesSprite.size();i++){
            window.draw(*(this->vectorOfCrossesSprite[i]));
        }
    }

    void DevelopmentCardRenderer::handleEvent (sf::Event event, sf::RenderWindow& window)
    {
        // Check if the button is enabled, and pressed with a left click
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            
            // Check if the click is inside the button.
            if (this->hitbox.contains(mousePos))
            {
                //TODO
            }
        }
    }
}