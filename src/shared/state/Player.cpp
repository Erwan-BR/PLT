#include "Player.h"

#include "../../constants/constants/PlayerObserversNotification.h"

namespace state {

    /// @brief Create a player from a json file.
    Player::Player(Json::Value jsonValue) :
        Observable()
    {
        this->name = jsonValue["name"].asString();
        this->id = jsonValue["id"].asInt();

        if (! jsonValue["empire"].isNull())
        {
            this->empire = std::make_shared<EmpireCard>(jsonValue["empire"]);
        }

        this->resourcesInEmpireUnit = jsonValue["resourcesInEmpireUnit"].asInt();
        this->state = static_cast<PlayerState> (jsonValue["state"].asInt());

        // Retrieve built cards from the JSON.
        this->builtCards = {};
        if (jsonValue["builtCards"].isArray())
        {
            const Json::Value cardArray = jsonValue["builtCards"];
        
            for (const Json::Value& cardJSON : cardArray)
            {
                this->builtCards.push_back(std::make_shared<DevelopmentCard>(cardJSON));
            }
        }

        // Retrieve toBuildCards from the JSON.
        this->toBuildCards = {};
        if (jsonValue["toBuildCards"].isArray())
        {
            const Json::Value cardArray = jsonValue["toBuildCards"];
        
            for (const Json::Value& cardJSON : cardArray)
            {
                this->toBuildCards.push_back(std::make_shared<DevelopmentCard>(cardJSON));
            }
        }

        // Retrieve toBuildCards from the JSON.
        this->draftingCards = {};
        if (jsonValue["draftingCards"].isArray())
        {
            const Json::Value cardArray = jsonValue["draftingCards"];
        
            for (const Json::Value& cardJSON : cardArray)
            {
                this->draftingCards.push_back(std::make_shared<DevelopmentCard>(cardJSON));
            }
        }

        // Retrieve toBuildCards from the JSON.
        this->draftCards = {};
        if (jsonValue["draftCards"].isArray())
        {
            const Json::Value cardArray = jsonValue["draftCards"];
        
            for (const Json::Value& cardJSON : cardArray)
            {
                this->draftCards.push_back(std::make_shared<DevelopmentCard>(cardJSON));
            }
        }

        this->initializeMaps();

        // Retrieve currentResources from the JSON
        const Json::Value& currentResourcesArray = jsonValue["currentResources"];
        for (const Json::Value& resourceObject : currentResourcesArray)
        {
            ResourceType resourceType = static_cast<ResourceType> (resourceObject["resourceType"].asInt());
            int quantity = resourceObject["quantity"].asInt();
            this->currentResources[resourceType] = quantity;
        }

        // Retrieve resourcesProduction from the JSON
        const Json::Value& resourcesProductionArray = jsonValue["resourcesProduction"];
        for (const Json::Value& resourceObject : resourcesProductionArray)
        {
            ResourceType resourceType = static_cast<ResourceType> (resourceObject["resourceType"].asInt());
            int quantity = resourceObject["quantity"].asInt();
            this->resourcesProduction[resourceType] = quantity;
        }

        // Retrieve cardsTypeList from the JSON
        const Json::Value& cardsTypeListArray = jsonValue["cardsTypeList"];
        for (const Json::Value& resourceObject : cardsTypeListArray)
        {
            CardType cardType = static_cast<CardType> (resourceObject["cardType"].asInt());
            int quantity = resourceObject["quantity"].asInt();
            this->cardsTypeList[cardType] = quantity;
        }  
    }

    /// @brief Constructor of player that takes into argument the relative path to the texture.
    /// @param name Name of the player.
    /// @param id ID of the player.
    Player::Player (std::string name, int id) :
        Observable(),
        name(name),
        id(id)
    {
        this->initializeMaps();
    }

    /// @brief Destructor of the class Player
    Player::~Player()
    {
    }

