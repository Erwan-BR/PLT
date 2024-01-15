#include "Card.h"
#include "CreateJSONFormatStructures.h"

namespace state {

    /// @brief Create a card from a json file.
    Card::Card(Json::Value jsonValue) :
        Observable()
    {
        // Retrive name.
        this->name = jsonValue["name"].asString();

        // Retrieve production gain from the JSON.
        this->productionGain = {};
        if (jsonValue["productionGain"].isArray())
        {
            const Json::Value productionArray = jsonValue["productionGain"];
        
            for (const Json::Value& jsonStruct : productionArray)
            {
                this->productionGain.push_back(CreateJSONFormatStructures::resourceToProduceFromJSON(jsonStruct));
            }
        }
        
        // Retrieve victory points
		this->victoryPoints = CreateJSONFormatStructures::cardVictoryPointFromJSON(jsonValue["victoryPoints"]);

        // To-do : Use path of images to store it as an attribute, to retrive it and replace folowing lines.
        this->relativePathToTexture = jsonValue["relativePathToTexture"].asString();
    }

    /// @brief Create a card with all information that concerned this card.
    /// @param name Name of the card that will be displayed.
    /// @param productionGain Represent what kind of resource the card can bring.
    /// @param relativePathToTexture Path of the design of the card.
    /// @param victoryPoints Represent what kind of points the card can bring.
    Card::Card (std::string name, constants::resourceProdList productionGain, std::string relativePathToTexture, constants::victoryPointsPtr victoryPoints) :
        Observable(),
        name(name),
        victoryPoints(victoryPoints),
        relativePathToTexture(relativePathToTexture)
    {        
        for(constants::resourceProdPtr resource : productionGain)
        {
            this->productionGain.push_back(resource);
        }
    }

    /// @brief Create a card with all information that concerned this card.
    /// @param name Name of the card that will be displayed.
    /// @param productionGain Represent what kind of resource the card can bring.
    /// @param victoryPoints Represent what kind of points the card can bring.
    Card::Card (std::string name, constants::resourceProdList productionGain, constants::victoryPointsPtr victoryPoints) :
        Observable(),
        name(name),
        victoryPoints(victoryPoints)
    {        
        for(constants::resourceProdPtr resource : productionGain)
        {
            this->productionGain.push_back(resource);
        }
    }

    /// @brief Card destructor
    Card::~Card()
    {
    }

    ///@brief Convert the Card to a JSON format. Usefull when the game is saved.
	///@return Readable JSON of the card.
    Json::Value Card::toJSON () const
    {
        // Instanciation of the card into a json format.
        Json::Value cardJson;

        // Writing basic information
        cardJson["name"] = this->name;

        // Serialize the vector of resources to produce
        Json::Value productionArray;
        for (const constants::resourceProdPtr& prodGain : this->productionGain)
        {
            productionArray.append(CreateJSONFormatStructures::jsonOfResourceToProduce(*prodGain));
        }
        cardJson["productionGain"] = productionArray;

        cardJson["victoryPoints"] = CreateJSONFormatStructures::jsonOfCardVictoryPoint(*(this->victoryPoints));

        cardJson["relativePathToTexture"] = this->relativePathToTexture;

        return cardJson;
    }

    /************************************* Setters & Getters *************************************/

    /// @brief Get the name of the Card.
    /// @return name of the card
    std::string Card::getName () const
    {
        return this->name;
    }

    /// @brief Get the vector of resource to produce of the cards.
    /// @return Ressources produced by the card.
    constants::resourceProdList Card::getProductionGain () const
    {
        return this->productionGain;
    }

    /// @brief Get how much points the card allows to win, according to the type of the object to have.
    /// @return Pointers to CardVictoryPoint.
    constants::victoryPointsPtr Card::getVictoryPoints () const
    {
        return this->victoryPoints;
    }

    /// @brief Get the relative path of the design of the card.
    /// @return Relative path to the design of the card.
    std::string Card::getRelativePathToTexture () const
    {
        return this->relativePathToTexture;
    }
}