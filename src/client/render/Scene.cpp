// Generated by AMillasseau

#include "Scene.h"

#include "../../constants/constants/PlayerObserversNotification.h"
#include "../../constants/constants/GameObserversNotification.h"

namespace render {

    /// @brief Full constructor of the Scene class.
    /// @param game Game that is displayed.
    /// @param locker Mutex that will lock the action performed by the player.
    /// @param engineOfGame Engine that make the complete game.
    Scene::Scene (std::shared_ptr<state::Game> game, std::mutex & locker, constants::enginePtr engineOfGame) :
        background_texture(constants::ResourceManager::getTexture("./resources/img/background.png")),
        game(game),
        locker(locker),
        engineOfGame(engineOfGame)
    {
        // Initialisation of the background sprite
        this->background.setTexture(this->background_texture);

        PlayerRenderer* pRenderer;

        //Get Players
        constants::playersList players = game->getPlayers();

        //Generate PlayerRenderer for MAIN_WINDOW
        pRenderer = new PlayerRenderer(players[this->playerIndex],{525.f,780.f},MAIN_WINDOW);
        this->player_renderer.push_back(pRenderer);
        pRenderer = new PlayerRenderer(players[1],{525.f,0.f},MAIN_WINDOW);
        this->player_renderer.push_back(pRenderer);
        
        //Generate PlayerRenderer for PLAYER_INFO
        pRenderer = new PlayerRenderer(players[this->playerIndex],{0.f,0.f},PLAYER_INFO);
        this->player_renderer.push_back(pRenderer);

        //Generate PlayerRenderer for PLANIFICATION_WINDOW
        pRenderer = new PlayerRenderer(players[this->playerIndex],{0.f,0.f},PLANIFICATION_WINDOW);
        this->player_renderer.push_back(pRenderer);

        //Generate PlayerRenderer for DRAFTING_WINDOW
        for (size_t i = 0; players.size() > i; i++)
        {
            pRenderer = new PlayerRenderer(players[i],{0.f,720.f-i*180.f},DRAFTING_WINDOW);
            this->player_renderer.push_back(pRenderer);
        }

        //Generate DraftingHandRenederer
        this->drafting_hand_renderer = new DraftingHandRenderer(players[this->playerIndex],{0.f,900.f});

        //Generate GameRenderer
        this->game_renderer = new GameRenderer(game,{0.f,0.f});

        //Generate Buttons for MAIN_WINDOW only if the Player isn't an AI
        if(this->enableInput)
        {
            constants::buttonPtr button;
            constants::commandPtr command;

            sf::Vector2f sizeOfSmallButtons = {100.f,100.f};
            sf::Vector2f sizeOfBigButtons = {220.f,100.f};

            // Create vector for buttons
            const std::vector<std::string> nameOfResources                   = {"MATERIAL", "ENERGY", "SCIENCE", "GOLD", "EXPLORATION", "KRYSTALLIUM", "COLONEL", "FINANCIER"};
            const std::vector<state::ResourceType> resourcesType             = {state::MATERIAL, state::ENERGY, state::SCIENCE, state::GOLD, state::EXPLORATION, state::COLONEL, state::FINANCIER};
            const std::vector<sf::Color> colorsOfButtons                     = {sf::Color(180,180,180), sf::Color(85,76,68), sf::Color::Green, sf::Color::Yellow, sf::Color::Blue, sf::Color::Red, sf::Color::Red, sf::Color::Cyan};
            const std::vector<sf::Vector2f> coordinatesButtonsUseResource    = {{1650.f,480.f}, {1770.f,480.f}, {1650.f,600.f}, {1770.f,600.f}, {1650.f,720.f}, {1770.f,720.f}, {1650.f,840.f}, {1770.f,840.f}};
            const std::vector<sf::Vector2f> coordinatesButtonsConvert        = {{50.f,480.f}, {170.f,480.f}, {50.f,600.f}, {170.f,600.f}, {50.f,720.f}};
            const std::vector<sf::Vector2f> coordinatesButtonsPreferredPerso = {{50.f,840.f}, {170.f,840.f}};

            // Buttons to place a resource on a card or to send it to the empire
            for (size_t index = 0; coordinatesButtonsUseResource.size() > index; index++)
            {
                button = constants::buttonPtr(new Button(coordinatesButtonsUseResource[index], sizeOfSmallButtons, nameOfResources[index], colorsOfButtons[index], nullptr, this->locker));
                this->btnMain.push_back(button);
            }

            // Buttons to convert a ressource into another one.
            for (size_t index = 0; coordinatesButtonsConvert.size() > index; index++)
            {
                command = constants::commandPtr(new engine::Command(engine::CONVERTRESOURCE, this->playerIndex, resourcesType[index]));
                button = constants::buttonPtr(new Button(coordinatesButtonsConvert[index], sizeOfSmallButtons, "CONVERT\n" + nameOfResources[index] + "\nTO MATERIAL", colorsOfButtons[index], command, this->locker));
                this->btnMain.push_back(button);
            }

            // Buttons to choose the preffered personnage.
            for (size_t index = 0; coordinatesButtonsPreferredPerso.size() > index; index++)
            {
                int indexWithOffset = index + 6;
                
                command = constants::commandPtr(new engine::Command(engine::SETPREFFEREDPERSONNAGE,this->playerIndex, resourcesType[indexWithOffset]));
                button = constants::buttonPtr(new Button(coordinatesButtonsPreferredPerso[index], sizeOfSmallButtons, "CHOOSE\n" + nameOfResources[indexWithOffset], colorsOfButtons[indexWithOffset], command, this->locker));
                this->btnMain.push_back(button);
            }

            // End production button
            command = constants::commandPtr(new engine::Command(engine::ENDPRODUCTION, this->playerIndex));
            button = constants::buttonPtr(new Button({1650.f,960.f}, sizeOfBigButtons, "END PROD", sf::Color(215,47,215), command, this->locker));
            this->btnMain.push_back(button);

            // Save game button
            command = constants::commandPtr(new engine::Command(engine::SAVEGAME));
            button = constants::buttonPtr(new Button({50.f,960.f}, sizeOfBigButtons, "SAVE GAME", sf::Color(215,47,215), command, this->locker));
            this->btnMain.push_back(button);

            // Buttons to switch the small view at the top of the main window.
            for(size_t i = 1; game->getPlayers().size() > i; i++)
            {
                command = constants::commandPtr(new engine::Command((engine::CommandID) -1,this->playerIndex));
                button = constants::buttonPtr(new Button({300.f,60.f*i},{200.f,50.f},"Switch to : "+game->getPlayers()[i]->getName(),sf::Color(215,47,215),command, this->locker));
                this->btnMain.push_back(button);
            }


            button = constants::buttonPtr(new Button({20.f,780.f}, sizeOfBigButtons,"KEEP", sf::Color(215,47,215), nullptr, this->locker));
            this->btnPlan.push_back(button);

            button = constants::buttonPtr(new Button({260.f,780.f}, sizeOfBigButtons, "DISCARD", sf::Color(215,47,215), nullptr, this->locker));
            this->btnPlan.push_back(button);

            command = constants::commandPtr(new engine::Command(engine::ENDPLANIFICATION, this->playerIndex));
            button = constants::buttonPtr(new Button({1680.f,780.f}, sizeOfBigButtons, "END PLAN", sf::Color(215,47,215), command, this->locker));
            this->btnPlan.push_back(button);

            button = constants::buttonPtr(new Button({1600.f,940.f}, sizeOfBigButtons, "CONFIRM", sf::Color(215,47,215), nullptr, this->locker));
            this->btnDraft.push_back(button);

            for(size_t i = 0; game->getPlayers().size() > i; i++)
            {
                command = constants::commandPtr(new engine::Command((engine::CommandID) -1,i));
                button = constants::buttonPtr(new Button({550.f+220.f*i, 50.f}, {200.f, 50.f}, "Switch to : " + game->getPlayers()[i]->getName(), sf::Color(215,47,215), command, this->locker));
                this->btnFull.push_back(button);
            }

            for(constants::buttonPtr btn: this->btnMain)
            {
                btn->setVisible(true);
                btn->setEnabled(true);
            }
            for(constants::buttonPtr btn: this->btnDraft)
            {
                btn->setVisible(true);
                btn->setEnabled(true);
            }
            for(constants::buttonPtr btn: this->btnPlan)
            {
                btn->setVisible(true);
                btn->setEnabled(true);
            }
            for(constants::buttonPtr btn: this->btnFull)
            {
                btn->setVisible(true);
                btn->setEnabled(true);
            }
        }

    }