    /// @brief Method called in the constructor. Used to initialize all dictionnary to null values.
    void Player::initializeMaps ()
    {
        this->resourcesProduction[ResourceType::MATERIAL] = 0;
        this->resourcesProduction[ResourceType::ENERGY] = 0;
        this->resourcesProduction[ResourceType::SCIENCE] = 0;
        this->resourcesProduction[ResourceType::GOLD] = 0;
        this->resourcesProduction[ResourceType::EXPLORATION] = 0;

        this->currentResources[ResourceType::MATERIAL] = 0;
        this->currentResources[ResourceType::ENERGY] = 0;
        this->currentResources[ResourceType::SCIENCE] = 0;
        this->currentResources[ResourceType::GOLD] = 0;
        this->currentResources[ResourceType::EXPLORATION] = 0;
        this->currentResources[ResourceType::KRYSTALLIUM] = 0;
        this->currentResources[ResourceType::FINANCIER] = 0;
        this->currentResources[ResourceType::COLONEL] = 0;

        this->cardsTypeList[CardType::STRUCTURE] = 0;
        this->cardsTypeList[CardType::VEHICLE] = 0;
        this->cardsTypeList[CardType::RESEARCH] = 0;
        this->cardsTypeList[CardType::PROJECT] = 0;
        this->cardsTypeList[CardType::DISCOVERY] = 0;
    }

    /// @brief Construct the card at the given index. The card is in toBuild and goes to builtCard.
    /// @param cardIndex Index of the card to construct, in the attributes toBuildCard.
    void Player::construct(int cardIndex)
    {
        if ((0 > cardIndex) || ((int)this->toBuildCards.size() <= cardIndex))
        {
            return ;
        }
        CardType cardConstructedType = this->toBuildCards[cardIndex]->getType();
        
        for(ResourceType resource : this->toBuildCards[cardIndex]->getInstantGain())
        {
            this->currentResources[resource]++;
        }

        // Transfering the element from a vector to the other one.
        this->builtCards.push_back(this->toBuildCards[cardIndex]);
        this->toBuildCards.erase(this->toBuildCards.begin() + cardIndex);
        
        // Add the card to the dictionnary containing constructed cards.
        this->cardsTypeList[cardConstructedType] ++;


        this->updateProduction();
    }
    
    /// @brief Check if a resource can be played by the player. Does not check if the player has the resource.
    /// @param resource Resource which the information is retrieved.
    /// @return True if the player can play this resource, false either.
    bool Player::isResourcePlayable (ResourceType resource) const
    {
        for (std::shared_ptr<DevelopmentCard> cardToBuild : this->toBuildCards)
        {
            if (cardToBuild->isResourceAddable(resource))
            {
                return true;
            }
        }
        return false;
    }

    /// @brief Add a resource to a card that is in toBuildCards.
    /// @param resource Resource to add to the card.
    /// @param cardIndex Index of the card.
    void Player::addResource (ResourceType resource, int cardIndex)
    {
        // Checking if the index of the card is valid and if the player has this resource.
        if ((0 > cardIndex) || ((int)this->toBuildCards.size() <= cardIndex) || (0 == this->currentResources.at(resource)))
        {
            return ;
        }

        //Adding the resource to the card, and building it if there are all the resources required on it.
        if(this->toBuildCards[cardIndex]->addResource(resource))
        {
            this->construct(cardIndex);
        }
        
        this->currentResources.at(resource) --;
        this->notifyObservers(TO_BUILD_CARDS_CHANGED);
    }

    /// @brief Convert a krystallium into another resource. Used when the player wants to place a krystallium on material/energy/...
    /// @param targetResource Resource that will replace the krystallium.
    void Player::convertKrystallium (ResourceType targetResource)
    {
        // Impossible to convert to colonel / financier. Moreover, the player has to have at least one krystallium to make the conversion.
        if ((ResourceType::COLONEL == targetResource) || (ResourceType::FINANCIER == targetResource) || (0 >= this->currentResources.at(ResourceType::KRYSTALLIUM)))
        {
            return ;
        }

        // Convert the resource and propagate the information to observers.
        this->currentResources.at(ResourceType::KRYSTALLIUM) --;
        this->currentResources.at(targetResource) ++;
        this->notifyObservers(PLAYER_CURRENT_RESOURCES_CHANGED);
    }
    
