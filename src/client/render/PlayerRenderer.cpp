#include "PlayerRenderer.h"
#include <string>

#define CARDS_DISPLAY_MAIN_WINDOW 14
#define CARDS_DISPLAY_DRAFTING 7
#define CARDS_DISPLAY_FULL 28

namespace render {
	/// @brief Full constructor of the PlayerRenderer class.
	/// @param transform indicating the position of the Renderer and passing the scale of the windows.
	/// @param window that will received this PlayerRenderer
	PlayerRenderer::PlayerRenderer(state::Player* player,sf::Transform transform,Window window){
		//Creation of the Font for the Texts
		sf::Font f;
		f.loadFromFile("./resources/font/arial.ttf");
		this->font = f;

		//Store attributes
		this->affected_window = window;
		this->player = player;

		//Initialize vectors
		this->sprites = {};
		this->sprite_transforms = {};
		this->devCardRenderers = {};
		this->texts = {};
		this->text_transforms = {};

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
			texture = player->getProfilePicture();
			this->textures.push_back(texture);					//Texture
			sprite= new sf::Sprite();
			sprite->setTexture(*(this->textures[1]));
			this->sprites.push_back(sprite);					//Sprite
			this->sprite_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(20.f,20.f));				//Transform

			//Enter Player Name (position 0 in texts)
			text = new sf::Text();
			text->setFont(font);
			text->setString(player->getName());
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
				this->text_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(200.0f,140.0f+50.0f*(i)));		//Transform
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
			texture = player->getProfilePicture();
			this->textures.push_back(texture);					//Texture
			sprite= new sf::Sprite();
			sprite->setTexture(*(this->textures[1]));
			this->sprites.push_back(sprite);					//Sprite
			this->sprite_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(10.f,50.f));				//Transform

			//Enter Player Name (position 0 in texts)
			text = new sf::Text();
			text->setFont(font);
			text->setString(player->getName());
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
			texture = player->getProfilePicture();
			this->textures.push_back(texture);					//Texture
			sprite= new sf::Sprite();
			sprite->setTexture(*(this->textures[1]));
			this->sprites.push_back(sprite);					//Sprite
			this->sprite_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(50.f,50.f).scale(2.f,2.f).scale(1.f,(431.f/375.f)));				//Transform

			//Enter Player Name (position 0 in texts)
			text = new sf::Text();
			text->setFont(font);
			text->setString(player->getName());
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

			//Enter Krystallium (position 14)
			text = new sf::Text();
			text->setFont(font);
			text->setString("x0+0/5");
			text->setCharacterSize(50);
			text->setFillColor(sf::Color::White);
			this->texts.push_back(text);				//Text
			this->text_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(1300.0f,200.0f));		//Transform

			//Enter Information Texts (position 15 to 16)
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
		case PLANIFICATION_WINDOW:
			//Enter Player board (position 0 in sprites)
			texture = new sf::Texture();
			texture->loadFromFile("./resources/img/player_draft.png");
			this->textures.push_back(texture);					//Texture
			sprite= new sf::Sprite();
			sprite->setTexture(*(this->textures[0]));
			this->sprites.push_back(sprite);					//Sprite
			this->sprite_transforms.push_back(sf::Transform(transform).translate(0.f,900.f));				//Transform

			//Enter Player Profile Picture (position 1 in sprites)
			texture = new sf::Texture();
			texture->loadFromFile("./resources/img/pfp_draft.png");
			this->textures.push_back(texture);					//Texture
			sprite= new sf::Sprite();
			sprite->setTexture(*(this->textures[1]));
			this->sprites.push_back(sprite);					//Sprite
			this->sprite_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(10.f,50.f));				//Transform

			//Enter Player board (position 2 in sprites)
			texture = new sf::Texture();
			texture->loadFromFile("./resources/img/player.png");
			this->textures.push_back(texture);					//Texture
			sprite= new sf::Sprite();
			sprite->setTexture(*(this->textures[2]));
			this->sprites.push_back(sprite);					//Sprite
			this->sprite_transforms.push_back(sf::Transform(transform).scale(2.f,2.f));				//Transform

			//Enter Player Profile Picture (position 3 in sprites)
			texture = player->getProfilePicture();
			this->textures.push_back(texture);					//Texture
			sprite= new sf::Sprite();
			sprite->setTexture(*(this->textures[3]));
			this->sprites.push_back(sprite);					//Sprite
			this->sprite_transforms.push_back(sf::Transform(sprite_transforms[2]).translate(20.f,20.f));				//Transform

			//Enter Player Name (position 0 in texts)
			text = new sf::Text();
			text->setFont(font);
			text->setString(player->getName());
			text->setCharacterSize(30);
			text->setFillColor(sf::Color::White);
			this->texts.push_back(text);			//Text
			this->text_transforms.push_back(sf::Transform(sprite_transforms[2]).translate(140.f,30.0f));		//Transform

			//Enter Resources/Constructions Count (position 1 to 10)
			for (i=0;i<10;i++){
				text = new sf::Text();
				text->setFont(font);
				text->setString("x0");
				text->setCharacterSize(10);
				text->setFillColor(sf::Color::White);
				this->texts.push_back(text);			//Text
				this->text_transforms.push_back(sf::Transform(sprite_transforms[2]).translate(40.f+80.f*(i/5),140.0f+30.0f*(i%5)));	//Transform
			}

			//Enter Victory Point / Token Count (position 11 to 13)
			for (i=0;i<3;i++){
				text = new sf::Text();
				text->setFont(font);
				text->setString("x0");
				text->setCharacterSize(10);
				text->setFillColor(sf::Color::White);
				this->texts.push_back(text);				//Text
				this->text_transforms.push_back(sf::Transform(sprite_transforms[2]).translate(200.0f,140.0f+50.0f*(i)));		//Transform
			}

			//Enter Drafted Hand (position 14 in texts)
			text = new sf::Text();
			text->setFont(font);
			text->setString("Drafted Cards");
			text->setCharacterSize(30);
			text->setFillColor(sf::Color::White);
			this->texts.push_back(text);			//Text
			this->text_transforms.push_back(sf::Transform(sprite_transforms[0]).translate(10.f,10.0f));		//Transform
			break;
		default:
			break;
		}
	}

	/// @brief Full destructor of the PlayerRenderer class.
	PlayerRenderer::~PlayerRenderer(){
		for (sf::Sprite* s : this->sprites){
			free(s);
		}
		for (sf::Text* t : this->texts){
			free(t);
		}
		for (DevelopmentCardRenderer* c : devCardRenderers){
			free(c);
		}
	}

	/// @brief update the Player Renderer with the current state of the game
	void PlayerRenderer::update()
	{
		DevelopmentCardRenderer* cRenderer;

		//Get Cards
		std::vector<state::DevelopmentCard*> tobuild = this->player->getToBuildCards();
		std::vector<state::DevelopmentCard*> built = this->player->getBuiltCards();
		std::vector<state::DevelopmentCard*> drafted = this->player->getDraftCards();
		int i;
		
		//Initialize vector
		this->devCardRenderers = {};

		switch(this->affected_window){
			case MAIN_WINDOW:
				//Create new Cards
				for (i=0;i<CARDS_DISPLAY_MAIN_WINDOW and i<(int) tobuild.size();i++){
					cRenderer = new DevelopmentCardRenderer(tobuild[i],sf::Transform(sprite_transforms[0]).translate(300.f+100.f*(i%7),0.f+150.f*(i/7)),150.f/375.f);
					this->devCardRenderers.push_back(cRenderer);	//Card Renderer
				}

				//Update String content
				(this->texts)[1]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::MATERIAL]));
				(this->texts)[2]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::ENERGY]));
				(this->texts)[3]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::SCIENCE]));
				(this->texts)[4]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::GOLD]));
				(this->texts)[5]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::EXPLORATION]));

				(this->texts)[6]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::STRUCTURE]));
				(this->texts)[7]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::VEHICLE]));
				(this->texts)[8]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::RESEARCH]));
				(this->texts)[9]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::PROJECT]));
				(this->texts)[10]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::DISCOVERY]));

				(this->texts)[11]->setString("x"+std::to_string(this->player->computeVictoryPoint()));
				(this->texts)[12]->setString("x"+std::to_string(this->player->getCurrentResources()[state::COLONEL]));
				(this->texts)[13]->setString("x"+std::to_string(this->player->getCurrentResources()[state::FINANCIER]));
				break;
			case DRAFTING_WINDOW:
				//Create new cards
				for (i=0;i<CARDS_DISPLAY_DRAFTING and i<(int) drafted.size();i++){
					cRenderer = new DevelopmentCardRenderer(drafted[i],sf::Transform(sprite_transforms[0]).translate(300.f+120.f*(i),0.f),170.f/375.f);
					this->devCardRenderers.push_back(cRenderer);	//Card Renderer
				}
				break;
			case PLAYER_INFO:
				//Create new cards built
				for (i=0;i<CARDS_DISPLAY_FULL and i<(int) built.size();i++){
					cRenderer = new DevelopmentCardRenderer(built[i],sf::Transform(sprite_transforms[0]).translate(50.f+130.f*(i%14),350.f+160.f*(i/14)+50.f*(i/28)),200.f/375.f);
					this->devCardRenderers.push_back(cRenderer);	//Card Renderer
				}
				//Create new cards to build
				for (i=0;i<CARDS_DISPLAY_FULL and i<(int) tobuild.size();i++){
					cRenderer = new DevelopmentCardRenderer(tobuild[i],sf::Transform(sprite_transforms[0]).translate(50.f+130.f*(i%14),720.f+160.f*(i/14)+50.f*(i/28)),200.f/375.f);
					this->devCardRenderers.push_back(cRenderer);	//Card Renderer
				}
				//Update String content
				(this->texts)[1]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::MATERIAL]));
				(this->texts)[2]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::ENERGY]));
				(this->texts)[3]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::SCIENCE]));
				(this->texts)[4]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::GOLD]));
				(this->texts)[5]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::EXPLORATION]));

				(this->texts)[6]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::STRUCTURE]));
				(this->texts)[7]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::VEHICLE]));
				(this->texts)[8]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::RESEARCH]));
				(this->texts)[9]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::PROJECT]));
				(this->texts)[10]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::DISCOVERY]));

				(this->texts)[11]->setString("x"+std::to_string(this->player->computeVictoryPoint()));
				(this->texts)[12]->setString("x"+std::to_string(this->player->getCurrentResources()[state::COLONEL]));
				(this->texts)[13]->setString("x"+std::to_string(this->player->getCurrentResources()[state::FINANCIER]));

				(this->texts)[14]->setString("x"+std::to_string(this->player->getCurrentResources()[state::KRYSTALLIUM])+"+"+std::to_string(this->player->getResourcesInEmpireUnit())+"/5");

				break;
			case PLANIFICATION_WINDOW:
				//Create new Cards drafted
				for (i=0;i<CARDS_DISPLAY_DRAFTING and i<(int) drafted.size();i++){
				cRenderer = new DevelopmentCardRenderer(drafted[i],sf::Transform(sprite_transforms[0]).translate(350.f+120.f*(i),10.f),170.f/375.f);
				this->devCardRenderers.push_back(cRenderer);	//Card Renderer
				}

				//Create new Cards to build
				for (i=0;i<CARDS_DISPLAY_MAIN_WINDOW and i<(int) tobuild.size();i++){
				cRenderer = new DevelopmentCardRenderer(tobuild[i],sf::Transform(sprite_transforms[2]).translate(350.f+70.f*(i%7),48.f+127.f*(i/7)).scale(0.2f,0.2f).scale(1.f,(431.f/375.f)),300.f/375.f);
				this->devCardRenderers.push_back(cRenderer);	//Card Renderer
				}

				(this->texts)[1]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::MATERIAL]));
				(this->texts)[2]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::ENERGY]));
				(this->texts)[3]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::SCIENCE]));
				(this->texts)[4]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::GOLD]));
				(this->texts)[5]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::EXPLORATION]));

				(this->texts)[6]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::STRUCTURE]));
				(this->texts)[7]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::VEHICLE]));
				(this->texts)[8]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::RESEARCH]));
				(this->texts)[9]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::PROJECT]));
				(this->texts)[10]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::DISCOVERY]));

				(this->texts)[11]->setString("x"+std::to_string(this->player->computeVictoryPoint()));
				(this->texts)[12]->setString("x"+std::to_string(this->player->getCurrentResources()[state::COLONEL]));
				(this->texts)[13]->setString("x"+std::to_string(this->player->getCurrentResources()[state::FINANCIER]));
			
			default:
				break;
		}

		//Update Cards
		for(i=0; i<(int) this->devCardRenderers.size();i++){
			(this->devCardRenderers[i])->update();
		}

	}

	void PlayerRenderer::draw(sf::RenderWindow& window){
		for(int i=0;i<(int) this->sprites.size();i++){
			window.draw(*(this->sprites[i]),(this->sprite_transforms[i]));
		}
		for(int i=0;i<(int) this->texts.size();i++){
			window.draw(*(this->texts[i]),(this->text_transforms[i]));
		}
		for(DevelopmentCardRenderer* cRenderer: this->devCardRenderers){
			cRenderer->draw(window);
		}

	}

	sf::Transform PlayerRenderer::getPos(){
		return this->sprite_transforms[0];
	}
};

