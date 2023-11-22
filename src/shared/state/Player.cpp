#include "Player.h"
#include <map>

namespace state {

    /// @brief Constructor of the class Player
    Player::Player() :
    Observable(),
    name(""),
    id(-1),
    profilePicture(sf::Texture())
    {
        resourcesProduction[MATERIAL] = 0;
        resourcesProduction[ENERGY] = 0;
        resourcesProduction[SCIENCE] = 0;
        resourcesProduction[GOLD] = 0;
        resourcesProduction[EXPLORATION] = 0;

        cardsTypeList[STRUCTURE] = 0;
        cardsTypeList[VEHICLE] = 0;
        cardsTypeList[RESEARCH] = 0;
        cardsTypeList[PROJECT] = 0;
        cardsTypeList[DISCOVERY] = 0;
    }
    
    /// @brief Constructor of the player, with some parameters.
    /// @param name Name of the player
    /// @param id Id of the player
    /// @param profilePicture Profile Picture of the player
    Player::Player(std::string name, int id, sf::Texture profilePicture) :
    Observable(),
    name(name),
    id(id),
    profilePicture(profilePicture)
    {
        resourcesProduction[MATERIAL] = 0;
        resourcesProduction[ENERGY] = 0;
        resourcesProduction[SCIENCE] = 0;
        resourcesProduction[GOLD] = 0;
        resourcesProduction[EXPLORATION] = 0;

        cardsTypeList[STRUCTURE] = 0;
        cardsTypeList[VEHICLE] = 0;
        cardsTypeList[RESEARCH] = 0;
        cardsTypeList[PROJECT] = 0;
        cardsTypeList[DISCOVERY] = 0;
    }

    /// @brief Destructor of the class Player
    Player::~Player()
    {
        this->empire->~EmpireCard();
        
        for(DevelopmentCard* card : builtCards)
        {
            card->~DevelopmentCard();
        }
        this->builtCards.clear();

        for(DevelopmentCard* card : toBuildCards)
        {
            card->~DevelopmentCard();
        }
        this->toBuildCards.clear();

        for(DevelopmentCard* card : draftingCards)
        {
            card->~DevelopmentCard();
        }
        this->draftingCards.clear();

        for(DevelopmentCard* card : draftCards)
        {
            card->~DevelopmentCard();
        }
        this->draftCards.clear();

        this->resourcesProduction.clear();
        this->cardsTypeList.clear();

        delete(this);
    }

    /// @brief Construct the card "cardToBuild"
    /// @param cardToBuild The card to build
    void Player::construct(DevelopmentCard* cardToBuid)
    {
        this->builtCards.push_back(cardToBuid);
        this->toBuildCards.erase(std::remove(this->toBuildCards.begin(), this->toBuildCards.end(), cardToBuid), this->toBuildCards.end());
        this->cardsTypeList[cardToBuid->getType()]++;
        this->updateProduction();

        this->notifyObservers();
    }

    /// @brief Add a resource "resource" to the card "card"
    /// @param resource Resource placed on the card "card"
    /// @param card Card that will receive the resource "resource"
    void Player::addResource(ResourceType resource, DevelopmentCard* card)
    {

		auto cardPos = std::find(this->toBuildCards.begin(), this->toBuildCards.end(), card);
		if(cardPos != toBuildCards.end())
        {
            //Check if the resource is addable to the designated card
            if((*cardPos)->isResourceAddable(resource))
            {
                //Adding the resource to the card, and building it if there are all the resources required on it.
                if((*cardPos)->addResource(resource))
                {
                    construct(*cardPos);
                    toBuildCards.erase(cardPos);
                }
            }
        }
    }

    /// @brief Discard the card "toDiscardCard"
    /// @param toDiscardCard Card that is going to be discarded
    void Player::discardCard(DevelopmentCard* toDiscardCard)
    {
		auto cardPos = std::find(this->draftCards.begin(), this->draftCards.end(), toDiscardCard);
        if(cardPos != this->draftCards.end())
        {
            this->currentResources.push_back(toDiscardCard->getDiscardGain());
            this->draftCards.erase(cardPos);
        }
        else
        {
            cardPos = std::find(this->toBuildCards.begin(), this->toBuildCards.end(), toDiscardCard);
            if(cardPos != this->toBuildCards.end())
            {
                sendResourceToEmpire(toDiscardCard->getDiscardGain());
                convertToKrystallium();
                this->toBuildCards.erase(cardPos);
            }
        }

        this->notifyObservers();
    }