    /// @brief Full destructor of the Scene class.
    Scene::~Scene ()
    {
    }

    /// @brief Setter for current_window
    /// @param window new window
    void Scene::changeWindow(Window window)
    {
        this->current_window = window;
        switch(this->current_window)
        {
            case MAIN_WINDOW:
            {
                for(int i = 0; i < 8; i++)
                {
                    this->btnMain[i]->changeCommand(nullptr);
                }
                break;
            }
                
            case DRAFTING_WINDOW:
            {
                this->btnDraft[0]->changeCommand(nullptr);
                break;
            }
                
            case PLANIFICATION_WINDOW:
            {
                this->btnPlan[0]->changeCommand(nullptr);
                this->btnPlan[1]->changeCommand(nullptr);
                break;
            }
                
            default:
            {
                break;
            }
        }
    }

    /// @brief Getter for current_window
    /// @return value of current_window
    Window Scene::getWindow()
    {
        return this->current_window;
    }
    
    /// @brief Setter for player displayed
    /// @param p_index index of Player to display in players
    /// @param window Window where the info are changed (among MAIN_WINDOW & PLAYER_INFO)
    void Scene::changePlayerInfoPlayer(int p_index,Window window)
    {
        // Get Player to be display
        constants::playerPtr player = game->getPlayers()[p_index];

        int r_id;
        switch(window)
        {
            case MAIN_WINDOW:
            {
                r_id = 1;
                break;
            }
            case PLAYER_INFO:
            {
                r_id = 2;
                break;
            }
            default:
            {
                return;
            }
        }
        // Get Position
        sf::Vector2f pos = this->player_renderer[r_id]->getPos();

        // Create Renderer
        PlayerRenderer* pRenderer = new PlayerRenderer(player,pos,window);

        // Link the renderer (Observer) to its Observable (Game & player) 
        player->addObserver(pRenderer);
        game->addObserver(pRenderer);

        // Update the just created Renderer with the current state of the game
        pRenderer->update(PLAYER_RESOURCES_PRODUCTION_CHANGED | CARDS_TYPE_LIST_CHANGED |TO_BUILD_CARDS_CHANGED | BUILT_CARDS_CHANGED | PLAYER_CURRENT_RESOURCES_CHANGED);
        
        // Put the new Renderer in its place
        this->player_renderer[r_id] = pRenderer;
    }

