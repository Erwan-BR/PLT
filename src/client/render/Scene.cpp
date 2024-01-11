// Generated by AMillasseau

#include "Scene.h"

#include "../../constants/constants/PlayerObserversNotification.h"

namespace render {

	/// @brief Full constructor of the Scene class.
	/// @param game Game that is displayed.
	/// @param locker Mutex that will lock the action performed by the player.
	/// @param engineOfGame Engine that make the complete game.
	Scene::Scene (std::shared_ptr<state::Game> game, std::mutex & locker, engine::Engine* engineOfGame) :
		game(game),
		locker(locker),
		engineOfGame(engineOfGame)
	{
		this->enableInput = true;
		//Store game attribute
		this->transform = transform;

       	//Creation and initialisation of the background texture
    	this->background_texture =sf::Texture();
    	(this->background_texture).loadFromFile("./resources/img/background.png");

    	//Creation and initialisation of the background sprite
    	this->background=sf::Sprite();
    	(this->background).setTexture(this->background_texture);

    	//Set Starting Window
    	this->current_window = MAIN_WINDOW;

		PlayerRenderer* pRenderer;
		Button* button;
		engine::Command* command;

		//Get Players
		std::vector<std::shared_ptr<state::Player>> players = game->getPlayers();

		//Generate PlayerRenderer for MAIN_WINDOW
		pRenderer = new PlayerRenderer(players[0],{525.f,780.f},MAIN_WINDOW);
    	this->player_renderer.push_back(pRenderer);
		pRenderer = new PlayerRenderer(players[1],{525.f,0.f},MAIN_WINDOW);
    	this->player_renderer.push_back(pRenderer);
		
		//Generate PlayerRenderer for PLAYER_INFO
		pRenderer = new PlayerRenderer(players[0],{0.f,0.f},PLAYER_INFO);
		this->player_renderer.push_back(pRenderer);

		//Generate PlayerRenderer for PLANIFICATION_WINDOW
		pRenderer = new PlayerRenderer(players[0],{0.f,0.f},PLANIFICATION_WINDOW);
		this->player_renderer.push_back(pRenderer);

		//Generate PlayerRenderer for DRAFTING_WINDOW
		for (int i = 0; i<(int) players.size();i++){
    		pRenderer = new PlayerRenderer(players[i],{0.f,720.f-i*180.f},DRAFTING_WINDOW);
			this->player_renderer.push_back(pRenderer);
		}

		//Generate DraftingHandRenederer
		this->drafting_hand_renderer = new DraftingHandRenderer(players[0],{0.f,900.f});

		//Generate GameRenderer
		this->game_renderer = new GameRenderer(game,{0.f,0.f});

		//Generate Buttons for MAIN_WINDOW only if the Player isn't an AI
		if(this->enableInput){
			button = new Button({1650.f,480.f},{100.f,100.f},"MATERIAL",sf::Color(180,180,180),nullptr, this->locker);
			this->btnMain.push_back(button);
			button = new Button({1770.f,480.f},{100.f,100.f},"ENERGY",sf::Color(85,76,68),nullptr, this->locker);
			this->btnMain.push_back(button);
			button = new Button({1650.f,600.f},{100.f,100.f},"SCIENCE",sf::Color::Green,nullptr, this->locker);
			this->btnMain.push_back(button);
			button = new Button({1770.f,600.f},{100.f,100.f},"GOLD",sf::Color::Yellow,nullptr, this->locker);
			this->btnMain.push_back(button);
			button = new Button({1650.f,720.f},{100.f,100.f},"EXPLORATION",sf::Color::Blue,nullptr, this->locker);
			this->btnMain.push_back(button);
			button = new Button({1770.f,720.f},{100.f,100.f},"KRYSTALIUM",sf::Color::Red,nullptr, this->locker);
			this->btnMain.push_back(button);
			button = new Button({1650.f,840.f},{100.f,100.f},"COLONEL",sf::Color::Red,nullptr, this->locker);
			this->btnMain.push_back(button);
			button = new Button({1770.f,840.f},{100.f,100.f},"FINANCIER",sf::Color::Cyan,nullptr, this->locker);
			this->btnMain.push_back(button);

			command = new engine::Command(engine::CONVERTRESOURCE,0,state::MATERIAL);
			button = new Button({50.f,480.f},{100.f,100.f},"CONVERT KRYSTALLIUM\nTO MATERIAL",sf::Color(180,180,180),command, this->locker);
			this->btnMain.push_back(button);
			command = new engine::Command(engine::CONVERTRESOURCE,0,state::ENERGY);
			button = new Button({170.f,480.f},{100.f,100.f},"CONVERT KRYSTALLIUM\nTO ENERGY",sf::Color(85,76,68),command, this->locker);
			this->btnMain.push_back(button);
			command = new engine::Command(engine::CONVERTRESOURCE,0,state::SCIENCE);
			button = new Button({50.f,600.f},{100.f,100.f},"CONVERT KRYSTALLIUM\nTO SCIENCE",sf::Color::Green,command, this->locker);
			this->btnMain.push_back(button);
			command = new engine::Command(engine::CONVERTRESOURCE,0,state::GOLD);
			button = new Button({170.f,600.f},{100.f,100.f},"CONVERT KRYSTALLIUM\nTO GOLD",sf::Color::Yellow,command, this->locker);
			this->btnMain.push_back(button);
			command = new engine::Command(engine::CONVERTRESOURCE,0,state::MATERIAL);
			button = new Button({50.f,720.f},{100.f,100.f},"CONVERT KRYSTALLIUM\nTO EXPLORATION",sf::Color::Blue,command, this->locker);
			this->btnMain.push_back(button);

			command = new engine::Command(engine::CHOOSETOKEN,0,state::COLONEL);
			button = new Button({50.f,840.f},{100.f,100.f},"CHOOSE\nCOLONEL",sf::Color::Red,command, this->locker);
			this->btnMain.push_back(button);
			command = new engine::Command(engine::CHOOSETOKEN,0,state::FINANCIER);
			button = new Button({50.f,840.f},{100.f,100.f},"CHOOSE\nFINANCIER",sf::Color::Cyan,command, this->locker);
			this->btnMain.push_back(button);

			command = new engine::Command(engine::ENDPRODUCTION,0);
			button = new Button({1650.f,960.f},{220.f,100.f},"END PROD",sf::Color(215,47,215),command, this->locker);
			this->btnMain.push_back(button);
			command = new engine::Command(engine::SAVEGAME);
			button = new Button({50.f,960.f},{220.f,100.f},"SAVE GAME",sf::Color(215,47,215),command, this->locker);
			this->btnMain.push_back(button);

			for(int i = 1; i<(int) game->getPlayers().size();i++){
				command = new engine::Command((engine::CommandID) -1,i);
				button = new Button({300.f,60.f*i},{200.f,50.f},"Switch to : "+game->getPlayers()[i]->getName(),sf::Color(215,47,215),command, this->locker);
				this->btnMain.push_back(button);
			}

			button = new Button({20.f,780.f},{220.f,100.f},"KEEP",sf::Color(215,47,215),nullptr, this->locker);
			this->btnPlan.push_back(button);
			button = new Button({260.f,780.f},{220.f,100.f},"DISCARD",sf::Color(215,47,215),nullptr, this->locker);
			this->btnPlan.push_back(button);
			command = new engine::Command(engine::ENDPLANIFICATION,0);
			button = new Button({1680.f,780.f},{220.f,100.f},"END PLAN",sf::Color(215,47,215), command, this->locker);
			this->btnPlan.push_back(button);

			button = new Button({1600.f,940.f},{220.f,100.f},"CONFIRM",sf::Color(215,47,215),nullptr, this->locker);
			this->btnDraft.push_back(button);

			for(int i = 0; i<(int) game->getPlayers().size();i++){
				command = new engine::Command((engine::CommandID) -1,i);
				button = new Button({550.f+220.f*i,50.f},{200.f,50.f},"Switch to : "+game->getPlayers()[i]->getName(),sf::Color(215,47,215),command, this->locker);
				this->btnFull.push_back(button);
			}

			for(Button* btn: this->btnMain){
				btn->setVisible(true);
				btn->setEnabled(true);
			}
			for(Button* btn: this->btnDraft){
				btn->setVisible(true);
				btn->setEnabled(true);
			}
			for(Button* btn: this->btnPlan){
				btn->setVisible(true);
				btn->setEnabled(true);
			}
			for(Button* btn: this->btnFull){
				btn->setVisible(true);
				btn->setEnabled(true);
			}
		}

	}

