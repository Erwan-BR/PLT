#include "DraftingHandRenderer.h"

#include <string>

#include "../../constants/constants/PlayerObserversNotification.h"
#include "../../constants/constants/GameConstants.h"

namespace render {
    DraftingHandRenderer::DraftingHandRenderer (std::shared_ptr<state::Player> player, sf::Vector2f position){
		//Creation of the Font for the Texts
		sf::Font f;
		f.loadFromFile("./resources/font/arial.ttf");
		this->font = f;

        //Store Player attribute
		this->player = player;

        //Get cards
        std::vector<std::shared_ptr<state::DevelopmentCard>> cards = player->getDraftingCards();

        //Initialize the vectors
		this->sprites = {};
		this->devCardRenderers = {};
		this->texts = {};

		sf::Texture* texture;
		sf::Sprite* sprite;
		sf::Text* text;
		

        //Enter Player board (position 0 in sprites)
        texture = new sf::Texture();
        texture->loadFromFile("./resources/img/player_draft.png");
        this->textures.push_back(texture);					//Texture
        sprite= new sf::Sprite();
        sprite->setTexture(*(this->textures[0]));
        sprite->setPosition(position);
        this->sprites.push_back(sprite);					//Sprite

        //Enter Player Profile Picture (position 1 in sprites)
        texture = new sf::Texture();
        texture->loadFromFile("./resources/img/pfp_draft.png");
        this->textures.push_back(texture);					//Texture
        sprite= new sf::Sprite();
        sprite->setTexture(*(this->textures[1]));
        sprite->setPosition(position+sf::Vector2f({10.f,50.f}));
        this->sprites.push_back(sprite);					//Sprite

        //Enter Cards (position 2 to 9 in sprites)
        for (size_t i = 0; (NUMBER_OF_CARDS_DRAFTED > i) && (cards.size() > i); i++)
        {
            DevelopmentCardRenderer* cRenderer = new DevelopmentCardRenderer(cards[i],position+sf::Vector2f(350.f+180.f*(i),10.f),170.f/375.f);
            this->devCardRenderers.push_back(cRenderer);	//Card Renderer
        }

        //Enter Player Name (position 0 in texts)
        text = new sf::Text();
        text->setFont(font);
        text->setString("Drafting Hand");
        text->setCharacterSize(30);
        text->setFillColor(sf::Color::White);
        text->setPosition(position+sf::Vector2f({10.f,10.f}));
        this->texts.push_back(text);			//Text
    }
    
    /// @brief update the DraftingHandRenderer with the current state of the game
    void DraftingHandRenderer::update (long flags){
        //Get Cards
		std::vector<std::shared_ptr<state::DevelopmentCard>> cards = player->getDraftingCards();
		        
        if(flags & DRAFTING_CARDS_CHANGED){
            this->devCardRenderers = {};
            //Create new Cards
            for (size_t i = 0; (NUMBER_OF_CARDS_DRAFTED > i) && (cards.size() > i); i++)
            {
                DevelopmentCardRenderer* cRenderer = new DevelopmentCardRenderer(cards[i],sprites[0]->getPosition()+sf::Vector2f(300.f+120.f*(i),0.f),170.f/375.f);
                this->devCardRenderers.push_back(cRenderer);	//Card Renderer
                cRenderer->update(flags);
            }
        }
    }

    void DraftingHandRenderer::draw(sf::RenderWindow& window){
        for(size_t i = 0; this->sprites.size() > i; i++){
			window.draw(*(this->sprites[i]));
		}
		for(size_t i = 0; this->texts.size() > i; i++){
			window.draw(*(this->texts[i]));
		}
		for(DevelopmentCardRenderer* cRenderer: this->devCardRenderers){
			cRenderer->draw(window);
		}
    }

    void DraftingHandRenderer::handleEvent (sf::Event event, sf::RenderWindow& window, Scene* scene){
        for(DevelopmentCardRenderer* c: this->devCardRenderers){
			c->handleEvent(event,window,scene);
		}
    }

}