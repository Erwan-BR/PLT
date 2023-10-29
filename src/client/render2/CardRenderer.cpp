#include "CardRenderer.h"

namespace render2 {

	/// @brief Empty constructor of the CardRenderer class.
	CardRenderer::CardRenderer(){

	}

	/// @brief Full constructor of the CardRenderer class.
	/// @param path String path to the image file of the Card
	/// @param hor_pos Horizontal position of the Card in pixels
	/// @param ver_pos Vertical position of the Card in pixels
	CardRenderer::CardRenderer(std::string path, int hor_pos, int ver_pos){
		//Creation and Initialisation of card texture
		this->texture =sf::Texture();
		this->texture.loadFromFile(path);

		//Creation and Initialisation of card sprite
		this->card_Sprite=sf::Sprite();
		(this->card_Sprite).setTexture(this->texture);

		//Storage of card's position
		this->horizontal_position = hor_pos;
		this->vertical_position = ver_pos;
	}

	/// @brief Full desctructor of the CardRenderer class.
	CardRenderer::~CardRenderer(){

	}

	/// @brief Display of the CardRenderer class.
	/// @param window Game window where the Sprite will be displayed
	void CardRenderer::draw (sf::RenderWindow* window){
		//Display of the sprite it the window using position
		window->draw(this->card_Sprite,sf::Transform().translate(this->horizontal_position,this->vertical_position));
	}

	/// @brief Change the position of the Card
	/// @param hor_pos Horizontal position of the Card in pixels
	/// @param ver_pos Vertical position of the Card in pixels
	void CardRenderer::changePosition (int hor_pos, int ver_pos){
		this->horizontal_position = hor_pos;	//Horizontal Position
		this->vertical_position = ver_pos;		//Vertical Position
	}

};

