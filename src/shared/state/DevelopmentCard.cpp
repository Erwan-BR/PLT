#include "DevelopmentCard.h"
#include "CreateJSONFormatStructures.h"

namespace state {
    /// @brief Create a development card from a json file.
    DevelopmentCard::DevelopmentCard (Json::Value jsonValue) :
        Card(jsonValue)
    {
        this->type = static_cast<CardType> (jsonValue["type"].asInt());

        this->numberOfCopies = jsonValue["numberOfCopies"].asInt();

        CreateJSONFormatStructures* createInformations = new CreateJSONFormatStructures;

        // Retrieve production gain from the JSON.
        this->costToBuild = {};
        if (jsonValue["costToBuild"].isArray())
        {
            const Json::Value costToBuildArray = jsonValue["costToBuild"];
            for (const Json::Value& jsonStruct : costToBuildArray)
            {
                this->costToBuild.push_back(createInformations->resourceToPayFromJSON(jsonStruct));
            }
        }

        // Retrieve instant gain
        this->instantGain = {};
        if (jsonValue["instantGain"].isArray())
        {
            const Json::Value& instantGainArray = jsonValue["instantGain"];

            for (unsigned int i = 0; i < instantGainArray.size(); ++i)
            {
                this->instantGain.push_back(static_cast<ResourceType>(instantGainArray[i].asInt()));
            }
        }

        this->discardGain = static_cast<ResourceType> (jsonValue["discardGain"].asInt());
        this->isPaid = jsonValue["isPaid"].asBool();
        this->quantityResourceMissing = jsonValue["quantityResourceMissing"].asInt();
    }

    /// @brief Full constructor of the DevelopmentCard class.
    /// @param name Name of the Card.
    /// @param productionGain Production of the Card at each turn.
    /// @param relativePathOfTexture Relative path of the image that represent the card.
    /// @param victoryPoints Structures that inform how the card can make some points.
    /// @param type Type of the card.
    /// @param numberOfCopies Number of copies of this card in the game.
    /// @param costToBuild Vector that contains all the resources to pay to build the Card.
    /// @param instantGain Vector that contains all the resources won at the construction of the Card.
    /// @param discardGain Pointers to the resources you get when the Card is discarded.
    DevelopmentCard::DevelopmentCard (std::string name, std::vector<ResourceToProduce*> productionGain, std::string relativePathOfTexture, CardVictoryPoint* victoryPoints, CardType type, int numberOfCopies, std::vector<ResourceToPay*> costToBuild, std::vector<ResourceType> instantGain, ResourceType discardGain) :
        Card(name, productionGain, relativePathOfTexture, victoryPoints),
        type(type),
        numberOfCopies(numberOfCopies),
        instantGain(instantGain),
        discardGain(discardGain),
        quantityResourceMissing((int)costToBuild.size()) // Because no resource is paid and the size is never 0.
    {
        for(ResourceToPay* resource : costToBuild)
        {
            this->costToBuild.push_back(resource);
        }
    }

    /// @brief Full constructor of the DevelopmentCard class.
    /// @param name Name of the Card.
    /// @param productionGain Production of the Card at each turn.
    /// @param victoryPoints Structures that inform how the card can make some points.
    /// @param type Type of the card.
    /// @param numberOfCopies Number of copies of this card in the game.
    /// @param costToBuild Vector that contains all the resources to pay to build the Card.
    /// @param instantGain Vector that contains all the resources won at the construction of the Card.
    /// @param discardGain Pointers to the resources you get when the Card is discarded.
    DevelopmentCard::DevelopmentCard (std::string name, std::vector<ResourceToProduce*> productionGain, CardVictoryPoint* victoryPoints, CardType type, int numberOfCopies, std::vector<ResourceToPay*> costToBuild, std::vector<ResourceType> instantGain, ResourceType discardGain) :
        Card(name, productionGain, victoryPoints),
        type(type),
        numberOfCopies(numberOfCopies),
        instantGain(instantGain),
        discardGain(discardGain),
        quantityResourceMissing((int)costToBuild.size()) // Because no resource is paid and the size is never 0.
    {
        for(ResourceToPay* resource : costToBuild)
        {
            this->costToBuild.push_back(resource);
        }
    }

    /// @brief Destructor of the DevelopmentCard class.
    DevelopmentCard::~DevelopmentCard ()
    {
        Card::~Card();
        
        for(ResourceToPay* resource : this->costToBuild)
        {
            delete(resource);
        }
    }