    /// @brief Discard a card to gain a discard gain.
    /// @param cardIndex Index of the card to discard.
    /// @param isADraftedCard Indicated if the card comes from the vector drafted card, or from toBuildCards.
    void Player::discardCard(int cardIndex, bool isADraftedCard)
    {
        if(isADraftedCard)
        {
            if ((0 > cardIndex) || ((int)this->draftCards.size() <= cardIndex))
            {
                return ;
            }
            ResourceType discardGain = this->draftCards.at(cardIndex)->getDiscardGain();
            this->currentResources.at(discardGain) ++ ;
            this->draftCards.erase(this->draftCards.begin() + cardIndex);
            this->notifyObservers(DRAFT_CARDS_CHANGED);
        }
        else
        {
            if ((0 > cardIndex) || ((int)this->toBuildCards.size() <= cardIndex))
            {
                return ;
            }
            this->resourcesInEmpireUnit ++;
            this->convertToKrystallium();
            this->toBuildCards.erase(this->toBuildCards.begin() + cardIndex);

            this->notifyObservers(TO_BUILD_CARDS_CHANGED);
        }
        
    }

    /// @brief Function called when the player wants to keep a card from the drafting phase.
    /// @param toKeepCardIndex Index of the card to keep.
    void Player::keepCard(int toKeepCardIndex)
    {
        if (0 > toKeepCardIndex || (int)this->draftCards.size() <= toKeepCardIndex)
        {
            return ;
        }
        std::shared_ptr<DevelopmentCard> card = this->draftCards.at(toKeepCardIndex);
        this->toBuildCards.push_back(card);
        this->draftCards.erase(this->draftCards.begin() + toKeepCardIndex);
        
        this->notifyObservers(DRAFT_CARDS_CHANGED | TO_BUILD_CARDS_CHANGED);
    }

    /// @brief Update the production of every tokens
    void Player::updateProduction()
    {
        this->resourcesProduction[MATERIAL] = computeProduction(MATERIAL);
        this->resourcesProduction[ENERGY] = computeProduction(ENERGY);
        this->resourcesProduction[SCIENCE] = computeProduction(SCIENCE);
        this->resourcesProduction[GOLD] = computeProduction(GOLD);
        this->resourcesProduction[EXPLORATION] = computeProduction(EXPLORATION);

        this->notifyObservers(PLAYER_RESOURCES_PRODUCTION_CHANGED);
    }

    /// @brief Compute the quantity of resource named "resourceToProduce" produced by the player
    /// @param resourceToProduce Type of the resource that will be produced
    /// @return Quantity of resource "resourceToProduce" obtained by the player
    int Player::computeProduction(ResourceType resourceToProduce) const
    {
        int productionValue = 0;

        // Iterating among all constructed cards.
        for(std::shared_ptr<DevelopmentCard> card : this->builtCards)
        {
            // Iterating among all resources produced by this card.
            for(ResourceToProduce* resource : card->getProductionGain())
            {
                // Checking if the resource is the same as the one we are constructing.
                if(resourceToProduce == resource->type)
                {
                    // Checking if it's nonetype, or if it has to be multiplied by the number of a certain type of card (already built)
                    if(CardType::NONETYPE == resource->cardType)
                    {
                        productionValue += resource->quantity;
                    }
                    else
                    {
                        productionValue += (resource->quantity) * (this->cardsTypeList.at(resource->cardType));
                    }
                }
            }
        }

        // Iterating among all resources produced by the empire.
        for(ResourceToProduce* resource : this->empire->getProductionGain())
        {
            // Checking if the resource is the same as the one we are constructing.
            if(resourceToProduce == resource->type)
            {
                // Checking if it's nonetype, or if it has to be multiplied by the number of a certain type of card (already built)
                if(CardType::NONETYPE == resource->cardType)
                {
                    productionValue += resource->quantity;           
                }
                else
                {
                    productionValue += (resource->quantity) * (this->cardsTypeList.at(resource->cardType));
                }
            }
        }

        return productionValue;
    }