    /// @brief Full destructor of the Scene class.
    Scene::~Scene ()
	{
		// Delte ongine only, it will delete the game automatically.
		delete engineOfGame;
		delete game_renderer;
		delete drafting_hand_renderer;

		for (PlayerRenderer* playerRenderer: this->player_renderer)
		{
			delete playerRenderer;
		}

		for (Button* button : this->btnMain)
		{
			delete button;
		}

		for (Button* button : this->btnPlan)
		{
			delete button;
		}

		for (Button* button : this->btnFull)
		{
			delete button;
		}

		for (Button* button : this->btnDraft)
		{
			delete button;
		}
    }

	/// @brief Setter for current_window
	/// @param window new window
	void Scene::changeWindow(Window window){
		this->current_window = window;
		switch(this->current_window){
			case MAIN_WINDOW:
				for(int i=0;i<8;i++){
					this->btnMain[i]->changeCommand(nullptr);
				}
				break;
			case DRAFTING_WINDOW:
				this->btnDraft[0]->changeCommand(nullptr);
				break;
			case PLANIFICATION_WINDOW:
				this->btnPlan[0]->changeCommand(nullptr);
				this->btnPlan[1]->changeCommand(nullptr);
				break;
			default:
				break;
		}
	}

	/// @brief Getter for current_window
	/// @return value of current_window
	Window Scene::getWindow(){
		return (this->current_window);
	}

	
	/// @brief Setter for player displayed
	/// @param p_index index of Player to display in players
	/// @param window Window where the info are changed (among MAIN_WINDOW & PLAYER_INFO)
	void Scene::changePlayerInfoPlayer(int p_index,Window window){
		//Get Player to be display
		std::shared_ptr<state::Player> player = game->getPlayers()[p_index];

		int r_id;
		switch(window){
			case MAIN_WINDOW:
				r_id = 1;
				break;
			case PLAYER_INFO:
				r_id = 2;
				break;
			default:
				return;
		}
		//Get Position
		sf::Vector2f pos = this->player_renderer[r_id]->getPos();

		//Create Renderer
		PlayerRenderer* pRenderer = new PlayerRenderer(player,pos,window);

		//Link the renderer (Observer) to its Observable (Game & player) 
		player->addObserver(pRenderer);
		game->addObserver(pRenderer);

		//TODO Destroy previous Renderer?

		//Update the just created Renderer with the current state of the game
		pRenderer->update(0);
		//Put the new Renderer in its place
		this->player_renderer[r_id] = pRenderer;
	}