    /// @brief Add a ressource into the Card. The resource must be addable. Should also update the quantity and the isPaid value.
    /// @param resource Resource that will be added to the Card.
    /// @return True if the card is just payed. False either.
    bool DevelopmentCard::addResource (ResourceType resource)
    {
        for (ResourceToPay* resourceToPay : this->costToBuild)
        {
            // Checking if the current resource is not paid, and if the type is the one of the input parameter.
            if ((!resourceToPay->isPaid) && (resourceToPay->type == resource))
            {
                resourceToPay->isPaid = true;
                this->notifyObservers();
                return (this->decreaseResourceUnitNeeded());
            } 
        }
        // The following line should never be reached.
        return false;
    }

    /// @brief Check if a resource can be added to the DevelopmentCard.
    /// @param resource The resource we want to know if it is addable.
    /// @return True if the resource can be added to the Card, else False.
    bool DevelopmentCard::isResourceAddable (ResourceType resource) const
    {
        // First, if a card is Paid, ressources can't be added.
        if (this->isPaid)
        {
            return false;
        }
        // If this line is reached, the card is not paid.

        // Iterating among all resources that should be paid
        for (ResourceToPay* resourceToPay : this->costToBuild)
        {
            // If the current ressource is not paid, we check if the resource can be added.
            if (!resourceToPay->isPaid)
            {
                // If both types are the same, resource can be added.
                if (resourceToPay->type == resource)
                {
                    return true;
                }
            }
        }
        // If this line is reached, it means that none of the ressources to pay may be paid. 
        return false;
    }
    
    /// @brief Decrease the amount of resource of unit needed. Also update the isPaid boolean if needed.
    /// @return True if the card is just payed. False either.
    bool DevelopmentCard::decreaseResourceUnitNeeded ()
    {
        // Decrease the quantity of ressource which are missing.
        this->quantityResourceMissing--;

        // Update the isPaid attribute according to the quantity of ressources that must be paid.
        this->isPaid = (this->quantityResourceMissing == 0);
        
        // Return the boolean isPaid to know if everything as been paid.
        return this->isPaid; 
    }

    ///@brief Convert the Development card to a JSON format. Usefull when the game is saved.
	///@return Readable JSON of the development card.
    Json::Value DevelopmentCard::toJSON () const
    {
        // Instanciation of the card into a JSON format.
        Json::Value devCardJSON = Card::toJSON();

        devCardJSON["type"] = static_cast<int>(this->type);

        devCardJSON["numberOfCopies"] = this->numberOfCopies;

        CreateJSONFormatStructures* createInformations = new CreateJSONFormatStructures;

        // Serialize the vector of the cost to build
        Json::Value costArray;
        for (const ResourceToPay* prodGain : this->costToBuild)
        {
            costArray.append(createInformations->jsonOfResourceToPay(*prodGain));
        }
        devCardJSON["costToBuild"] = costArray;

        // Serialize the vector of the cost to build
        Json::Value instantGainArray;
        for (const ResourceType instantGainValue : this->instantGain)
        {
            instantGainArray.append(static_cast<int>(instantGainValue));
        }
        devCardJSON["instantGain"] = instantGainArray;

        devCardJSON["discardGain"] = this->discardGain;

        devCardJSON["isPaid"] = this->isPaid;

        devCardJSON["quantityResourceMissing"] = this->quantityResourceMissing;

        return devCardJSON;
    }

    /************************************* Setters & Getters *************************************/

    /// @brief Get the discard Gain. USefull for the Player class.
    /// @return Pointer to the ressource of the discard gain.
    ResourceType DevelopmentCard::getDiscardGain () const
    {
        return this->discardGain;
    }

    /// @brief Getter for the type attribute.
    /// @return type attribute.
    CardType DevelopmentCard::getType() const
    {
        return this->type;
    }

    /// @brief Getter for the cost to build.
    /// @return Cost to build.
    std::vector<ResourceToPay*> DevelopmentCard::getCostToBuild() const
    {
        return this->costToBuild;
    }

    /// @brief Gettter for the instant gain of the card (gain when the card is constructed.)
    /// @return Instant gain of the card.
    std::vector<ResourceType> DevelopmentCard::getInstantGain() const
    {
        return this->instantGain;
    }

    /// @brief Get the number of resources that needs to be paid on this card.
    /// @return Number of resources to pay on this card.
    int DevelopmentCard::getQuantityResourcesMissing () const
    {
        int quantityResourcesMissing = 0;
        if (this->isPaid)
        {
            return 0;
        }
        for (ResourceToPay* resourceToPay : this->costToBuild)
        {
            if (! resourceToPay->isPaid)
            {
                quantityResourcesMissing ++;
            }
        }
        return quantityResourcesMissing;
    }
}