    /// @brief Compute the number of victory points the player has
    /// @return Number of victory points of the player on the moment
    int Player::computeVictoryPoint() const
    {
        int victoryPoints = 0;
        for(std::shared_ptr<DevelopmentCard> card : this->builtCards)
        {
            CardVictoryPoint* cardVictoryPoints = card->getVictoryPoints();

            if(0 == cardVictoryPoints->cardOrResourceType)
            {
                victoryPoints += cardVictoryPoints->numberOfPoints;
            }
            else if(ResourceType::COLONEL == cardVictoryPoints->cardOrResourceType)
            {
                victoryPoints += cardVictoryPoints->numberOfPoints * this->currentResources.at(ResourceType::COLONEL);
            }
            else if(ResourceType::FINANCIER == cardVictoryPoints->cardOrResourceType)
            {
                victoryPoints += cardVictoryPoints->numberOfPoints * this->currentResources.at(ResourceType::FINANCIER);
            }
            else if((20 < cardVictoryPoints->cardOrResourceType) && (26 > cardVictoryPoints->cardOrResourceType))
            {
                victoryPoints += (cardVictoryPoints->numberOfPoints) * this->cardsTypeList.at((state::CardType)(cardVictoryPoints->cardOrResourceType));
            }
        }

        CardVictoryPoint* empireVictoryPoints = this->empire->getVictoryPoints();
        if(0 == empireVictoryPoints->cardOrResourceType)
        {
            victoryPoints += empireVictoryPoints->numberOfPoints;
        }
        else if(ResourceType::COLONEL == empireVictoryPoints->cardOrResourceType)
        {
            victoryPoints += empireVictoryPoints->numberOfPoints * this->currentResources.at(ResourceType::COLONEL);
        }
        else if(ResourceType::FINANCIER == empireVictoryPoints->cardOrResourceType)
        {
            victoryPoints += empireVictoryPoints->numberOfPoints * this->currentResources.at(ResourceType::FINANCIER);
        }
        else if((20 < empireVictoryPoints->cardOrResourceType) && (26 > empireVictoryPoints->cardOrResourceType))
        {
            victoryPoints += (empireVictoryPoints->numberOfPoints) * this->cardsTypeList.at((state::CardType)empireVictoryPoints->cardOrResourceType);
        }

        return victoryPoints;
    }

    /// @brief Take a resource produced by the player and place it on the Empire of the player
    /// @param resource Type of resource that one will be send to the empire card of the player
    void Player::sendResourceToEmpire(ResourceType resource)
    {
        if (0 == this->currentResources.at(resource))
        {
            return;
        }
        this->currentResources.at(resource)--;
        this->resourcesInEmpireUnit++;
        this->convertToKrystallium();
        this->notifyObservers(PLAYER_CURRENT_RESOURCES_CHANGED);
    }

    /// @brief Converts the empire's resources into a krystallium when it reaches 5 resources
    void Player::convertToKrystallium()
    {
        if(5 == this->resourcesInEmpireUnit)
        {
            this->resourcesInEmpireUnit = 0;
            this->currentResources.at(ResourceType::KRYSTALLIUM) ++;
        }
    }

