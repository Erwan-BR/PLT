// Generated by AMillasseau


#include "Scene.h"

namespace render {

	/// @brief Full constructor of the Scene class.
    Scene::Scene(state::Game* game,sf::Transform transform){
		this->game = game;

       	//Creation and initialisation of the background texture
    	this->background_texture =sf::Texture();
    	(this->background_texture).loadFromFile("./resources/img/background.png");

    	//Creation and initialisation of the background sprite
    	this->background=sf::Sprite();
    	(this->background).setTexture(this->background_texture);

    	//Set Starting Window
    	this->current_window = MAIN_WINDOW;

		PlayerRenderer* pRenderer;

		std::vector<state::Player*> players = game->getPlayers();
		for (int i = 0; i<(int) players.size();i++){
			pRenderer = new PlayerRenderer(players[i],generatePlayerTransform(transform,MAIN_WINDOW,i),MAIN_WINDOW);
    		this->player_renderer.push_back(pRenderer);
		}
		for (int i = 0; i<(int) players.size();i++){
    		pRenderer = new PlayerRenderer(players[i],generatePlayerTransform(transform,DRAFTING_WINDOW,i),DRAFTING_WINDOW);
			this->player_renderer.push_back(pRenderer);
		}
		pRenderer = new PlayerRenderer(game->getPlayers()[0],transform,PLAYER_INFO);
		this->player_renderer.push_back(pRenderer);
		pRenderer = new PlayerRenderer(game->getPlayers()[0],generatePlayerTransform(transform,PLANIFICATION_WINDOW,0).translate(0.f,900.f),PLANIFICATION_WINDOW);
		this->player_renderer.push_back(pRenderer);

		this->drafting_hand_renderer = new DraftingHandRenderer((game->getPlayers())[0],sf::Transform(transform).translate(0.f,900.f));

		this->game_renderer = new GameRenderer(game,transform);
	}

    /// @brief Full destructor of the Scene class.
    Scene::~Scene (){

    }

    /// @brief Getter of the background sprite.
    /// @return The sprite corresponding of the background of the scene
    sf::Sprite Scene::getBackground (){
    	return (this->background);
    }

    /// @brief Getter of the player renderer.
    /// @param index corresponding of the wanted player renderer in the vector player_renderer
	/// @return The player renderer corresponding of the index.
	PlayerRenderer* Scene::getPlayerRenderer (int i){
		return (this->player_renderer)[i];
	}

	int Scene::getNumberPlayerRenderer(){
		return (this->player_renderer).size();
	}

	GameRenderer* Scene::getGameRenderer(){
		return this->game_renderer;
	}

	DraftingHandRenderer* Scene::getHandRenderer(){
		return this->drafting_hand_renderer;
	}

	/// @brief Setter for current_window
	/// @param window new window
	void Scene::changeWindow(Window window){
		this->current_window = window;
	}

	/// @brief Getter for current_window
	/// @return value of current_window
	Window Scene::getWindow(){
		return (this->current_window);
	}

	void Scene::changePlayerInfoPlayer(int index,sf::Transform transform){
		state::Player* player = game->getPlayers()[index];
		PlayerRenderer* pRenderer = new PlayerRenderer(player,transform,PLAYER_INFO);
		player->addObserver(pRenderer);
		//TODO Destroy previous Renderer?
		this->player_renderer[4] = pRenderer;
	}

	sf::Transform Scene::generatePlayerTransform(sf::Transform transform, Window window, int indice){
		if (window == MAIN_WINDOW){
			if (indice == 0){
				return sf::Transform(transform).translate(525.f,780.f);
			}
			else {
				return sf::Transform(transform).translate(525.f,0.f);
				//TODO See for indice>2
			}
		}
		if (window == DRAFTING_WINDOW){
			if (indice == 0){
				return sf::Transform(transform).translate(0.f,720.f);
			}
			else {
				return sf::Transform(transform).translate(0.f,(indice-1)*180.f);
			}
		if (window == PLANIFICATION_WINDOW){
			return sf::Transform(transform).translate(0.f,720.f);
		}
		}
	return sf::Transform(transform);
	}

	void Scene::update(){
		this->game_renderer->update();
		this->drafting_hand_renderer->update();
		for(PlayerRenderer* pRend:this->player_renderer){
			pRend->update();
		}
	}
};
