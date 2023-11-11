#include "PlayerRenderer.h"
#include <string>

namespace render {

	/// @brief Empty constructor of the PlayerRenderer class.
	PlayerRenderer::PlayerRenderer(){
		//Enter Player board (position 0)
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile("../resources/img/player.png");
		this->textures.push_back(texture);					//Texture
		sf::Sprite* sprite= new sf::Sprite();
		sprite->setTexture(*(this->textures[0]));
		this->sprites.push_back(sprite);					//Sprite
		this->transforms.push_back(sf::Transform());													//Transform

		//Enter Player Profile Picture (position 1)
		texture = new sf::Texture();
		texture->loadFromFile("../resources/img/default_pfp.png");
		this->textures.push_back(texture);					//Texture
		sprite= new sf::Sprite();
		sprite->setTexture(*(this->textures[1]));
		this->sprites.push_back(sprite);					//Sprite
		this->transforms.push_back(sf::Transform(transforms[0]).translate(20.f,20.f));				//Transform
	}

	/// @brief Current constructor of the PlayerRenderer class.
	PlayerRenderer::PlayerRenderer(sf::Transform transform){
		//Enter Player board (position 0)
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile("../resources/img/player.png");
		this->textures.push_back(texture);					//Texture
		sf::Sprite* sprite= new sf::Sprite();
		sprite->setTexture(*(this->textures[0]));
		this->sprites.push_back(sprite);					//Sprite
		this->transforms.push_back(transform);													//Transform

		//Enter Player Profile Picture (position 1)
		texture = new sf::Texture();
		texture->loadFromFile("../resources/img/default_pfp.png");
		this->textures.push_back(texture);					//Texture
		sprite= new sf::Sprite();
		sprite->setTexture(*(this->textures[1]));
		this->sprites.push_back(sprite);					//Sprite
		this->transforms.push_back(sf::Transform(transforms[0]).translate(20.f,20.f));				//Transform

		//Enter Cards (position 2 to 16)
		int i;
		for (i=0;i<14;i++){
			texture = new sf::Texture();
			texture->loadFromFile("../resources/img/ExampleCards/card"+std::to_string(i%6)+".png");
			this->textures.push_back(texture);	//Texture
			sprite= new sf::Sprite();
			sprite->setTexture(*(this->textures[i+2]));
			this->sprites.push_back(sprite);	//Sprite
			this->transforms.push_back(sf::Transform(transforms[0]).translate(350.f+70.f*(i%7),48.f+127.f*(i/7)).scale(0.2f,0.2f));		//Transform
		}
	}

	/// @brief Full constructor of the PlayerRenderer class.
	/// @param player Pointer on the Player coresponding to this Renderer
	PlayerRenderer::PlayerRenderer(state::Player* player,int index){

	}

	/// @brief Full destructor of the PlayerRenderer class.
	PlayerRenderer::~PlayerRenderer(){

	}
    
	/// @brief Getter Sprite of PlayerRenderer class.
	/// @return The sprite corresponding of the background of the player part.
	sf::Sprite* PlayerRenderer::getSprite(int i){
		return (this->sprites)[i];
	}

	sf::Transform PlayerRenderer::getTransform(int i){
		return (this->transforms)[i];
	}

	int PlayerRenderer::getNumberDrawable(){
		return (this->transforms).size();
	}
};