    /// @brief Add the selected card from the drafting deck to the selected one
    /// @param cardIndex Card choosed by the player
    void Player::chooseDraftCard(int cardIndex)
    {
        if (0 > cardIndex || (int)this->draftingCards.size() <= cardIndex)
        {
            return ;
        }
        this->draftCards.push_back(draftingCards.at(cardIndex));
        this->draftingCards.erase(this->draftingCards.begin() + cardIndex);
        this->state = PlayerState::PENDING;

        this->notifyObservers(DRAFTING_CARDS_CHANGED | DRAFT_CARDS_CHANGED | PLAYER_STATE_CHANGED);
    }
    
    /// @brief Receive multiple resources from the game
    /// @param resourceToReceive Type of the resource to receive.
    /// @param numberOfResources Number of ressources to receive.
    void Player::receiveResources (ResourceType resourceToReceive, int numberOfResources)
    {
        for (int i = 0; i < numberOfResources ; i++)
        {
            this->currentResources.at(resourceToReceive) ++;
        }
        this->notifyObservers(PLAYER_CURRENT_RESOURCES_CHANGED);
        
    }

    /// @brief End the planificiation for the current player. Send all drafted cards to the to buildCard.
    void Player::endPlanification ()
    {
        for (std::shared_ptr<DevelopmentCard> card : this->draftCards)
        {
            this->toBuildCards.push_back(card);
        }

        this->sendAllResourcesToEmpire();

        this->draftCards.clear();
        this->state = PlayerState::PENDING;
        this->notifyObservers(TO_BUILD_CARDS_CHANGED | DRAFT_CARDS_CHANGED | PLAYER_STATE_CHANGED);
    }

    /// @brief End the production for the current player. Send all resources in empires.
    void Player::endProduction ()
    {
        this->sendAllResourcesToEmpire();
        this->state = PlayerState::PENDING;
        this->notifyObservers(PLAYER_STATE_CHANGED);
    }

    /// @brief Send all resources (material, energy, gold, exploration, science)
    void Player::sendAllResourcesToEmpire ()
    {
        const std::vector<ResourceType> resourcesToSend = {ResourceType::MATERIAL, ResourceType::ENERGY, ResourceType::SCIENCE, ResourceType::GOLD, ResourceType::EXPLORATION};
        for (ResourceType resourceType : resourcesToSend)
        {
            while(0 != this->currentResources.at(resourceType))
            {
                this->sendResourceToEmpire(resourceType);
            }
        }
        this->notifyObservers(PLAYER_CURRENT_RESOURCES_CHANGED);
    }


    ///@brief Convert the Player to a JSON format. Usefull when the game is saved.
	///@return Readable JSON of the player.
    Json::Value Player::toJSON () const
    {
        // Instanciation of the player into a JSON format.
        Json::Value playerJSON;

        playerJSON["name"] = this->name;
        playerJSON["id"] = this->id;
        
        if (nullptr == this->empire)
        {
            playerJSON["empire"] = Json::nullValue;
        }
        else
        {
            playerJSON["empire"] = this->empire->toJSON();
        }

        // Serialize the vector of builtCards
        Json::Value builtCardsArray;
        for (const std::shared_ptr<DevelopmentCard>& card : this->builtCards)
        {
            builtCardsArray.append(card->toJSON());
        }
        playerJSON["builtCards"] = builtCardsArray;

        // Serialize the vector of toBuildCards
        Json::Value toBuildCardsArray;
        for (const std::shared_ptr<DevelopmentCard>& card : this->toBuildCards)
        {
            toBuildCardsArray.append(card->toJSON());
        }
        playerJSON["toBuildCards"] = toBuildCardsArray;

        // Serialize the vector of draftingCards
        Json::Value draftingCardsArray;
        for (const std::shared_ptr<DevelopmentCard>& card : this->draftingCards)
        {
            draftingCardsArray.append(card->toJSON());
        }
        playerJSON["draftingCards"] = draftingCardsArray;

        // Serialize the vector of draftCards
        Json::Value draftCardsArray;
        for (const std::shared_ptr<DevelopmentCard>& card : this->draftCards)
        {
            draftCardsArray.append(card->toJSON());
        }
        playerJSON["draftCards"] = draftCardsArray;

        playerJSON["state"] = static_cast<int> (this->state);
        playerJSON["resourcesInEmpireUnit"] = this->resourcesInEmpireUnit;
        
        // Serialize the map of currentResources
        Json::Value currentResourcesArray;
        for (const auto& entry : this->currentResources) {
            Json::Value resourceObject;
            resourceObject["resourceType"] = static_cast<int>(entry.first);
            resourceObject["quantity"] = entry.second;
            currentResourcesArray.append(resourceObject);
        }
        playerJSON["currentResources"] = currentResourcesArray;

        // Serialize the map of resourcesProduction
        Json::Value resourcesProductionArray;
        for (const auto& entry : this->resourcesProduction) {
            Json::Value resourceObject;
            resourceObject["resourceType"] = static_cast<int>(entry.first);
            resourceObject["quantity"] = entry.second;
            resourcesProductionArray.append(resourceObject);
        }
        playerJSON["resourcesProduction"] = resourcesProductionArray;

        // Serialize the map of cardsTypeList
        Json::Value cardsTypeListArray;
        for (const auto& entry : this->cardsTypeList) {
            Json::Value resourceObject;
            resourceObject["cardType"] = static_cast<int>(entry.first);
            resourceObject["quantity"] = entry.second;
            cardsTypeListArray.append(resourceObject);
        }
        playerJSON["cardsTypeList"] = cardsTypeListArray;

        return playerJSON;
    }

