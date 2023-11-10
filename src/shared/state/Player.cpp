#include "Player.h"
#include <map>

namespace state {

    /// @brief Constructor of the class Player
    Player::Player() :
    name(""),
    id(-1),
    profilePicture(sf::Texture()),
    empire(new EmpireCard()),
    builtCards({}),
    toBuildCards({}),
    draftingCards({}),
    draftCards({}),
    state(PENDING),
    financierTokensUnit(0),
    colonelTokensUnit(0),
    krystalliumTokensUnit(0),
    currentResources({}),
	resourcesInEmpireUnit(0)
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

    }

    /// @brief Construct the card "cardToBuild"
    /// @param cardToBuild The card to build
    void Player::construct(DevelopmentCard* cardToBuid)
    {
        this->builtCards.push_back(cardToBuid);
        this->toBuildCards.erase(std::remove(this->toBuildCards.begin(), this->toBuildCards.end(), cardToBuid), this->toBuildCards.end());
        this->cardsTypeList[cardToBuid->getType()]++;
        updateProduction();
        
    }

    /// @brief Add a resource "resource" to the card "card"
    /// @param resource Resource placed on the card "card"
    /// @param card Card that will receive the resource "resource"
    void Player::addResource(Resource* resource, DevelopmentCard* card)
    {
        //Check if the resource is addable to the designated card
        if(card->isResourceAddable(resource))
        {
            //Adding the resource to the card, and building it if there are all the resources required on it.
            if(card->addResource(resource))
            {
                construct(card);
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
    }

    void Player::updateProduction()
    {
        this->resourcesProduction[MATERIAL] = computeProduction(MATERIAL);
        this->resourcesProduction[ENERGY] = computeProduction(ENERGY);
        this->resourcesProduction[SCIENCE] = computeProduction(SCIENCE);
        this->resourcesProduction[GOLD] = computeProduction(GOLD);
        this->resourcesProduction[EXPLORATION] = computeProduction(EXPLORATION);
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
    void Player::sendResourceToEmpire(Resource* resource)
    {
        this->resourcesInEmpireUnit++;
        delete(resource);
    }

    /// @brief Converts the empire's resources into a krystallium when it reaches 5 resources
    void Player::convertToKrystallium()
    {
        if(this->resourcesInEmpireUnit == 5)
        {
            this->resourcesInEmpireUnit -= 5;
            this->krystalliumTokensUnit++;
        }
    }

    /// @brief Add the selected card "card" from the drafting deck to the selected one
    /// @param card Card choosed by the player
    void Player::chooseDraftCard(DevelopmentCard* card)
    {
            this->draftCards.push_back(card);
            auto cardPos = std::find(this->draftingCards.begin(), this->draftingCards.end(), card);
            this->draftingCards.erase(cardPos);
            this->state = PENDING;
    }

    /// @brief Return the selected token by the player (Colonel/Financier)
    /// Not implementable as it ask to know on which one does the player clicks.
    /// @return Boolean returned by the choice of the player (true => Colonel, false => Financier)
    bool Player::chooseColonelToken() const
    {
        return false;
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
}