    void Scene::changePlayerInfoPlayer(int p_index)
    {
        changePlayerInfoPlayer(p_index,this->current_window);
    }

    /// @brief update the Scene with the current state of the game
    /// @param flags Flags that indicate what should be refreshed.
    void Scene::update(long flags)
    {
        if(PLAYER_CURRENT_RESOURCES_CHANGED & flags)
        {
            std::vector<std::string> nameOfResources = {"MATERIAL\n(", "ENERGY\n(", "SCIENCE\n(", "GOLD\n(", "EXPLORATION\n(", "KRYSTALLIUM\n(", "COLONEL\n(", "FINANCIER\n("};
            std::vector<state::ResourceType> resources = {state::MATERIAL, state::ENERGY, state::SCIENCE, state::GOLD, state::EXPLORATION, state::KRYSTALLIUM, state::COLONEL, state::FINANCIER};

            for (size_t index = 0; nameOfResources.size() > index; index++)
            {
                std::string numberOfRessources = std::to_string(this->game->getPlayers()[this->playerIndex]->getCurrentResources()[resources[index]]);
                btnMain[index]->setText(nameOfResources[index] + numberOfRessources + ")");
            }
        }
        if(GAME_PHASE_CHANGED & flags)
        {
            switch(game->getPhase())
            {
                case state::PRODUCTION:
                {
                    btnMain[15]->setEnabled(true);
                    btnPlan[2]->setEnabled(false);
                    break;
                }
                case state::PLANIFICATION:
                {    
                    btnMain[15]->setEnabled(false);
                    btnPlan[2]->setEnabled(true);
                    break;
                }
                default:
                {
                    btnMain[15]->setEnabled(false);
                    btnPlan[2]->setEnabled(false);
                    break;
                }
            }
        }
    }

