#include "DraftingHandRenderer.h"
#include <string>

namespace render {
    DraftingHandRenderer::DraftingHandRenderer (state::Player* player, sf::Transform transform){
		//Creation of the Font for the Texts
		sf::Font f;
		f.loadFromFile("./resources/font/arial.ttf");
		this->font = f;

		this->player = player;
        std::vector<state::DevelopmentCard*> cards = player->getDraftingCards();

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
            cRenderer = new DevelopmentCardRenderer(cards[i],sf::Transform(sprite_transforms[0]).translate(350.f+180.f*(i),10.f).scale(0.35f,0.35f).scale(1.f,(431.f/375.f)));
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
    sf::Sprite* DraftingHandRenderer::getSprite (int index){
        return this->sprites[index];
    }
    sf::Transform DraftingHandRenderer::getSpriteTransform (int index){
        return this->sprite_transforms[index];
    }
    int DraftingHandRenderer::getNumberSprite (){
        return this->sprites.size();
    }
    sf::Text* DraftingHandRenderer::getText (int index){
        return this->texts[index];
    }
    sf::Transform DraftingHandRenderer::getTextTransform (int index){
        return this->text_transforms[index];
    }
    int DraftingHandRenderer::getNumberText (){
        return this->texts.size();
    }
    DevelopmentCardRenderer* DraftingHandRenderer::getCardRenderer (int index){
        return this->devCardRenderers[index];
    }

    int DraftingHandRenderer::getNumberCardRenderer (){
        return this->devCardRenderers.size();
    }
    
    void DraftingHandRenderer::update (){
        DevelopmentCardRenderer* cRenderer;

		std::vector<state::DevelopmentCard*> cards = player->getDraftingCards();
		int i;
		
        for (i=0;i<7 and i<(int) cards.size();i++){
            cRenderer = new DevelopmentCardRenderer(cards[i],sf::Transform(sprite_transforms[0]).translate(350.f+180.f*(i),10.f).scale(0.35f,0.35f).scale(1.f,(431.f/375.f)));
            this->devCardRenderers.push_back(cRenderer);	//Card Renderer
        }
		

		for(i=0; i<this->getNumberCardRenderer();i++){
			(this->getCardRenderer(i))->update();
		}

    }



}