	void Scene::changePlayerInfoPlayer(int p_index){
		changePlayerInfoPlayer(p_index,this->current_window);
	}

	/// @brief update the Scene with the current state of the game
	void Scene::update(long flags){
		if(PLAYER_CURRENT_RESOURCES_CHANGED & flags){
			btnMain[0]->setText("MATERIAL\n("+std::to_string(this->game->getPlayers()[0]->getCurrentResources()[state::MATERIAL])+")");
			btnMain[1]->setText("ENERGY\n("+std::to_string(this->game->getPlayers()[0]->getCurrentResources()[state::ENERGY])+")");
			btnMain[2]->setText("SCIENCE\n("+std::to_string(this->game->getPlayers()[0]->getCurrentResources()[state::SCIENCE])+")");
			btnMain[3]->setText("GOLD\n("+std::to_string(this->game->getPlayers()[0]->getCurrentResources()[state::GOLD])+")");
			btnMain[4]->setText("EXPLORATION\n("+std::to_string(this->game->getPlayers()[0]->getCurrentResources()[state::EXPLORATION])+")");
			btnMain[5]->setText("KRYSTALLIUM\n("+std::to_string(this->game->getPlayers()[0]->getCurrentResources()[state::KRYSTALLIUM])+")");
			btnMain[6]->setText("COLONEL\n("+std::to_string(this->game->getPlayers()[0]->getCurrentResources()[state::COLONEL])+")");
			btnMain[7]->setText("FINANCIER\n("+std::to_string(this->game->getPlayers()[0]->getCurrentResources()[state::FINANCIER])+")");
		}
	}