    /************************************* Setters & Getters *************************************/

    /// @brief Setter for the empire card. The resources produced has to be updated.
    /// @param empire Empire to give to the player.
    void Player::setEmpire(std::shared_ptr<EmpireCard> empire)
    {
        this->empire = empire;

        this->updateProduction();
    }

    /// @brief Setter for the drafting deck
    /// @param draft drafting deck to give to the player
    void Player::setDraftingCards(std::vector<std::shared_ptr<DevelopmentCard>> draft)
    {
        this->draftingCards.clear();
        for(std::shared_ptr<DevelopmentCard> card : draft)
        {
            this->draftingCards.push_back(card);
        }
        this->notifyObservers(DRAFTING_CARDS_CHANGED);
    }

    /// @brief Setter for the drafting deck
    /// @param draft drafting deck to give to the player
    void Player::setState(PlayerState state)
    {
        this->state = state;
        this->notifyObservers(PLAYER_STATE_CHANGED);
    }

    /// @brief Set the preferred personnage of the player. Usefull for choosing colonel / financier at third production.
    /// @param newPreferedPersonnage New preferred personnage.
    void Player::setPreferedPersonnage (ResourceType newPreferedPersonnage)
    {
        if (ResourceType::COLONEL == newPreferedPersonnage || ResourceType::FINANCIER == newPreferedPersonnage)
        {
            this->preferedPersonnage = newPreferedPersonnage;
        }
    }

    /// @brief Get the production of a given resource.
    /// @param resource Resource which the production quantity is asked.
    /// @return Production of this resource.
    int Player::getProductionGain (ResourceType resource) const
    {
        return this->resourcesProduction.at(resource);
    }

    /// @brief Get the name of the player
    /// @return Name of the player
    std::string Player::getName () const
    {
        return this->name;
    }

    /// @brief Get the empire card of the player.
    /// @return Empire Card of the player.
    std::shared_ptr<EmpireCard> Player::getEmpire () const
    {
        return this->empire;
    }

    /// @brief Get the cards that are already built by the player.
    /// @return Vector of cards built by the player.
    std::vector<std::shared_ptr<DevelopmentCard>> Player::getBuiltCards () const
    {
        return this->builtCards;
    }

    /// @brief Get the cards that are not already built by the player.
    /// @return Vector of cards not built by the player.
    std::vector<std::shared_ptr<DevelopmentCard>> Player::getToBuildCards () const
    {
        return this->toBuildCards;
    }

