#include "DevelopmentCardRenderer.h"

#include "constants/CustomTypes.h"

namespace render
{
    /// @brief Constructor of the card renderer.
    /// @param card Card to render.
    /// @param position Position of the card that is displayed.
    /// @param scale Float that represent how to scale the card in the view.
    DevelopmentCardRenderer::DevelopmentCardRenderer (std::shared_ptr<state::DevelopmentCard> card, sf::Vector2f position, float scale) :
        card(card),
        texture(constants::ResourceManager::getTexture(this->card->getRelativePathToTexture())),
        paidTexture(constants::ResourceManager::getTexture("./resources/img/resourcesPaid.png")),
        notPaidTexture(constants::ResourceManager::getTexture("./resources/img/resourcesNotPaid.png"))
    {
        //Generate Sprite
        this->sprite.setTexture(this->texture);
        this->sprite.setPosition(position);
        this->sprite.setScale(scale,scale);

        this->hitbox = this->sprite.getGlobalBounds();

        //Get number of crosses (ie number of resources to build)
        size_t numberOfSprites = this->card->getCostToBuild().size();
        
        //Initialize Vector
        this->vectorOfCrossesSprite = std::vector<sf::Sprite>(numberOfSprites, sf::Sprite());

        //Create the Sprite using the notPaid Texture
        for (size_t index = 0; numberOfSprites > index; index++)
        {
            vectorOfCrossesSprite[index].setTexture(this->notPaidTexture);
            vectorOfCrossesSprite[index].setScale(scale*0.035f,scale*0.035f);
            vectorOfCrossesSprite[index].setPosition(position+sf::Vector2f(25.f,7.0f+35.0f*index)*(scale));
        }
    }

    /// @brief Destructor of the card renderer.
    DevelopmentCardRenderer::~DevelopmentCardRenderer ()
    {
    }

    /// @brief Update the render of the Renderer of Card.
    /// @param flags Flags that indicate what should be updated. Not relevent here, but for other observer it is.
    void DevelopmentCardRenderer::update (long flags)
    {
        // Retrieve the elements to pay.
        constants::resourcePayList vectorOfElementsToPay = this->card->getCostToBuild();
        
        // Iterating among all resources that needs to be paid.
        for (size_t index = 0; index < vectorOfCrossesSprite.size(); index++)
        {
            if (vectorOfElementsToPay[index]->isPaid)
            {
                this->vectorOfCrossesSprite[index].setTexture(this->paidTexture);
            }
        }
    }

    /// @brief Draw the card on the screen
    /// @param window Window were the card has to be displayed.
    void DevelopmentCardRenderer::draw(sf::RenderWindow& window)
    {
        window.draw(this->sprite);
        for(int i=0;i<(int) this->vectorOfCrossesSprite.size();i++){
            window.draw(this->vectorOfCrossesSprite[i]);
        }
    }

    /// @brief Handle an event on the card. Allows to check if the card has been clicked by the player.
    /// @param event Event that may occur (click, key press, ...)
    /// @param window Window where the event occured.
    /// @param scene Scene (main view) where the card takes place.
    void DevelopmentCardRenderer::handleEvent (sf::Event event, sf::RenderWindow& window, Scene* scene)
    {
        // Check if the button is enabled, and pressed with a left click
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            
            // Check if the click is inside the button.
            if (this->hitbox.contains(mousePos))
            {
                //std::cout<<"Card Clicked:"<<this->card->getName()<<std::endl;
                scene->setSelectedCard(this->card);
            }
        }
    }
}