    /// @brief Handle the event of clicking on a button, on a given window.
    /// @param event Event that represent what happend (click, key pressed, ...)
    /// @param window Window where the scene belongs to.
    void Scene::buttonHandle(sf::Event event, sf::RenderWindow& window)
    {
        switch (this->current_window)
        {
            case MAIN_WINDOW:
            {
                for(constants::buttonPtr btn: this->btnMain)
                {
                    btn->handleEvent(event, window, this->engineOfGame, this);
                }
                this->player_renderer[0]->handleEvent(event, window, this);
                break;
            }
                
            case DRAFTING_WINDOW:
            {
                for(constants::buttonPtr btn: this->btnDraft)
                {
                    btn->handleEvent(event, window, this->engineOfGame, this);
                }
                this->drafting_hand_renderer->handleEvent(event, window, this);
                break;
            }
                
            case PLANIFICATION_WINDOW:
            {
                for(constants::buttonPtr btn: this->btnPlan)
                {
                    btn->handleEvent(event, window, this->engineOfGame, this);
                }
                this->player_renderer[3]->handleEvent(event, window, this);
                break;
            }
                
            case PLAYER_INFO:
            {
                for(constants::buttonPtr btn: this->btnFull)
                {
                    btn->handleEvent(event, window, this->engineOfGame, this);
                }
                break;
            }
                
            default:
            {
                break;
            }
        }
    }

    /// @brief Set a card as the one selected by the player when clicked.
    /// @param card Pointer to the card the player clicked on.
    void Scene::setSelectedCard(std::shared_ptr<state::Card> card)
    {
        constants::playerPtr p = this->game->getPlayers()[this->playerIndex];
        switch (this->current_window)
        {
            case MAIN_WINDOW:
            {
                constants::deckOfCards cards = p->getToBuildCards();
                std::vector<state::ResourceType> resourceType = {state::MATERIAL, state::ENERGY, state::SCIENCE, state::GOLD, state::EXPLORATION, state::KRYSTALLIUM, state::COLONEL, state::FINANCIER};

                auto iterator = std::find(cards.begin(), cards.end(), card);
                
                // if the card is found, it means that the player choosed a developmentCard. He want to add a resource on it.
                if (iterator != cards.end())
                {
                    int indexOfCard = iterator - cards.begin();
                    // Creating commands for adding resource to a card.
                    for (size_t index = 0; resourceType.size() > index; index++)
                    {
                        bool isRessourceNeeded = this->game->getPlayers()[this->playerIndex]->isResourcePlayable(resourceType[index], indexOfCard);

                        constants::commandPtr command = constants::commandPtr(new engine::Command(engine::ADDRESOURCE, this->playerIndex, indexOfCard, resourceType[index]));
                        this->btnMain[index]->changeCommand(command);
                        this->btnMain[index]->setEnabled(isRessourceNeeded);
                    }
                }
                // If the card is not found, it means that the player clicked on the empire. He wants to send a resource on the empire.
                else
                {
                    // Creating commands for sending a resource to the empire.
                    for (size_t index = 0; resourceType.size() > index; index++)
                    {
                        bool doesPlayerHaveResource = (0 < (this->game->getPlayers()[this->playerIndex]->getCurrentResources(resourceType[index])));

                        constants::commandPtr command = constants::commandPtr(new engine::Command(engine::SENDRESOURCETOEMPIRE, this->playerIndex, resourceType[index]));
                        this->btnMain[index]->changeCommand(command);
                        this->btnMain[index]->setEnabled(doesPlayerHaveResource);
                    }
                }
                break;
            }
            case DRAFTING_WINDOW:
            {
                auto cards = p->getDraftingCards();
                auto iterator = std::find(cards.begin(), cards.end(), card);
                // Checking if the iterator is found on the drafting cards to activate the 'CONFIRM' buton.
                if (iterator != cards.end())
                {
                    int indexOfCard = iterator - cards.begin();
                    // Creating commands for choosing the card to draft
                    constants::commandPtr command = constants::commandPtr(new engine::Command(engine::CHOOSEDRAFTCARD, this->playerIndex, indexOfCard));
                    this->btnDraft[0]->changeCommand(command);
                    this->btnDraft[0]->setEnabled(true);
                    
                }
                break;
            }
            case PLANIFICATION_WINDOW:
            {
                auto cards = p->getDraftCards();
                auto iterator = std::find(cards.begin(), cards.end(), card);
                // Checking if the iterator is found on the drafting cards to activate the 'keep card' and 'discard card butons.
                if (iterator != cards.end())
                {
                    int indexOfCard = iterator - cards.begin();
                    
                    // Creating the keep card command
                    constants::commandPtr command = constants::commandPtr(new engine::Command(engine::KEEPCARD, this->playerIndex, indexOfCard,true));
                    this->btnPlan[0]->changeCommand(command);
                    this->btnPlan[0]->setEnabled(true);
                    
                    // Creating the discard card command
                    command = constants::commandPtr(new engine::Command(engine::DISCARDCARD, this->playerIndex, indexOfCard, true));
                    this->btnPlan[1]->changeCommand(command);
                    this->btnPlan[1]->setEnabled(true);
                    return ;
                }
                // If the card was not found, let's check if it's inside the toBuildCard (cards choosed previously).
                cards = p->getToBuildCards();
                iterator = std::find(cards.begin(), cards.end(), card);
                if (iterator != cards.end())
                {
                    int indexOfCard = iterator - cards.begin();

                    // We can disable the button 'keep' because the card can only be discarded.
                    this->btnPlan[0]->setEnabled(false);
                    constants::commandPtr command = constants::commandPtr(new engine::Command(engine::DISCARDCARD, this->playerIndex, indexOfCard, false));
                    this->btnPlan[1]->changeCommand(command);
                    this->btnPlan[1]->setEnabled(true);
                }
                break;
            }
            default:
            {
                break;
            }
        }
    }

