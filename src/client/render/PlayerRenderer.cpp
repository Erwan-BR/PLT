#include "PlayerRenderer.h"
#include <string>

namespace render {

	/// @brief Empty constructor of the PlayerRenderer class.
	PlayerRenderer::PlayerRenderer(){
		//Creation of the Font for the Texts
		sf::Font f;
		f.loadFromFile("./resources/font/arial.ttf");
		this->font = f;

		//Enter Player board (position 0)
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile("./resources/img/player.png");
		this->textures.push_back(texture);					//Texture
		sf::Sprite* sprite= new sf::Sprite();
		sprite->setTexture(*(this->textures[0]));
		this->sprites.push_back(sprite);					//Sprite
		this->sprite_transforms.push_back(sf::Transform());		//Transform

		//Enter Player Profile Picture (position 1)
		texture = new sf::Texture();
		texture->loadFromFile("./resources/img/default_pfp.png");
		this->textures.push_back(texture);					//Texture
		sprite= new sf::Sprite();
		sprite->setTexture(*(this->textures[1]));
		this->sprites.push_back(sprite);					//Sprite
		this->sprite_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(20.f,20.f));				//Transform
	}

	/// @brief Full constructor of the PlayerRenderer class.
	/// @param transform indicating the position of the Renderer and passing the scale of the windows.
	/// @param window that will received this PlayerRenderer
	PlayerRenderer::PlayerRenderer(sf::Transform transform,Window window){
		//Creation of the Font for the Texts
		sf::Font f;
		f.loadFromFile("./resources/font/arial.ttf");
		this->font = f;

		int i;
		sf::Texture* texture;
		sf::Sprite* sprite;
		sf::Text* text;

		switch (window){
		case MAIN_WINDOW:
			//Enter Player board (position 0 in sprites)
			texture = new sf::Texture();
			texture->loadFromFile("./resources/img/player.png");
			this->textures.push_back(texture);					//Texture
			sprite= new sf::Sprite();
			sprite->setTexture(*(this->textures[0]));
			this->sprites.push_back(sprite);					//Sprite
			this->sprite_transforms.push_back(transform);				//Transform

			//Enter Player Profile Picture (position 1 in sprites)
			texture = new sf::Texture();
			texture->loadFromFile("./resources/img/default_pfp.png");
			this->textures.push_back(texture);					//Texture
			sprite= new sf::Sprite();
			sprite->setTexture(*(this->textures[1]));
			this->sprites.push_back(sprite);					//Sprite
			this->sprite_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(20.f,20.f));				//Transform

			//Enter Cards (position 2 to 16 in sprites)
			for (i=0;i<14;i++){
				texture = new sf::Texture();
				texture->loadFromFile("./resources/img/DevelopmentCards/image_"+std::to_string(i%78+1)+".png");
				this->textures.push_back(texture);	//Texture
				sprite= new sf::Sprite();
				sprite->setTexture(*(this->textures[i+2]));
				this->sprites.push_back(sprite);	//Sprite
				this->sprite_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(350.f+70.f*(i%7),48.f+127.f*(i/7)).scale(0.2f,0.2f).scale(1.f,(431.f/375.f)));		//Transform
			}

			//Enter Player Name (position 0 in texts)
			text = new sf::Text();
			text->setFont(font);
			text->setString("Nom");
			text->setCharacterSize(30);
			text->setFillColor(sf::Color::White);
			this->texts.push_back(text);			//Text
			this->text_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(140.f,30.0f));		//Transform

			//Enter Resources/Constructions Count (position 1 to 10)
			for (i=0;i<10;i++){
				text = new sf::Text();
				text->setFont(font);
				text->setString("x0");
				text->setCharacterSize(10);
				text->setFillColor(sf::Color::White);
				this->texts.push_back(text);			//Text
				this->text_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(40.f+80.f*(i/5),140.0f+30.0f*(i%5)));	//Transform
			}

			//Enter Victory Point / Token Count (position 11 to 13)
			for (i=0;i<3;i++){
				text = new sf::Text();
				text->setFont(font);
				text->setString("x0");
				text->setCharacterSize(10);
				text->setFillColor(sf::Color::White);
				this->texts.push_back(text);				//Text
				this->text_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(200.0f,140.0f+30.0f*(i)));		//Transform
			}
			break;
		case DRAFTING_WINDOW:
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
			texture->loadFromFile("./resources/img/default_pfp.png");
			this->textures.push_back(texture);					//Texture
			sprite= new sf::Sprite();
			sprite->setTexture(*(this->textures[1]));
			this->sprites.push_back(sprite);					//Sprite
			this->sprite_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(10.f,50.f));				//Transform

			//Enter Cards (position 2 to 9 in sprites)
			for (i=0;i<7;i++){
				texture = new sf::Texture();
				texture->loadFromFile("./resources/img/DevelopmentCards/image_"+std::to_string(i%78+1)+".png");
				this->textures.push_back(texture);	//Texture
				sprite= new sf::Sprite();
				sprite->setTexture(*(this->textures[i+2]));
				this->sprites.push_back(sprite);	//Sprite
				this->sprite_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(350.f+180.f*(i),10.f).scale(0.35f,0.35f).scale(1.f,(431.f/375.f)));		//Transform
			}

			//Enter Player Name (position 0 in texts)
			text = new sf::Text();
			text->setFont(font);
			text->setString("Nom");
			text->setCharacterSize(30);
			text->setFillColor(sf::Color::White);
			this->texts.push_back(text);			//Text
			this->text_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(10.f,10.0f));		//Transform

			break;
		case PLAYER_INFO:
			//Enter Player board (position 0 in sprites)
			texture = new sf::Texture();
			texture->loadFromFile("./resources/img/player_full.png");
			this->textures.push_back(texture);					//Texture
			sprite= new sf::Sprite();
			sprite->setTexture(*(this->textures[0]));
			this->sprites.push_back(sprite);					//Sprite
			this->sprite_transforms.push_back(transform);				//Transform

			//Enter Player Profile Picture (position 1 in sprites)
			texture = new sf::Texture();
			texture->loadFromFile("./resources/img/default_pfp.png");
			this->textures.push_back(texture);					//Texture
			sprite= new sf::Sprite();
			sprite->setTexture(*(this->textures[1]));
			this->sprites.push_back(sprite);					//Sprite
			this->sprite_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(50.f,50.f).scale(2.f,2.f).scale(1.f,(431.f/375.f)));				//Transform

			//Enter Cards (position 2 to 58 in sprites)
			for (i=0;i<56;i++){
				texture = new sf::Texture();
				texture->loadFromFile("./resources/img/DevelopmentCards/image_"+std::to_string(i%78+1)+".png");
				this->textures.push_back(texture);	//Texture
				sprite= new sf::Sprite();
				sprite->setTexture(*(this->textures[i+2]));
				this->sprites.push_back(sprite);	//Sprite
				this->sprite_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(50.f+130.f*(i%14),350.f+160.f*(i/14)+50.f*(i/28)).scale(0.3f,0.3f));		//Transform
			}

			//Enter Player Name (position 0 in texts)
			text = new sf::Text();
			text->setFont(font);
			text->setString("Nom");
			text->setCharacterSize(50);
			text->setFillColor(sf::Color::White);
			this->texts.push_back(text);			//Text
			this->text_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(300.f,50.0f));		//Transform

			//Enter Resources/Constructions Count (position 1 to 10)
			for (i=0;i<10;i++){
				text = new sf::Text();
				text->setFont(font);
				text->setString("x0");
				text->setCharacterSize(50);
				text->setFillColor(sf::Color::White);
				this->texts.push_back(text);			//Text
				this->text_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(350.f+200.f*(i%5),125.0f+75.0f*(i/5)));	//Transform
			}

			//Enter Victory Point / Token Count (position 11 to 13)
			for (i=0;i<3;i++){
				text = new sf::Text();
				text->setFont(font);
				text->setString("x0");
				text->setCharacterSize(50);
				text->setFillColor(sf::Color::White);
				this->texts.push_back(text);				//Text
				this->text_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(1300.0f+200.f*(i),125.0f));		//Transform
			}

			//Enter Information Texts (position 14 to 15)
			text = new sf::Text();
			text->setFont(font);
			text->setString("Cards Built");
			text->setCharacterSize(40);
			text->setFillColor(sf::Color::White);
			this->texts.push_back(text);				//Text
			this->text_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(50.0f,300.f));		//Transform

			text = new sf::Text();
			text->setFont(font);
			text->setString("Cards in construction");
			text->setCharacterSize(40);
			text->setFillColor(sf::Color::White);
			this->texts.push_back(text);				//Text
			this->text_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(50.f,670.f));		//Transform
			break;
		default:
			break;
		}
	}

	/// @brief Full destructor of the PlayerRenderer class.
	PlayerRenderer::~PlayerRenderer(){

	}
    
	/// @brief Getter Sprite of PlayerRenderer class.
	///	@param i the position of the wanted Sprite in the vector
	/// @return The Sprite corresponding
	sf::Sprite* PlayerRenderer::getSprite(int i){
		return (this->sprites)[i];
	}

	/// @brief Getter Transform of PlayerRenderer class.
	///	@param i the position of the wanted transform in the vector
	/// @return The transform corresponding.
	sf::Transform PlayerRenderer::getSpriteTransform(int i){
		return (this->sprite_transforms)[i];
	}

	/// @brief Getter Number of Sprite element in PlayerRenderer class.
	///	@return Number of Sprite element in the vector sprites (same as the numbers of elements in sprite_transforms).
	int PlayerRenderer::getNumberSprite(){
		return (this->sprites).size();
	}

	/// @brief Getter Text of PlayerRenderer class.
	///	@param i the position of the wanted text in the vector
	/// @return The text corresponding
	sf::Text* PlayerRenderer::getText(int i){
		return (this->texts)[i];
	}

	/// @brief Getter Transform of PlayerRenderer class.
	///	@param i the position of the wanted transform in the vector
	/// @return The transform corresponding.
	sf::Transform PlayerRenderer::getTextTransform(int i){
		return (this->text_transforms)[i];
	}

	/// @brief Getter Number of Drawable element in PlayerRenderer class.
	///	@return Number of Drawable element in the vector sprites (same as the numbers of elements in transforms).
	int PlayerRenderer::getNumberText(){
		return (this->texts).size();
	}

	/// @brief Setter Sprite & Texture (position 1 in vector sprites)
	///	@param Name of png file from resource/img without extension
	void PlayerRenderer::changeProfilePicture(std::string path){
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile("./resources/img/"+path+".png");
		this->textures[1] = texture;
		(this->sprites[1])->setTexture(*(this->textures[1]));
	}

	/// @brief Setter Name (position 0 in vector texts)
	///	@param name New name
	void PlayerRenderer::changeName(std::string name){
		//TODO Check name to avoid too long string and/or problems.
		(this->texts[0])->setString(name);
	}

	/// @brief Setter for a numerical value (position 1 to 13 in vector texts)
	///	@param index determines the number to change (from top left (0) to right bottom(12))
	/// @param value New value
	void PlayerRenderer::changeNumbers(int index,int value){
		//TODO Check value to avoid too long string and/or problems.
		if (index<14 and index>=0){
		(this->texts[index+1])->setString("x"+std::to_string(value));
		}
	}
};