	void Scene::buttonHandle(sf::Event event,sf::RenderWindow& window){
		switch (this->current_window){
			case MAIN_WINDOW:
				for(Button* btn: this->btnMain){
					btn->handleEvent(event,window, this->engineOfGame, this);
				}
				this->player_renderer[0]->handleEvent(event,window,this);
				break;
			case DRAFTING_WINDOW:
				for(Button* btn: this->btnDraft){
					btn->handleEvent(event,window, this->engineOfGame, this);
				}
				this->drafting_hand_renderer->handleEvent(event,window,this);
				break;
			case PLANIFICATION_WINDOW:
				for(Button* btn: this->btnPlan){
					btn->handleEvent(event,window, this->engineOfGame, this);
				}
				this->player_renderer[3]->handleEvent(event,window,this);
				break;
			case PLAYER_INFO:
				for(Button* btn: this->btnFull){
					btn->handleEvent(event,window, this->engineOfGame, this);
				}
				break;
			default:
				break;
		}

	}

	void Scene::setSelectedCard(std::shared_ptr<state::Card> card){
		std::shared_ptr<state::Player> p = this->game->getPlayers()[0];
		switch (this->current_window){
			case MAIN_WINDOW:{
				auto cards = p->getToBuildCards();
				engine::Command* command;
				bool skip =false;
				for(int i=0; i < (int) cards.size();i++){
					if(cards[i] == card){
						engine::Command* command;
						command = new engine::Command(engine::ADDRESOURCE,0,i,state::MATERIAL);
						this->btnMain[0]->changeCommand(command);
						command = new engine::Command(engine::ADDRESOURCE,0,i,state::ENERGY);
						this->btnMain[1]->changeCommand(command);
						command = new engine::Command(engine::ADDRESOURCE,0,i,state::SCIENCE);
						this->btnMain[2]->changeCommand(command);
						command = new engine::Command(engine::ADDRESOURCE,0,i,state::GOLD);
						this->btnMain[3]->changeCommand(command);
						command = new engine::Command(engine::ADDRESOURCE,0,i,state::EXPLORATION);
						this->btnMain[4]->changeCommand(command);
						command = new engine::Command(engine::ADDRESOURCE,0,i,state::KRYSTALLIUM);
						this->btnMain[5]->changeCommand(command);
						command = new engine::Command(engine::ADDRESOURCE,0,i,state::COLONEL);
						this->btnMain[6]->changeCommand(command);
						command = new engine::Command(engine::ADDRESOURCE,0,i,state::FINANCIER);
						this->btnMain[7]->changeCommand(command);
						skip = true;
					}
				}
				if(! skip){
					command = new engine::Command(engine::SENDRESOURCETOEMPIRE,0,state::MATERIAL);
					this->btnMain[0]->changeCommand(command);
					command = new engine::Command(engine::SENDRESOURCETOEMPIRE,0,state::MATERIAL);
					this->btnMain[1]->changeCommand(command);
					command = new engine::Command(engine::SENDRESOURCETOEMPIRE,0,state::SCIENCE);
					this->btnMain[2]->changeCommand(command);
					command = new engine::Command(engine::SENDRESOURCETOEMPIRE,0,state::GOLD);
					this->btnMain[3]->changeCommand(command);
					command = new engine::Command(engine::SENDRESOURCETOEMPIRE,0,state::EXPLORATION);
					this->btnMain[4]->changeCommand(command);
					command = new engine::Command(engine::SENDRESOURCETOEMPIRE,0,state::KRYSTALLIUM);
					this->btnMain[5]->changeCommand(command);
					command = new engine::Command(engine::SENDRESOURCETOEMPIRE,0,state::COLONEL);
					this->btnMain[6]->changeCommand(command);
					command = new engine::Command(engine::SENDRESOURCETOEMPIRE,0,state::FINANCIER);
					this->btnMain[7]->changeCommand(command);
				}
				}
				break;
			case DRAFTING_WINDOW:{
				auto cards = p->getDraftingCards();
				for(int i=0; i < (int) cards.size();i++){
					if(cards[i] == card){
						engine::Command* command;
						command = new engine::Command(engine::CHOOSEDRAFTCARD,0,i);
						this->btnDraft[0]->changeCommand(command);
						this->btnDraft[0]->setEnabled(true);
					}
				}
				}
				break;
			case PLANIFICATION_WINDOW:{
				auto cards = p->getDraftCards();
				for(int i=0; i < (int) cards.size();i++){
					if(cards[i] == card){
						engine::Command* command;
						command = new engine::Command(engine::KEEPCARD,0,i);
						this->btnPlan[1]->changeCommand(command);
						command = new engine::Command(engine::DISCARDCARD,0,i);
						this->btnPlan[1]->changeCommand(command);
					}
				}

				cards = p->getToBuildCards();
				for(int i=0; i < (int) cards.size();i++){
					if(cards[i] == card){
						engine::Command* command;
						this->btnPlan[0]->setEnabled(false);
						command = new engine::Command(engine::DISCARDCARD,0,i);
						this->btnPlan[1]->changeCommand(command);
					}
				}
				}
				break;
			default:
				break;
		}
	}

