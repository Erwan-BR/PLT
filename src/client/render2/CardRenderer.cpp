#include "CardRenderer.h"

namespace render2 {

	/// @brief Empty constructor of the CardRenderer class.
	CardRenderer::CardRenderer(){

	}

	/// @brief Full constructor of the CardRenderer class.
	/// @param path String path to the image file of the Card
	/// @param hor_pos Horizontal position of the Card in pixels
	/// @param ver_pos Vertical position of the Card in pixels
	CardRenderer::CardRenderer(std::string path){
		//Creation and Initialisation of card texture
		this->texture =sf::Texture();
		this->texture.loadFromFile(path);

		//Creation and Initialisation of card sprite
		this->card_Sprite=sf::Sprite();
		(this->card_Sprite).setTexture(this->texture);
	}

	/// @brief Full desctructor of the CardRenderer class.
	CardRenderer::~CardRenderer(){

	}

	/// @brief Getter Sprite of Card class
	/// @return The sprite corresponding to the Card.
	sf::Sprite CardRenderer::getSprite (){
		return (this->card_Sprite);
	}
};

