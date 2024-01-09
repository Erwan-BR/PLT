#include "EmpireCard.h"
#include "CreateJSONFormatStructures.h"

namespace state {

    /// @brief Create an empire card from a json file.
    EmpireCard::EmpireCard(Json::Value jsonValue) :
        Card(jsonValue)
    {
        CreateJSONFormatStructures* createInformations = new CreateJSONFormatStructures;

        // Retrieve productionGainFaceB from the JSON.
        this->productionGainFaceB = {};
        if (jsonValue["productionGainFaceB"].isArray())
        {
            const Json::Value productionFaceBArray = jsonValue["productionGainFaceB"];
        
            for (const Json::Value& jsonStruct : productionFaceBArray)
            {
                this->productionGainFaceB.push_back(createInformations->resourceToProduceFromJSON(jsonStruct));
            }
        }

        this->empire = static_cast<EmpireLand> (jsonValue["empire"].asInt());

        this->relativePathToTextureFaceB = jsonValue["relativePathToTextureFaceB"].asString();

        this->isFaceA = jsonValue["isFaceA"].asBool();
    }

    /// @brief Full constructor for the EmpireCard class
    /// @param name Name of the empire
    /// @param productionGain Production provided by the empire
    /// @param victoryPoints Victory points provided by the empire
    /// @param productionGainFaceB FaceB production provided by the empire
    /// @param empire Region the empire belongs to
    EmpireCard::EmpireCard (std::string name, std::vector<ResourceToProduce*> productionGain, CardVictoryPoint* victoryPoints, std::vector<ResourceToProduce*> productionGainFaceB, EmpireLand empire, bool isFaceA) :
        Card(name, productionGain, victoryPoints),
        empire(empire),
        isFaceA(isFaceA)
    {
        for(ResourceToProduce* resource : productionGainFaceB)
        {
            this->productionGainFaceB.push_back(resource);
        }
    }

    /// @brief Full constructor for the EmpireCard class
    /// @param name Name of the empire
    /// @param productionGain Production provided by the empire
    /// @param victoryPoints Victory points provided by the empire
    /// @param relativePathToTexture Path to find the image of the player face A of the card.
    /// @param productionGainFaceB FaceB production provided by the empire
    /// @param empire Region the empire belongs to
    /// @param relativePathToTextureFaceB Path to find the image of the player face B of the card.
    EmpireCard::EmpireCard (std::string name, std::vector<ResourceToProduce*> productionGain, std::string relativePathToTexture, CardVictoryPoint* victoryPoints, std::vector<ResourceToProduce*> productionGainFaceB, EmpireLand empire, std::string relativePathToTextureFaceB, bool isFaceA) :
        Card(name, productionGain, relativePathToTexture, victoryPoints),
        empire(empire),
        isFaceA(isFaceA),
        relativePathToTextureFaceB(relativePathToTextureFaceB)
    {
        for(ResourceToProduce* resource : productionGainFaceB)
        {
            this->productionGainFaceB.push_back(resource);
        }
    }
    
    /// @brief Destructor for the EmpireCard class
    EmpireCard::~EmpireCard ()
    {
        for(ResourceToProduce* resource : productionGainFaceB)
        {
            delete(resource);
        }
    }

    ///@brief Convert the Empire to a JSON format. Usefull when the game is saved.
	///@return Readable JSON of the empire.
    Json::Value EmpireCard::toJSON () const
    {
        // Instanciation of the empire card into a JSON format.
        Json::Value empireCardJSON = Card::toJSON();
        
        CreateJSONFormatStructures* createInformations = new CreateJSONFormatStructures;

        // Serialize the vector of the cost to build
        Json::Value productionGainFaceBArray;
        for (const ResourceToProduce* prodGain : this->productionGainFaceB)
        {
            productionGainFaceBArray.append(createInformations->jsonOfResourceToProduce(*prodGain));
        }
        empireCardJSON["productionGainFaceB"] = productionGainFaceBArray;

        empireCardJSON["empire"] = static_cast<int> (this->empire);
        empireCardJSON["isFaceA"] = this->isFaceA;
        empireCardJSON["relativePathToTextureFaceB"] = this->relativePathToTextureFaceB;

        return empireCardJSON;
    }

    /************************************* Setters & Getters *************************************/

    /// @brief Returns the production gain, according to the face that is played.
    /// @return Production gain of the Empire.
    std::vector<ResourceToProduce*> EmpireCard::getProductionGain () const
    {
        if (isFaceA)
        {
            return this->productionGain;
        }
        return this->productionGainFaceB;
    }

    /// @brief Number of victory points, according to the face that is played.
    /// @return Victory points of the Empire.
    CardVictoryPoint* EmpireCard::getVictoryPoints () const
    {
        if (isFaceA)
        {
            return this->victoryPoints;
        }
        return new CardVictoryPoint{};
    }

    /// @brief Retrieve the path of the texture of the second face of the card.
    /// @return Path to the design of the face B.
    std::string EmpireCard::getRelativePathToTexture () const
    {
        if (this->isFaceA)
        {
            return this->relativePathToTexture;
        }
        return this->relativePathToTextureFaceB;
    }
}