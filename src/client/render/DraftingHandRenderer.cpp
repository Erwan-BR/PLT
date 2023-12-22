#include "DraftingHandRenderer.h"
#include <string>

namespace render {
    DraftingHandRenderer::DraftingHandRenderer (state::Player* player, sf::Transform transform){
		//Creation of the Font for the Texts
		sf::Font f;
		f.loadFromFile("./resources/font/arial.ttf");
		this->font = f;

        //Store Player attribute
		this->player = player;

        //Get cards
        std::vector<state::DevelopmentCard*> cards = player->getDraftingCards();

        //Initialize the vectors
		this->sprites = {};
		this->sprite_transforms = {};
		this->devCardRenderers = {};
		this->texts = {};
		this->text_transforms = {};

		int i;
		sf::Texture* texture;
		sf::Sprite* sprite;
		sf::Text* text;
		DevelopmentCardRenderer* cRenderer;

        //Enter Player board (position 0 in sprites)
        texture = new sf::Texture();
        texture->loadFromFile("./resources/img/player_draft.png");
        this->textures.push_back(texture);					//Texture
        sprite= new sf::Sprite();
        sprite->setTexture(*(this->textures[0]));
        this->sprites.push_back(sprite);					//Sprite
        this->sprite_transforms.push_back(transform);				//Transform

        //Enter Player Profile Picture (position 1 in sprites)
        texture = new sf::Texture();
        texture->loadFromFile("./resources/img/pfp_draft.png");
        this->textures.push_back(texture);					//Texture
        sprite= new sf::Sprite();
        sprite->setTexture(*(this->textures[1]));
        this->sprites.push_back(sprite);					//Sprite
        this->sprite_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(10.f,50.f));				//Transform

        //Enter Cards (position 2 to 9 in sprites)
        for (i=0;i<7 and i<(int) cards.size();i++){
            cRenderer = new DevelopmentCardRenderer(cards[i],sf::Transform(sprite_transforms[0]).translate(350.f+180.f*(i),10.f),150.f/375.f);
            this->devCardRenderers.push_back(cRenderer);	//Card Renderer
        }

        //Enter Player Name (position 0 in texts)
        text = new sf::Text();
        text->setFont(font);
        text->setString("Drafting Hand");
        text->setCharacterSize(30);
        text->setFillColor(sf::Color::White);
        this->texts.push_back(text);			//Text
        this->text_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(10.f,10.0f));		//Transform
    }
    
    /// @brief update the DraftingHandRenderer with the current state of the game
    void DraftingHandRenderer::update (){
        DevelopmentCardRenderer* cRenderer;

        //Get Cards
		std::vector<state::DevelopmentCard*> cards = player->getDraftingCards();

		int i;
		
        //Initialize vector
        this->devCardRenderers = {};

        //Create new Cards
        for (i=0;i<7 and i<(int) cards.size();i++){
            cRenderer = new DevelopmentCardRenderer(cards[i],sf::Transform(sprite_transforms[0]).translate(300.f+120.f*(i),0.f),170.f/375.f);
            this->devCardRenderers.push_back(cRenderer);	//Card Renderer
        }
		
        //Update Cards
		for(i=0; i<(int) this->devCardRenderers.size();i++){
			(this->devCardRenderers[i])->update();
		}
    }

    void DraftingHandRenderer::draw(sf::RenderWindow& window){
        for(int i=0;i<(int) this->sprites.size();i++){
			window.draw(*(this->sprites[i]),(this->sprite_transforms[i]));
		}
		for(int i=0;i<(int) this->texts.size();i++){
			window.draw(*(this->texts[i]),(this->text_transforms[i]));
		}
		for(DevelopmentCardRenderer* cRenderer: this->devCardRenderers){
			cRenderer->draw(window);
		}
    }


}