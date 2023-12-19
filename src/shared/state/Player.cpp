#include "Player.h"
#include <map>

namespace state {

    /// @brief Constructor of the class Player
    Player::Player() :
    Observable(),
    name(""),
    id(-1),
    profilePicture(new sf::Texture())
    {
        resourcesProduction[ResourceType::MATERIAL] = 0;
        resourcesProduction[ResourceType::ENERGY] = 0;
        resourcesProduction[ResourceType::SCIENCE] = 0;
        resourcesProduction[ResourceType::GOLD] = 0;
        resourcesProduction[ResourceType::EXPLORATION] = 0;

        cardsTypeList[CardType::STRUCTURE] = 0;
        cardsTypeList[CardType::VEHICLE] = 0;
        cardsTypeList[CardType::RESEARCH] = 0;
        cardsTypeList[CardType::PROJECT] = 0;
        cardsTypeList[CardType::DISCOVERY] = 0;
    }
    
    /// @brief Constructor of the player, with some parameters.
    /// @param name Name of the player
    /// @param id Id of the player
    /// @param profilePicture Profile Picture of the player
    Player::Player(std::string name, int id, sf::Texture* profilePicture) :
    Observable(),
    name(name),
    id(id),
    profilePicture(profilePicture)
    {
        resourcesProduction[ResourceType::MATERIAL] = 0;
        resourcesProduction[ResourceType::ENERGY] = 0;
        resourcesProduction[ResourceType::SCIENCE] = 0;
        resourcesProduction[ResourceType::GOLD] = 0;
        resourcesProduction[ResourceType::EXPLORATION] = 0;

        cardsTypeList[CardType::STRUCTURE] = 0;
        cardsTypeList[CardType::VEHICLE] = 0;
        cardsTypeList[CardType::RESEARCH] = 0;
        cardsTypeList[CardType::PROJECT] = 0;
        cardsTypeList[CardType::DISCOVERY] = 0;
    }

    /// @brief Destructor of the class Player
    Player::~Player()
    {
        this->resourcesProduction.clear();
        this->cardsTypeList.clear();
        delete this->empire;
        
        for(DevelopmentCard* card : this->builtCards)
        {
            delete card;
        }


        for(DevelopmentCard* card : this->toBuildCards)
        {
            delete card;
        }


        for(DevelopmentCard* card : this->draftingCards)
        {
            delete card;
        }

        for(DevelopmentCard* card : this->draftCards)
        {
            delete card;
        }

    }

    /// @brief Construct the card at the given index. The card is in toBuild and goes to builtCard.
    /// @param cardIndex Index of the card to construct, in the attributes toBuildCard.
    void Player::construct(int cardIndex)
    {
        if ((0 > cardIndex) || ((int)this->toBuildCards.size() < cardIndex))
        {
            return ;
        }
        CardType cardConstructedType = this->toBuildCards[cardIndex]->getType();
        
        // Transfering the element from a vector to the other one.
        this->builtCards.push_back(this->toBuildCards[cardIndex]);
        this->toBuildCards.erase(this->toBuildCards.begin() + cardIndex);
        
        // Add the card to the dictionnary containing constructed cards.
        this->cardsTypeList[cardConstructedType] ++;
        this->updateProduction();
        this->notifyObservers();
    }
    
    /// @brief Check if a resource can be played by the player. Does not check if the player has the resource.
    /// @param resource Resource which the information is retrieved.
    /// @return True if the player can play this resource, false either.
    bool Player::isResourcePlayable (ResourceType resource) const
    {
        for (DevelopmentCard* cardToBuild : this->toBuildCards)
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
        auto resourcePosition = std::find(this->currentResources.begin(), this->currentResources.end(), resource);
        if ((0 > cardIndex || ((int)this->toBuildCards.size() < cardIndex)) || (this->currentResources.end() == resourcePosition))
        {
            return ;
        }
        //Check if the resource is addable to the designated card
        if(this->toBuildCards[cardIndex]->isResourceAddable(resource))
        {
            //Adding the resource to the card, and building it if there are all the resources required on it.
            if(this->toBuildCards[cardIndex]->addResource(resource))
            {
                this->construct(cardIndex);
            }
            this->currentResources.erase(resourcePosition);
        }
    }
    
