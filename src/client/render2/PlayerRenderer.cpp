#include "PlayerRenderer.h"

namespace render2 {

	PlayerRenderer::PlayerRenderer(){

	}

	PlayerRenderer::PlayerRenderer(state::Player* player){
		this->texture =sf::Texture();
		//this->texture.loadFromFile("file");
		this->player_Sprite=sf::Sprite();
		(this->player_Sprite).setTexture(this->texture);
	}

	PlayerRenderer::~PlayerRenderer(){

	}
    
	void PlayerRenderer::draw (sf::RenderWindow* window){
		window->draw(this->player_Sprite);
	}

};

