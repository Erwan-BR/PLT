#include "PlayerRenderer.h"
#include <string>
#include <iostream>

#define CARDS_DISPLAY_MAIN_WINDOW 14
#define CARDS_DISPLAY_DRAFTING 7
#define CARDS_DISPLAY_FULL 28

namespace render {
    /// @brief Full constructor of the PlayerRenderer class.
    /// @param transform indicating the position of the Renderer and passing the scale of the windows.
    /// @param window that will received this PlayerRenderer
    PlayerRenderer::PlayerRenderer(std::shared_ptr<state::Player> player,sf::Vector2f position,Window window){
        //Creation of the Font for the Texts
        sf::Font f;
        f.loadFromFile("./resources/font/arial.ttf");
        this->font = f;

        //Store attributes
        this->affected_window = window;
        this->player = player;

        //Initialize vectors
        this->sprites = {};
        this->devCardRenderers = {};
        this->texts = {};

        int i;
        sf::Texture* texture;
        sf::Sprite* sprite;
        sf::Text* text;

        switch (window){
        case MAIN_WINDOW:
            //Enter Player board (position 0 in sprites)
            texture = new sf::Texture();
            texture->loadFromFile("./resources/img/player.png");
            this->textures.push_back(texture);                    //Texture
            sprite= new sf::Sprite();
            sprite->setTexture(*(this->textures[0]));
            sprite->setPosition(position);
            this->sprites.push_back(sprite);                    //Sprite

            // Enter Player Empire Card (position 1 in sprites)
            if (NULL != this->player->getEmpire())
            {
                texture = new sf::Texture();
                texture->loadFromFile(this->player->getEmpire()->getRelativePathToTexture());
                this->textures.push_back(texture);                    //Texture
                sprite= new sf::Sprite();
                sprite->setTexture(*(this->textures[1]));
                sprite->setPosition(position+sf::Vector2f(20.f,20.f));
                sprite->setScale(0.2f,0.2f);
                this->sprites.push_back(sprite);                    //Sprite
            }

            //Enter Player Name (position 0 in texts)
            text = new sf::Text();
            text->setFont(font);
            text->setString(player->getName());
            text->setCharacterSize(30);
            text->setFillColor(sf::Color::White);
            text->setPosition(position+sf::Vector2f(200.f,30.f));
            this->texts.push_back(text);            //Text

            //Enter Resources/Constructions Count (position 1 to 10)
            for (i=0;i<10;i++){
                text = new sf::Text();
                text->setFont(font);
                text->setString("x0");
                text->setCharacterSize(10);
                text->setFillColor(sf::Color::White);
                text->setPosition(position+sf::Vector2f(40.f+80.f*(i/5),140.0f+30.0f*(i%5)));
                this->texts.push_back(text);            //Text
            }

            //Enter Victory Point / Token Count (position 11 to 13)
            for (i=0;i<3;i++){
                text = new sf::Text();
                text->setFont(font);
                text->setString("x0");
                text->setCharacterSize(10);
                text->setFillColor(sf::Color::White);
                text->setPosition(position+sf::Vector2f(200.0f,140.0f+50.0f*(i)));
                this->texts.push_back(text);                //Text
            }
            break;
        case DRAFTING_WINDOW:
            //Enter Player board (position 0 in sprites)
            texture = new sf::Texture();
            texture->loadFromFile("./resources/img/player_draft.png");
            this->textures.push_back(texture);                    //Texture
            sprite= new sf::Sprite();
            sprite->setTexture(*(this->textures[0]));
            sprite->setPosition(position);
            this->sprites.push_back(sprite);                    //Sprite

            // Enter Player Empire Card (position 1 in sprites)
            if (NULL != this->player->getEmpire())
			{
				texture = new sf::Texture();
				texture->loadFromFile(this->player->getEmpire()->getRelativePathToTexture());
				this->textures.push_back(texture);                    //Texture
				sprite= new sf::Sprite();
				sprite->setTexture(*(this->textures[1]));
                sprite->setPosition(position+sf::Vector2f(10.f,50.f));
                sprite->setScale(0.2f,0.2f);
				this->sprites.push_back(sprite);                    //Sprite
			}
            //Enter Player Name (position 0 in texts)
            text = new sf::Text();
            text->setFont(font);
            text->setString(player->getName());
            text->setCharacterSize(30);
            text->setFillColor(sf::Color::White);
            text->setPosition(position+sf::Vector2f(10.f,10.f));
            this->texts.push_back(text);            //Text

            break;
        case PLAYER_INFO:
            //Enter Player board (position 0 in sprites)
            texture = new sf::Texture();
            texture->loadFromFile("./resources/img/player_full.png");
            this->textures.push_back(texture);                    //Texture
            sprite= new sf::Sprite();
            sprite->setTexture(*(this->textures[0]));
            sprite->setPosition(position);
            this->sprites.push_back(sprite);                    //Sprite

            // Enter Player Empire Card (position 1 in sprites)
            if (NULL != this->player->getEmpire())
            {
                texture = new sf::Texture();
                texture->loadFromFile(this->player->getEmpire()->getRelativePathToTexture());
                this->textures.push_back(texture);                    //Texture
                sprite= new sf::Sprite();
                sprite->setTexture(*(this->textures[1]));
                sprite->setPosition(position+sf::Vector2f(50.f,70.f));
                sprite->setScale(0.3f,0.3f);
                this->sprites.push_back(sprite);                    //Sprite
            }
            
            //Enter Player Name (position 0 in texts)
            text = new sf::Text();
            text->setFont(font);
            text->setString(player->getName());
            text->setCharacterSize(50);
            text->setFillColor(sf::Color::White);
            text->setPosition(position+sf::Vector2f(300.f,50.f));
            this->texts.push_back(text);            //Text

            //Enter Resources/Constructions Count (position 1 to 10)
            for (i=0;i<10;i++){
                text = new sf::Text();
                text->setFont(font);
                text->setString("x0");
                text->setCharacterSize(50);
                text->setFillColor(sf::Color::White);
                text->setPosition(position+sf::Vector2f(350.f+200.f*(i%5),125.0f+75.0f*(i/5)));
                this->texts.push_back(text);            //Text
            }

            //Enter Victory Point / Token Count (position 11 to 13)
            for (i=0;i<3;i++){
                text = new sf::Text();
                text->setFont(font);
                text->setString("x0");
                text->setCharacterSize(50);
                text->setFillColor(sf::Color::White);
                text->setPosition(position+sf::Vector2f(1300.0f+200.f*(i),125.0f));
                this->texts.push_back(text);                //Text
            }

            //Enter Krystallium (position 14)
            text = new sf::Text();
            text->setFont(font);
            text->setString("x0+0/5");
            text->setCharacterSize(50);
            text->setFillColor(sf::Color::White);
            text->setPosition(position+sf::Vector2f(1300.0f,200.0f));
            this->texts.push_back(text);                //Text

            //Enter Information Texts (position 15 to 16)
            text = new sf::Text();
            text->setFont(font);
            text->setString("Cards Built");
            text->setCharacterSize(40);
            text->setFillColor(sf::Color::White);
            text->setPosition(position+sf::Vector2f(50.0f,300.f));
            this->texts.push_back(text);                //Text

            text = new sf::Text();
            text->setFont(font);
            text->setString("Cards in construction");
            text->setCharacterSize(40);
            text->setFillColor(sf::Color::White);
            text->setPosition(position+sf::Vector2f(50.f,670.f));
            this->texts.push_back(text);                //Text
            break;
        case PLANIFICATION_WINDOW:
            //Enter Player board (position 0 in sprites)
            texture = new sf::Texture();
            texture->loadFromFile("./resources/img/player_draft.png");
            this->textures.push_back(texture);                    //Texture
            sprite= new sf::Sprite();
            sprite->setTexture(*(this->textures[0]));
            sprite->setPosition(position+sf::Vector2f(0.f,900.f));
            this->sprites.push_back(sprite);                    //Sprite

            //Enter Player Profile Picture (position 1 in sprites)
            texture = new sf::Texture();
            texture->loadFromFile("./resources/img/pfp_draft.png");
            this->textures.push_back(texture);                    //Texture
            sprite= new sf::Sprite();
            sprite->setTexture(*(this->textures[1]));
            sprite->setPosition(position+sf::Vector2f(10.f,950.f));
            this->sprites.push_back(sprite);                    //Sprite

            //Enter Player board (position 2 in sprites)
            texture = new sf::Texture();
            texture->loadFromFile("./resources/img/player.png");
            this->textures.push_back(texture);                    //Texture
            sprite= new sf::Sprite();
            sprite->setTexture(*(this->textures[2]));
            sprite->setScale(2.f,2.f);
            this->sprites.push_back(sprite);                    //Sprite

            // Enter Player Empire Card (position 1 in sprites)
            if (NULL != this->player->getEmpire())
            {
                texture = new sf::Texture();
                texture->loadFromFile(this->player->getEmpire()->getRelativePathToTexture());
                this->textures.push_back(texture);                    //Texture
                sprite= new sf::Sprite();
                sprite->setTexture(*(this->textures[3]));
                sprite->setPosition(position+sf::Vector2f(40.f,40.f));
                sprite->setScale(0.4f,0.4f);
                this->sprites.push_back(sprite);                    //Sprite
            }

            //Enter Player Name (position 0 in texts)
            text = new sf::Text();
            text->setFont(font);
            text->setString(player->getName());
            text->setCharacterSize(60);
            text->setFillColor(sf::Color::White);
            text->setPosition(position+sf::Vector2f(400.f,60.0f));
            this->texts.push_back(text);            //Text

            //Enter Resources/Constructions Count (position 1 to 10)
            for (i=0;i<10;i++){
                text = new sf::Text();
                text->setFont(font);
                text->setString("x0");
                text->setCharacterSize(30);
                text->setFillColor(sf::Color::White);
                text->setPosition(position+sf::Vector2f(80.f+160.f*(i/5),280.0f+60.0f*(i%5)));
                this->texts.push_back(text);            //Text
            }

            //Enter Victory Point / Token Count (position 11 to 13)
            for (i=0;i<3;i++){
                text = new sf::Text();
                text->setFont(font);
                text->setString("x0");
                text->setCharacterSize(30);
                text->setFillColor(sf::Color::White);
                text->setPosition(position+sf::Vector2f(400.0f,280.0f+100.0f*(i)));
                this->texts.push_back(text);                //Text
            }

            //Enter Drafted Hand (position 14 in texts)
            text = new sf::Text();
            text->setFont(font);
            text->setString("Drafted Cards");
            text->setCharacterSize(30);
            text->setFillColor(sf::Color::White);
            text->setPosition(position+sf::Vector2f(10.f,910.f));
            this->texts.push_back(text);            //Text
            break;
        default:
            break;
        }
    }