	void Scene::draw(sf::RenderWindow& window){
		switch (this->current_window){
			case MAIN_WINDOW:
				window.draw(this->background);		//Background
				//Display GameRenderer
				this->game_renderer->draw(window);			
				
				//Display players
				this->player_renderer[0]->draw(window);
				this->player_renderer[1]->draw(window);
				
				for (Button* btn: btnMain){
					btn->draw(window);
				}

				break;
			case DRAFTING_WINDOW:
				//Display players
				for (int i=4; i < (int) this->player_renderer.size(); i++){
					this->player_renderer[i]->draw(window);
				}
				//Display Drafting Hand
				this->drafting_hand_renderer->draw(window);

				for (Button* btn: btnDraft){
					btn->draw(window);
				}
				break;
			case PLAYER_INFO:
				//Display Player
				this->player_renderer[2]->draw(window);

				for (Button* btn: btnFull){
					btn->draw(window);
				}
				break;
			case PLANIFICATION_WINDOW:
				window.draw(this->background,this->transform);
				//Display Drafted Hand
				this->player_renderer[3]->draw(window);

				for (Button* btn: btnPlan){
					btn->draw(window);
				}
				break;
			default:
				break;
			}

	}

	void Scene::setupObserver(std::shared_ptr<state::Observable> observable){
		observable->addObserver(this->game_renderer);
		for(PlayerRenderer* pRenderer: player_renderer){
			observable->addObserver(pRenderer);
		}
		observable->addObserver(this->drafting_hand_renderer);
		observable->addObserver(this);
	}
};
