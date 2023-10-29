#include "CardRenderer.h"

namespace render2 {

	CardRenderer::CardRenderer(){

	}

	CardRenderer::CardRenderer(std::string path, int hor_pos, int ver_pos){
		this->texture =sf::Texture();
		this->texture.loadFromFile(path);
		this->card_Sprite=sf::Sprite();
		(this->card_Sprite).setTexture(this->texture);
		this->horizontal_position = hor_pos;
		this->vertical_position = ver_pos;
	}

	CardRenderer::~CardRenderer(){

	}
    
	void CardRenderer::draw (sf::RenderWindow* window){
		window->draw(this->card_Sprite);
	}

	void CardRenderer::changePosition (int hor_pos, int ver_pos){
		this->horizontal_position = hor_pos;
		this->vertical_position = ver_pos;
	}

};