    /// @brief Discard a card to gain a discard gain.
    /// @param cardIndex Index of the card to discard.
    /// @param isADraftedCard Indicated if the card comes from the vector drafted card, or from toBuildCards.
    void Player::discardCard(int cardIndex, bool isADraftedCard)
    {
        if(isADraftedCard)
        {
            if ((0 > cardIndex) || ((int)this->draftCards.size() < cardIndex))
            {
                return ;
            }
            DevelopmentCard* toDiscardCard = this->draftCards.at(cardIndex);
            this->currentResources.push_back(toDiscardCard->getDiscardGain());
            this->draftCards.erase(this->draftCards.begin() + cardIndex);            
        }
        else
        {
            if ((0 > cardIndex) || ((int)this->toBuildCards.size() < cardIndex))
            {
                return ;
            }
            DevelopmentCard* toDiscardCard = this->toBuildCards.at(cardIndex);
            sendResourceToEmpire(toDiscardCard->getDiscardGain());
            convertToKrystallium();
            this->toBuildCards.erase(this->toBuildCards.begin() + cardIndex);             
        }
        this->notifyObservers();
    }

    /// @brief Function called when the player wants to keep a card from the drafting phase.
    /// @param toKeepCardIndex Index of the card to keep.
    void Player::keepCard(int toKeepCardIndex)
    {
        if (0 > toKeepCardIndex || (int)this->draftCards.size() < toKeepCardIndex)
        {
            return ;
        }
        DevelopmentCard* card = this->draftCards.at(toKeepCardIndex);
        this->toBuildCards.push_back(card);
        this->draftCards.erase(this->draftCards.begin() + toKeepCardIndex);
        this->notifyObservers();
    }

    /// @briefUpdate the production of every tokens
    void Player::updateProduction()
    {
        this->resourcesProduction[MATERIAL] = computeProduction(MATERIAL);
        this->resourcesProduction[ENERGY] = computeProduction(ENERGY);
        this->resourcesProduction[SCIENCE] = computeProduction(SCIENCE);
        this->resourcesProduction[GOLD] = computeProduction(GOLD);
        this->resourcesProduction[EXPLORATION] = computeProduction(EXPLORATION);

        this->notifyObservers();
    }