    /// @brief Full destructor of the PlayerRenderer class.
    PlayerRenderer::~PlayerRenderer(){
        for (sf::Sprite* s : this->sprites){
            delete s;
        }
        for (sf::Text* t : this->texts){
            delete t;
        }
        for (DevelopmentCardRenderer* c : devCardRenderers){
            delete c;
        }
    }

    /// @brief update the Player Renderer with the current state of the game
    void PlayerRenderer::update(long flags)
    {
        DevelopmentCardRenderer* cRenderer;

        //Get Cards
        std::vector<std::shared_ptr<state::DevelopmentCard>> tobuild = this->player->getToBuildCards();
        std::vector<std::shared_ptr<state::DevelopmentCard>> built = this->player->getBuiltCards();
        std::vector<std::shared_ptr<state::DevelopmentCard>> drafted = this->player->getDraftCards();
        int i;
        
        //Initialize vector
        this->devCardRenderers = {};

        switch(this->affected_window){
            case MAIN_WINDOW:
                if(flags & TO_BUILD_CARDS_CHANGED){
                    //Create new Cards
                    for (i=0;i<CARDS_DISPLAY_MAIN_WINDOW and i<(int) tobuild.size();i++){
                        cRenderer = new DevelopmentCardRenderer(tobuild[i],sprites[0]->getPosition()+sf::Vector2f(300.f+100.f*(i%7),0.f+150.f*(i/7)),150.f/375.f);
                        this->devCardRenderers.push_back(cRenderer);    //Card Renderer
                        cRenderer->update(flags);
                    }
                }

                if(flags & RESOURCES_PRODUCTION_PLAYER_CHANGED){
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
                }

                (this->texts)[11]->setString("x"+std::to_string(this->player->computeVictoryPoint()));

                if(flags & CURRENT_RESOURCES_PLAYER_CHANGED){
                    (this->texts)[12]->setString("x"+std::to_string(this->player->getCurrentResources()[state::COLONEL]));
                    (this->texts)[13]->setString("x"+std::to_string(this->player->getCurrentResources()[state::FINANCIER]));
                }
                break;
            case DRAFTING_WINDOW:
                if(flags & DRAFT_CARDS_CHANGED){
                    //Create new cards
                    for (i=0;i<CARDS_DISPLAY_DRAFTING and i<(int) drafted.size();i++){
                        cRenderer = new DevelopmentCardRenderer(drafted[i],sprites[0]->getPosition()+sf::Vector2f(300.f+120.f*(i),0.f),170.f/375.f);
                        this->devCardRenderers.push_back(cRenderer);    //Card Renderer
                        cRenderer->update(flags);
                    }
                }
                break;
            case PLAYER_INFO:
                if(flags & BUILT_CARDS_CHANGED){
                //Create new cards built
                    for (i=0;i<CARDS_DISPLAY_FULL and i<(int) built.size();i++){
                        cRenderer = new DevelopmentCardRenderer(built[i],sprites[0]->getPosition()+sf::Vector2f(50.f+130.f*(i%14),350.f+160.f*(i/14)+50.f*(i/28)),200.f/375.f);
                        this->devCardRenderers.push_back(cRenderer);    //Card Renderer
                        cRenderer->update(flags);
                    }
                }
                if(flags & TO_BUILD_CARDS_CHANGED){
                //Create new cards to build
                    for (i=0;i<CARDS_DISPLAY_FULL and i<(int) tobuild.size();i++){
                        cRenderer = new DevelopmentCardRenderer(tobuild[i],sprites[0]->getPosition()+sf::Vector2f(50.f+130.f*(i%14),720.f+160.f*(i/14)+50.f*(i/28)),200.f/375.f);
                        this->devCardRenderers.push_back(cRenderer);    //Card Renderer
                        cRenderer->update(flags);
                    }
                }
                if(flags & RESOURCES_PRODUCTION_PLAYER_CHANGED){
                    //Update String content
                    (this->texts)[1]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::MATERIAL]));
                    (this->texts)[2]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::ENERGY]));
                    (this->texts)[3]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::SCIENCE]));
                    (this->texts)[4]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::GOLD]));
                    (this->texts)[5]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::EXPLORATION]));
                }
                if(flags & CARDS_TYPE_LIST_CHANGED){
                    (this->texts)[6]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::STRUCTURE]));
                    (this->texts)[7]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::VEHICLE]));
                    (this->texts)[8]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::RESEARCH]));
                    (this->texts)[9]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::PROJECT]));
                    (this->texts)[10]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::DISCOVERY]));
                }
                (this->texts)[11]->setString("x"+std::to_string(this->player->computeVictoryPoint()));
                if(flags & CURRENT_RESOURCES_PLAYER_CHANGED){
                    (this->texts)[12]->setString("x"+std::to_string(this->player->getCurrentResources()[state::COLONEL]));
                    (this->texts)[13]->setString("x"+std::to_string(this->player->getCurrentResources()[state::FINANCIER]));

                    (this->texts)[14]->setString("x"+std::to_string(this->player->getCurrentResources()[state::KRYSTALLIUM])+"+"+std::to_string(this->player->getResourcesInEmpireUnit())+"/5");
                }
                break;
            case PLANIFICATION_WINDOW:
                if(flags & DRAFT_CARDS_CHANGED){
                    //Create new Cards drafted
                    for (i=0;i<CARDS_DISPLAY_DRAFTING and i<(int) drafted.size();i++){
                        cRenderer = new DevelopmentCardRenderer(drafted[i],sprites[0]->getPosition()+sf::Vector2f(350.f+120.f*(i),10.f),170.f/375.f);
                        this->devCardRenderers.push_back(cRenderer);    //Card Renderer
                        cRenderer->update(flags);
                    }
                }
                if(flags & TO_BUILD_CARDS_CHANGED){
                    //Create new Cards to build
                    for (i=0;i<CARDS_DISPLAY_MAIN_WINDOW and i<(int) tobuild.size();i++){
                        cRenderer = new DevelopmentCardRenderer(tobuild[i],sprites[2]->getPosition()+sf::Vector2f(600.f+250.f*(i%7),300.f*(i/7)),300.f/375.f);
                        this->devCardRenderers.push_back(cRenderer);    //Card Renderer
                        cRenderer->update(flags);
                    }
                }

                if(flags & RESOURCES_PRODUCTION_PLAYER_CHANGED){
                    //Update String content
                    (this->texts)[1]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::MATERIAL]));
                    (this->texts)[2]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::ENERGY]));
                    (this->texts)[3]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::SCIENCE]));
                    (this->texts)[4]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::GOLD]));
                    (this->texts)[5]->setString("x"+std::to_string(this->player->getResourcesProduction()[state::EXPLORATION]));
                }
                if(flags & CARDS_TYPE_LIST_CHANGED){
                    (this->texts)[6]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::STRUCTURE]));
                    (this->texts)[7]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::VEHICLE]));
                    (this->texts)[8]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::RESEARCH]));
                    (this->texts)[9]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::PROJECT]));
                    (this->texts)[10]->setString("x"+std::to_string(this->player->getCardsTypeList()[state::DISCOVERY]));
                }
                (this->texts)[11]->setString("x"+std::to_string(this->player->computeVictoryPoint()));
                if(flags & CURRENT_RESOURCES_PLAYER_CHANGED){
                    (this->texts)[12]->setString("x"+std::to_string(this->player->getCurrentResources()[state::COLONEL]));
                    (this->texts)[13]->setString("x"+std::to_string(this->player->getCurrentResources()[state::FINANCIER]));
                }
            default:
                break;
        }
    }

    void PlayerRenderer::draw(sf::RenderWindow& window){
        for(int i=0;i<(int) this->sprites.size();i++){
            window.draw(*(this->sprites[i]));
        }
        for(int i=0;i<(int) this->texts.size();i++){
            window.draw(*(this->texts[i]));
        }
        for(DevelopmentCardRenderer* cRenderer: this->devCardRenderers){
            cRenderer->draw(window);
        }

    }

    void PlayerRenderer::handleEvent (sf::Event event, sf::RenderWindow& window, Scene* scene){
        switch (this->affected_window){
            case MAIN_WINDOW:
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && this->sprites.size()>=1){
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                // Check if the click is inside the Empire Card.
                if (this->sprites[1]->getGlobalBounds().contains(mousePos)){
                    std::cout<<"Empire Clicked"<<std::endl;
                    scene->setSelectedCard(this->player->getEmpire());
                }
            }
            case PLANIFICATION_WINDOW:
				for(DevelopmentCardRenderer* c: this->devCardRenderers){
					c->handleEvent(event,window,scene);
				}
                break;
			case PLAYER_INFO:
            case DRAFTING_WINDOW:
			default:
				break;
        }
        return ;
    }

    sf::Vector2f PlayerRenderer::getPos(){
        return this->sprites[0]->getPosition();
    }
};

