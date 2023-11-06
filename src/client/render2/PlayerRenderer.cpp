#include "PlayerRenderer.h"

namespace render2 {

	/// @brief Empty constructor of the PlayerRenderer class.
	PlayerRenderer::PlayerRenderer(){

	}

	/// @brief Full constructor of the PlayerRenderer class.
	/// @param player Pointer on the Player coresponding to this Renderer
	PlayerRenderer::PlayerRenderer(state::Player* player){
		//Creation of the texture
		this->texture =sf::Texture();
		//Set the texture from the image file
		//this->texture.loadFromFile("file");

		//Creation and initialisation of the Sprite
		this->player_Sprite=sf::Sprite();
		(this->player_Sprite).setTexture(this->texture);
	}

	/// @brief Full destructor of the PlayerRenderer class.
	PlayerRenderer::~PlayerRenderer(){

	}
    
	/// @brief Draw of the PlayerRenderer class.
	/// @param window Game window where the Sprite will be displayed
	void PlayerRenderer::draw (sf::RenderWindow* window){

		//draw the Sprite
		window->draw(this->player_Sprite);
	}

};