    /// @brief Compute the quantity of resource named "resourceToProduce" produced by the player
    /// @param resourceToProduce Type of the resource that will be produced
    /// @return Quantity of resource "resourceToProduce" obtained by the player
    int Player::computeProduction(ResourceType resourceToProduce) const
    {
        int productionValue = 0;

        // Iterating among all constructed cards.
        for(DevelopmentCard* card : this->builtCards)
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
        for(DevelopmentCard* card : this->builtCards)
        {
            CardVictoryPoint* cardVictoryPoints = card->getVictoryPoints();

            if(0 == cardVictoryPoints->cardOrResourceType)
            {
                victoryPoints += cardVictoryPoints->numberOfPoints;
            }
            else if(ResourceType::COLONEL == cardVictoryPoints->cardOrResourceType)
            {
                victoryPoints += cardVictoryPoints->numberOfPoints * this->colonelTokensUnit;
            }
            else if(ResourceType::FINANCIER == cardVictoryPoints->cardOrResourceType)
            {
                victoryPoints += cardVictoryPoints->numberOfPoints * this->financierTokensUnit;
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
            victoryPoints += empireVictoryPoints->numberOfPoints * this->colonelTokensUnit;
        }
        else if(ResourceType::FINANCIER == empireVictoryPoints->cardOrResourceType)
        {
            victoryPoints += empireVictoryPoints->numberOfPoints * this->financierTokensUnit;
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
        // Checking if the player has the resources.
        auto resourcePosition = std::find(this->currentResources.begin(), this->currentResources.end(), resource);
        if (this->currentResources.end() == resourcePosition)
        {
            return ;
        }
        this->currentResources.erase(resourcePosition);
        this->resourcesInEmpireUnit++;
        this->convertToKrystallium();
        this->notifyObservers();
    }

    /// @brief Converts the empire's resources into a krystallium when it reaches 5 resources
    void Player::convertToKrystallium()
    {
        if(5 == this->resourcesInEmpireUnit)
        {
            this->resourcesInEmpireUnit = 0;
            this->krystalliumTokensUnit++;
        }
    }

    /// @brief Add the selected card from the drafting deck to the selected one
    /// @param cardIndex Card choosed by the player
    void Player::chooseDraftCard(int cardIndex)
    {
        if (0 > cardIndex || (int)this->draftingCards.size() < cardIndex)
        {
            return ;
        }
        this->draftCards.push_back(draftingCards.at(cardIndex));
        this->draftingCards.erase(this->draftingCards.begin() + cardIndex);
        this->state = PlayerState::PENDING;

        this->notifyObservers();
    }

    /// @brief Return the selected token by the player (Colonel/Financier)
    /// Not implementable as it ask to know on which one does the player clicks.
    /// @return Boolean returned by the choice of the player (true => Colonel, false => Financier)
    bool Player::chooseColonelToken() const
    {
        return false ;
    }
    
    /// @brief Receive multiple resources from the game
    /// @param resourceToReceive Type of the resource to receive.
    /// @param numberOfResources Number of ressources to receive.
    void Player::receiveResources (ResourceType resourceToReceive, int numberOfResources)
    {
        for (int i = 0; i < numberOfResources ; i++)
        {
            if (ResourceType::COLONEL == resourceToReceive)
            {
                this->colonelTokensUnit ++ ;
            }
            else if (ResourceType::FINANCIER == resourceToReceive)
            {
                this->financierTokensUnit ++;
            }
            else if (ResourceType::KRYSTALLIUM == resourceToReceive)
            {
                this->krystalliumTokensUnit ++;
            }
            else
            {
                this->currentResources.push_back(resourceToReceive);
            }
        }

        this->notifyObservers();
    }

    /// @brief End the planificiation for the current player. Send all drafted cards to the to buildCard.
    void Player::endPlanification ()
    {
        for (DevelopmentCard* card : this->draftCards)
        {
            this->toBuildCards.push_back(card);
        }

        for (ResourceType resource : this->currentResources)
        {
            this->sendResourceToEmpire(resource);
        }

        this->draftCards.clear();
        this->currentResources.clear();
        this->state = PlayerState::PENDING;
        this->notifyObservers();
    }

    /// @brief End the production for the current player. Send all resources in empires.
    void Player::endProduction ()
    {
        for (ResourceType resource : this->currentResources)
        {
            this->sendResourceToEmpire(resource);
        }

        this->currentResources.clear();
        this->state = PlayerState::PENDING;
        this->notifyObservers();
    }

    /// @brief Transform the Player to a readable string.
    /// @return Readable string that represents the information of the Player.
    std::string Player::toString () const
    {
        std::string returnValue = "Name: " + this->name + "\n";
        
        returnValue += "Id: " + std::to_string(this->id) + "\n";
        returnValue += "-----Empire informations:-----\n " + empire->toString() + "\n";
        returnValue += "builtCards length: " + std::to_string(this->builtCards.size()) + "\n";
        returnValue += "toBuildCards length: " + std::to_string(this->toBuildCards.size()) + "\n";
        returnValue += "draftingCards length: " + std::to_string(this->draftingCards.size()) + "\n";
        returnValue += "dratfCards length: " + std::to_string(this->draftCards.size()) + "\n";
        returnValue += "State: " + std::to_string(this->state) + "\n";
        returnValue += "financierTokensUnit: " + std::to_string(this->financierTokensUnit) + "\n";
        returnValue += "colonelTokensUnit: " + std::to_string(this->colonelTokensUnit) + "\n";
        returnValue += "krystalliumTokensUnit: " + std::to_string(this->krystalliumTokensUnit) + "\n";
        returnValue += "currentResources length: " + std::to_string(this->currentResources.size()) + "\n";
        returnValue += "resourcesInEmpireUnit: " + std::to_string(this->resourcesInEmpireUnit) + "\n";


        return returnValue;
    }

    /************************************* Setters & Getters *************************************/

    /// @brief Setter for the empire card. The resources produced has to be updated.
    /// @param empire Empire to give to the player.
    void Player::setEmpire(EmpireCard* empire)
    {
        this->empire = empire;

        this->updateProduction();
    }

    /// @brief Setter for the drafting deck
    /// @param draft drafting deck to give to the player
    void Player::setDraftingCards(std::vector<DevelopmentCard*> draft)
    {
        this->draftingCards = {};
        for(DevelopmentCard* card : draft)
        {
            this->draftingCards.push_back(card);
        }

        this->notifyObservers();
    }

    /// @brief Setter for the drafting deck
    /// @param draft drafting deck to give to the player
    void Player::setState(PlayerState state)
    {
        this->state = state;
        this->notifyObservers();
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

    /// @brief Get the profile picture of the player, to display it
    /// @return Profile picture of the player
    sf::Texture* Player::getProfilePicture () const
    {
        return this->profilePicture;
    }

    /// @brief Get the empire card of the player.
    /// @return Empire Card of the player.
    EmpireCard* Player::getEmpire () const
    {
        return this->empire;
    }

    /// @brief Get the cards that are already built by the player.
    /// @return Vector of cards built by the player.
    std::vector<DevelopmentCard*> Player::getBuiltCards () const
    {
        return this->builtCards;
    }

    /// @brief Get the cards that are not already built by the player.
    /// @return Vector of cards not built by the player.
    std::vector<DevelopmentCard*> Player::getToBuildCards () const
    {
        return this->toBuildCards;
    }

    /// @brief Get the cards that are in the hand of the player, and he has to choose one.
    /// @return Vector of cards that the player can choose.
    std::vector<DevelopmentCard*> Player::getDraftingCards () const
    {
        return this->draftingCards;
    }

    /// @brief Get the cards that the player choosed during the drafting phase.
    /// @return Vector of cards that the player choosed during the drafing phase.
    std::vector<DevelopmentCard*> Player::getDraftCards () const
    {
        return this->draftCards;
    }

    /// @brief Get the State of the player (PENDING, PLAYING)
    /// @return State of the player
    PlayerState Player::getState () const
    {
        return this->state;
    }

    /// @brief Get the quantity of Financier tokens that the player has.
    /// @return Quantity of Financier tokens that the player has.
    int Player::getFinancierTokensUnit () const
    {
        return this->financierTokensUnit;
    }

    /// @brief Get the quantity of Colonel tokens that the player has.
    /// @return Quantity of Colonel tokens that the player has.
    int Player::getColonelTokensUnit () const
    {
        return this->colonelTokensUnit;
    }

    /// @brief Get the quantity of Krystallium tokens that the player has.
    /// @return Quantity of Krystallium tokens that the player has.
    int Player::getKrystalliumTokensUnit () const
    {
        return this->krystalliumTokensUnit;
    }

    /// @brief Get the ressources that the player has and can play now.
    /// @return Vector of ressources that the player can play.
    std::vector<ResourceType> Player::getCurrentResources () const
    {
        return this->currentResources;
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

    /************************************* Methods implemented for AI. *************************************/
    
    /// @brief Method for AI, to make them choose their card. Method implemented in Player because both Player and AI are in the same vector in Game.
    void AIChooseDraftingCard ()
    {
        return ;
    }

    /// @brief Method for AI, to make them choose their card in planification. Method implemented in Player because both Player and AI are in the same vector in Game.
    void AIPlanification ()
    {
        return ;
    }

    /// @brief Method for AI, to make them used their resources. Method implemented in Player because both Player and AI are in the same vector in Game.
    void AIUseProducedResources ()
    {
        return ;
    }
}
