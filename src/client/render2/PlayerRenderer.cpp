#include "PlayerRenderer.h"

namespace render2 {

    
	void PlayerRenderer::draw (sf::RenderWindow* window){
		window->draw(this->player_Sprite);
	}

};

