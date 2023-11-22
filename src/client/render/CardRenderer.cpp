#include "DevelopmentCardRenderer.h"

namespace render
{
    /// @brief Constructor of the card renderer.
    DevelopmentCardRenderer::DevelopmentCardRenderer ()
    {
        this->card = new state::DevelopmentCard();
        this->texture = new sf::Texture();
        this->sprite = new sf::Sprite();
    }

    /// @brief Constructor of the card renderer.
    /// @param card Card to render.
    DevelopmentCardRenderer::DevelopmentCardRenderer (state::DevelopmentCard* card) :
        card(card),
        texture(&(card->getDesign()))
    {
        this->sprite->setTexture(*(this->texture));
    }

    /// @brief Destructor of the card renderer.
    DevelopmentCardRenderer::~DevelopmentCardRenderer ()
    {

    }

    /// @brief Update the render of the Renderer of Card.
    void DevelopmentCardRenderer::update ()
    {
        for (auto element : card->get)
        {
            ;
        }
    }
}