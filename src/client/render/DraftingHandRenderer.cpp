#include "DraftingHandRenderer.h"

#include <string>

#include "../../constants/constants/PlayerObserversNotification.h"
#include "../../constants/constants/GameConstants.h"
#include "../../constants/constants/CustomTypes.h"

namespace render
{
    /// @brief Full constrcutor of the drafting hand renderer
    /// @param player Player that is playing.
    /// @param position Position of the element on the main view.
    DraftingHandRenderer::DraftingHandRenderer (constants::playerPtr player, sf::Vector2f position) :
        player(player),
        textureBackground(constants::ResourceManager::getTexture("./resources/img/player_draft.png")),
        textureHand(constants::ResourceManager::getTexture("./resources/img/pfp_draft.png")),
        devCardRenderers({})
    {
		//Creation of the Font for the Texts
		sf::Font f;
		f.loadFromFile("./resources/font/arial.ttf");
		this->font = f;

        //Get cards
        constants::deckOfCards cards = player->getDraftingCards();

        //Enter Player board (position 0 in sprites)
        this->spriteBackground.setTexture(this->textureBackground);
        this->spriteBackground.setPosition(position);

        //Enter Player Profile Picture (position 1 in sprites)
        this->spriteHand.setTexture(this->textureHand);
        this->spriteHand.setPosition(position + sf::Vector2f({10.f,50.f}));

        //Enter Cards (position 2 to 9 in sprites)
        for (size_t i = 0; (NUMBER_OF_CARDS_DRAFTED > i) && (cards.size() > i); i++)
        {
            DevelopmentCardRenderer* cRenderer = new DevelopmentCardRenderer(cards[i],position+sf::Vector2f(350.f+180.f*(i),10.f),170.f/375.f);
            this->devCardRenderers.push_back(cRenderer);	//Card Renderer
        }

        //Enter Player Name (position 0 in texts)
        this->text.setFont(font);
        this->text.setString("Drafting Hand");
        this->text.setCharacterSize(30);
        this->text.setFillColor(sf::Color::White);
        this->text.setPosition(position+sf::Vector2f({10.f,10.f}));
    }
    
    /// @brief update the DraftingHandRenderer with the current state of the game
    /// @param flags Flags used to knwo what changed on a player. Only DRAFTING_CARDS_CHANGED is relevent here.
    void DraftingHandRenderer::update (long flags)
    {
		constants::deckOfCards cards = player->getDraftingCards();
		        
        if(DRAFTING_CARDS_CHANGED & flags)
        {
            this->devCardRenderers.clear();
            //Create new Cards
            for (size_t i = 0; (NUMBER_OF_CARDS_DRAFTED > i) && (cards.size() > i); i++)
            {
                DevelopmentCardRenderer* cRenderer = new DevelopmentCardRenderer(cards[i], this->spriteBackground.getPosition() + sf::Vector2f(300.f+120.f*(i),0.f), 170.f/375.f);
                this->devCardRenderers.push_back(cRenderer);	//Card Renderer
                cRenderer->update(flags);
            }
        }
    }

    /// @brief Draw the drafting hand on the main window.
    /// @param window Window where the hand is displayed.
    void DraftingHandRenderer::draw(sf::RenderWindow& window)
    {
        window.draw(this->spriteBackground);
        window.draw(this->spriteHand);
        window.draw(this->text);

		for(DevelopmentCardRenderer* cRenderer: this->devCardRenderers)
        {
			cRenderer->draw(window);
		}
    }

    /// @brief Handle an event that occurs on this view. Call the method for every card inside.
    /// @param event Event that may occur (click, key press, ...)
    /// @param window Window where the event occured.
    /// @param scene Scene (main view) where the card takes place.
    void DraftingHandRenderer::handleEvent (sf::Event event, sf::RenderWindow& window, Scene* scene)
    {
        for(DevelopmentCardRenderer* c: this->devCardRenderers)
        {
			c->handleEvent(event,window,scene);
		}
    }

}