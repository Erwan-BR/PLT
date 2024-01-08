#include "Card.h"
#include "CreateJSONFormatStructures.h"

namespace state {

    /// @brief Create a card from a json file.
    Card::Card(Json::Value jsonValue) :
        Observable()
    {
        // Retrive name.
        this->name = jsonValue["name"].asString();

        CreateJSONFormatStructures* createInformations = new CreateJSONFormatStructures;

        // Retrieve production gain from the JSON.
        this->productionGain = {};
        if (jsonValue["productionGain"].isArray())
        {
            const Json::Value productionArray = jsonValue["productionGain"];
        
            for (const Json::Value& jsonStruct : productionArray)
            {
                this->productionGain.push_back(createInformations->resourceToProduceFromJSON(jsonStruct));
            }
        }
        
        // Retrieve victory points
		this->victoryPoints = createInformations->cardVictoryPointFromJSON(jsonValue["victoryPoints"]);

        // To-do : Use path of images to store it as an attribute, to retrive it and replace folowing lines.
        this->relativePathToTexture = jsonValue["relativePathToTexture"].asString();
        this->design = new sf::Texture;
        this->design->loadFromFile(this->relativePathToTexture);
    }

    /// @brief Create a card with all information that concerned this card.
    /// @param name Name of the card that will be displayed.
    /// @param productionGain Represent what kind of resource the card can bring.
    /// @param design Pointer to the design of the card, loaded in a texture.
    /// @param victoryPoints Represent what kind of points the card can bring.
    Card::Card (std::string name, std::vector<ResourceToProduce*> productionGain, sf::Texture* design, CardVictoryPoint* victoryPoints) :
        Observable(),
        name(name),
        design(design),
        victoryPoints(victoryPoints)
    {
        
        for(ResourceToProduce* resource : productionGain)
        {
            this->productionGain.push_back(resource);
        }
    }

    /// @brief Create a card with all information that concerned this card.
    /// @param name Name of the card that will be displayed.
    /// @param productionGain Represent what kind of resource the card can bring.
    /// @param relativePathToTexture Path of the design of the card.
    /// @param victoryPoints Represent what kind of points the card can bring.
    Card::Card (std::string name, std::vector<ResourceToProduce*> productionGain, std::string relativePathToTexture, CardVictoryPoint* victoryPoints) :
        Observable(),
        name(name),
        victoryPoints(victoryPoints),
        relativePathToTexture(relativePathToTexture)
    {
        this->design = new sf::Texture;
        this->design->loadFromFile(relativePathToTexture);
        
        for(ResourceToProduce* resource : productionGain)
        {
            this->productionGain.push_back(resource);
        }
    }

    /// @brief Card destructor
    Card::~Card()
    {
        for(ResourceToProduce* resource : this->productionGain)
        {
            delete(resource);
        }
    }

    ///@brief Convert the Card to a JSON format. Usefull when the game is saved.
	///@return Readable JSON of the card.
    Json::Value Card::toJSON () const
    {
        // Instanciation of the card into a json format.
        Json::Value cardJson;

        // Writing basic information
        cardJson["name"] = this->name;

        CreateJSONFormatStructures* createInformations = new CreateJSONFormatStructures;

        // Serialize the vector of resources to produce
        Json::Value productionArray;
        for (const ResourceToProduce* prodGain : this->productionGain)
        {
            productionArray.append(createInformations->jsonOfResourceToProduce(*prodGain));
        }
        cardJson["productionGain"] = productionArray;

        cardJson["victoryPoints"] = createInformations->jsonOfCardVictoryPoint(*(this->victoryPoints));

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
    std::vector<ResourceToProduce*> Card::getProductionGain () const
    {
        return this->productionGain;
    }

    /// @brief Get the design of the card.
    /// @return Design of the card.
    sf::Texture* Card::getDesign () const
    {
        return this->design;
    }

    /// @brief Get how much points the card allows to win, according to the type of the object to have.
    /// @return Pointers to CardVictoryPoint.
    CardVictoryPoint* Card::getVictoryPoints () const
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