    /// @brief Draw the complete Scene.
    /// @param window Window where the scene belong to.
    void Scene::draw(sf::RenderWindow& window)
    {
        switch (this->current_window)
        {
            case MAIN_WINDOW:
            {
                window.draw(this->background);        //Background
                //Display GameRenderer
                this->game_renderer->draw(window);            
                
                //Display players
                this->player_renderer[0]->draw(window);
                this->player_renderer[1]->draw(window);
                
                for (constants::buttonPtr btn: btnMain)
                {
                    btn->draw(window);
                }

                break;
            }
                
            case DRAFTING_WINDOW:
            {
                //Display players
                for (size_t i = 4; this->player_renderer.size() > i; i++)
                {
                    this->player_renderer[i]->draw(window);
                }
                //Display Drafting Hand
                this->drafting_hand_renderer->draw(window);

                for (constants::buttonPtr btn: btnDraft)
                {
                    btn->draw(window);
                }
                break;
            }
                
            case PLAYER_INFO:
            {
                //Display Player
                this->player_renderer[2]->draw(window);

                for (constants::buttonPtr btn: btnFull)
                {
                    btn->draw(window);
                }
                break;
            }
                
            case PLANIFICATION_WINDOW:
            {
                window.draw(this->background,this->transform);
                //Display Drafted Hand
                this->player_renderer[3]->draw(window);

                for (constants::buttonPtr btn: btnPlan)
                {
                    btn->draw(window);
                }
                break;
            }

            default:
            {
                break;
            }
        }
    }

    /// @brief Function to disable all buttons from a window.
    /// @param index Index of the button to disable
    /// @param window Window where the button is draw.
    void Scene::disableButton(int index, Window window)
    {
        switch (window)
        {
            case MAIN_WINDOW:
            {
                this->btnMain[index]->setEnabled(false);
                break;
            }
            case DRAFTING_WINDOW:
            {
                this->btnDraft[index]->setEnabled(false);
                break;
            }
            case PLANIFICATION_WINDOW:
            {
                this->btnPlan[index]->setEnabled(false);
                break;
            }
            default:
            {
                break;
            }
        }
    }

    /// @brief Setup an observer to make the scene look at 
    /// @param observable New observable.
    void Scene::setupObserver(state::Observable* observable)
    {
        observable->addObserver(this->game_renderer);
        for(PlayerRenderer* pRenderer: player_renderer)
        {
            observable->addObserver(pRenderer);
        }
        observable->addObserver(this->drafting_hand_renderer);
        observable->addObserver(this);
    }
};