    /// @brief Get the cards that are in the hand of the player, and he has to choose one.
    /// @return Vector of cards that the player can choose.
    std::vector<std::shared_ptr<DevelopmentCard>> Player::getDraftingCards () const
    {
        return this->draftingCards;
    }

    /// @brief Get the cards that the player choosed during the drafting phase.
    /// @return Vector of cards that the player choosed during the drafting phase.
    std::vector<std::shared_ptr<DevelopmentCard>> Player::getDraftCards () const
    {
        return this->draftCards;
    }

    /// @brief Get the State of the player (PENDING, PLAYING)
    /// @return State of the player
    PlayerState Player::getState () const
    {
        return this->state;
    }

    /// @brief Get the ressources that the player has and can play now.
    /// @return Vector of ressources that the player can play.
    std::map<ResourceType,int> Player::getCurrentResources () const
    {
        return this->currentResources;
    }

    /// @brief Get the current resources 
    /// @param resource Resource which we want to know number the player has.
    /// @return Number of resources of the input that the player has.
    int Player::getCurrentResources (ResourceType resource) const
    {
        return this->currentResources.at(resource);
    }

    /// @brief Get the quantity of ressources in the empire (to convert to Krystallium)
    /// @return Quantity of ressources in the empire.
    int Player::getResourcesInEmpireUnit () const
    {
        return this->resourcesInEmpireUnit;
    }

    /// @brief Get the resources production of all types.
    /// @return Map of every production by the player.
    std::map<ResourceType,int> Player::getResourcesProduction () const
    {
        return this->resourcesProduction;
    }

    /// @brief Get how much built cards of each type the player has build
    /// @return Map of evry card type built by the player
    std::map<CardType,int> Player::getCardsTypeList () const
    {
        return this->cardsTypeList;
    }

    /// @brief Retrieve the ID of the player. To know if a player is an AI, use isAI.
    /// @return ID of the player.
    int Player::getID () const
    {
        return this->id;
    }

    /// @brief Retrieve the prefered personnage of the player.
    /// @return Preferred personnage of the player.
    bool Player::isPreferedPersonnageColonel () const
    {
        return (ResourceType::COLONEL == this->preferedPersonnage);
    }

    /// @brief Check if a player is an AI (because players with negative ID are AIs)
    /// @return Boolean that state if a player is an AI.
    bool Player::isAI () const
    {
        return (this->id < 0);
    }

    /// @brief Check if the player is a real player AND is playing.
    /// @return Boolean that state if a player is an AI and playing.
    bool Player::isRealPlayerAndPlaying () const
    {
        return (! this->isAI()) && (PlayerState::PLAYING == this->state);
    }

    /// @brief Function that retrieve the quantity of personnages of a player. Usefull in case of tie in a game.
    /// @return Numbers of personnages of the players (i.e colonel + financier)
    int Player::getQuantityPersonnages () const
    {
        return this->currentResources.at(ResourceType::COLONEL) + this->currentResources.at(ResourceType::FINANCIER);
    }

    /************************************* Methods implemented for AI. *************************************/
    
    /// @brief Method for AI, to make them choose their card. Method implemented in Player because both Player and AI are in the same vector in Game.
    void Player::AIChooseDraftingCard ()
    {
        return ;
    }

    /// @brief Method for AI, to make them choose their card in planification. Method implemented in Player because both Player and AI are in the same vector in Game.
    void Player::AIPlanification ()
    {
        return ;
    }

    /// @brief Method for AI, to make them used their resources. Method implemented in Player because both Player and AI are in the same vector in Game.
    void Player::AIUseProducedResources ()
    {
        return ;
    }

    /// @brief Method for AI, to make them choose colonel of financier token. Method implemented in Player because both Player and AI are in the same vector in Game.
    /// @return True if the AI choose colonel, false either.
    bool Player::AIChooseColonelToken ()
    {
        return false;
    }
}
