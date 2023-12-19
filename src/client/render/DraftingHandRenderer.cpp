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
            cRenderer = new DevelopmentCardRenderer(cards[i],sf::Transform(sprite_transforms[0]).translate(350.f+180.f*(i),10.f));
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

    /// @brief Getter Sprites
    /// @param index position of the wanted sprite in sprites
    /// @return Pointer to wanted Sprite
    sf::Sprite* DraftingHandRenderer::getSprite (int index){
        return this->sprites[index];
    }

    /// @brief Getter Transform for sprite
    /// @param index position of the wanted transform in sprite_transform
    /// @return Wanted Transform
    sf::Transform DraftingHandRenderer::getSpriteTransform (int index){
        return this->sprite_transforms[index];
    }

    /// @brief Getter number of Sprite
    /// @return Number of Sprite in sprites
    int DraftingHandRenderer::getNumberSprite (){
        return this->sprites.size();
    }

    /// @brief Getter Text
    /// @param index position of the wanted Text in texts
    /// @return Pointer to wanted Text
    sf::Text* DraftingHandRenderer::getText (int index){
        return this->texts[index];
    }

    /// @brief Getter Transform for Text
    /// @param index position of the wanted transform in text_transform
    /// @return Wanted Transform
    sf::Transform DraftingHandRenderer::getTextTransform (int index){
        return this->text_transforms[index];
    }

    /// @brief Getter number of Text
    /// @return Number of Text in texts
    int DraftingHandRenderer::getNumberText (){
        return this->texts.size();
    }

    /// @brief Getter CardRenderer
    /// @param index position of the wanted renderer in devCardRenderers
    /// @return Pointer to wanted CardRenderer
    DevelopmentCardRenderer* DraftingHandRenderer::getCardRenderer (int index){
        return this->devCardRenderers[index];
    }

    /// @brief Getter number of CardRenderer
    /// @return Number of CardRenderer in devCardRenderers
    int DraftingHandRenderer::getNumberCardRenderer (){
        return this->devCardRenderers.size();
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
            cRenderer = new DevelopmentCardRenderer(cards[i],sf::Transform(sprite_transforms[0]).translate(350.f+180.f*(i),10.f));
            this->devCardRenderers.push_back(cRenderer);	//Card Renderer
        }
		
        //Update Cards
		for(i=0; i<this->getNumberCardRenderer();i++){
			(this->getCardRenderer(i))->update();
		}

    }



}