    /// @brief Function called when the player wants to keep a card from the drafting phase.
    /// @param toKeepCard Card to keep
    void Player::keepCard(DevelopmentCard* toKeepCard)
    {
        auto cardPos = std::find(this->draftCards.begin(), this->draftCards.end(), toKeepCard);
        if(cardPos != this->draftCards.end())
        {
            this->toBuildCards.push_back(toKeepCard);
            this->draftCards.erase(cardPos);
        }

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
        for(DevelopmentCard* card : this->builtCards)
        {
            for(ResourceToProduce* resource : card->getProductionGain())
            {
                if(resource->type == resourceToProduce)
                {
                    if(resource->cardType != NONETYPE)
                    {
                        productionValue += (resource->quantity)*cardsTypeList.at(resource->cardType);
                    }
                }
                else
                {
                        productionValue += resource->quantity;
                   
                }
            } 
        }

        for(ResourceToProduce* resource : this->empire->getProductionGain())
        {
            if(resource->type == resourceToProduce)
            {
                if(resource->cardType != NONETYPE)
                {
                    productionValue += (resource->quantity)*cardsTypeList.at(resource->cardType);
                }
            }
            else
            {
                    productionValue += resource->quantity;           
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

            if(cardVictoryPoints->cardOrResourceType == 0)
            {
                victoryPoints += cardVictoryPoints->numberOfPoints;
            }
            else if(cardVictoryPoints->cardOrResourceType == COLONEL)
            {
                victoryPoints += cardVictoryPoints->numberOfPoints * this->colonelTokensUnit;
            }
            else if(cardVictoryPoints->cardOrResourceType == FINANCIER)
            {
                victoryPoints += cardVictoryPoints->numberOfPoints * this->financierTokensUnit;
            }
            else if(20 < cardVictoryPoints->cardOrResourceType and cardVictoryPoints->cardOrResourceType < 30)
            {
                victoryPoints += (cardVictoryPoints->numberOfPoints) * this->cardsTypeList.at((state::CardType)(cardVictoryPoints->cardOrResourceType));
            }
        }

        CardVictoryPoint* empireVictoryPoints = this->empire->getVictoryPoints();
        if(empireVictoryPoints->cardOrResourceType == 0)
        {
            victoryPoints += empireVictoryPoints->numberOfPoints;
        }
        else if(empireVictoryPoints->cardOrResourceType == COLONEL)
        {
            victoryPoints += empireVictoryPoints->numberOfPoints * this->colonelTokensUnit;
        }
        else if(empireVictoryPoints->cardOrResourceType == FINANCIER)
        {
            victoryPoints += empireVictoryPoints->numberOfPoints * this->financierTokensUnit;
        }
        else if(20 < empireVictoryPoints->cardOrResourceType and empireVictoryPoints->cardOrResourceType < 30)
        {
            victoryPoints += (empireVictoryPoints->numberOfPoints) * this->cardsTypeList.at((state::CardType)empireVictoryPoints->cardOrResourceType);
        }

        return victoryPoints;
    }

    /// @brief Take a resource produced by the player and place it on the Empire of the player
    /// @param resource Type of resource that one will be send to the empire card of the player
    void Player::sendResourceToEmpire(ResourceType resource)
    {
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

    /// @brief Add the selected card "card" from the drafting deck to the selected one
    /// @param card Card choosed by the player
    void Player::chooseDraftCard(DevelopmentCard* card)
    {
        auto cardPos = std::find(this->draftingCards.begin(), this->draftingCards.end(), card);
        if(cardPos != draftingCards.end())
        {
            this->draftCards.push_back(card);
            this->draftingCards.erase(cardPos);
            this->state = PENDING;
        }

        this->notifyObservers();
    }

    /// @brief Return the selected token by the player (Colonel/Financier)
    /// Not implementable as it ask to know on which one does the player clicks.
    /// @return Boolean returned by the choice of the player (true => Colonel, false => Financier)
    bool Player::chooseColonelToken() const
    {
        return false ;
    }
    
    /// @brief Receive resource from the game.
    /// @param resourceToReceive Resource to add to the player.
    void Player::receiveResource (ResourceType resourceToReceive)
    {
        this->currentResources.push_back(resourceToReceive);

        this->notifyObservers();
    }
    
    /// @brief Receive multiple resources from the game
    /// @param resourceToReceive Type of the resource to receive.
    /// @param numberOfResources Number of ressources to receive.
    void Player::receiveResources (ResourceType resourceToReceive, int numberOfResources)
    {
        for (int i = 0; i < numberOfResources ; i++)
        {
            this->currentResources.push_back(resourceToReceive);
        }

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

    /// @brief Setter for the empire card
    /// @param empire Empire to give to the player
    void Player::setEmpire(EmpireCard* empire)
    {
        this->empire = empire;

        this->notifyObservers();
    }

    /// @brief Setter for the drafting deck
    /// @param draft drafting deck to give to the player
    void Player::setDraftingCards(std::vector<DevelopmentCard*> draft)
    {
        for(DevelopmentCard* card : draft)
        {
            this->draftingCards.push_back(card);
        }

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
    sf::Texture Player::getProfilePicture () const
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
}
