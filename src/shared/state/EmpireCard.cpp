#include "EmpireCard.h"
#include "CreateJSONFormatStructures.h"

namespace state {

    /// @brief Create an empire card from a json file.
    EmpireCard::EmpireCard(Json::Value jsonValue) :
        Card(jsonValue)
    {
        // Retrieve productionGainFaceB from the JSON.
        this->productionGainFaceB = {};
        if (jsonValue["productionGainFaceB"].isArray())
        {
            const Json::Value productionFaceBArray = jsonValue["productionGainFaceB"];
        
            for (const Json::Value& jsonStruct : productionFaceBArray)
            {
                this->productionGainFaceB.push_back(CreateJSONFormatStructures::resourceToProduceFromJSON(jsonStruct));
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
    EmpireCard::EmpireCard (std::string name, constants::resourceProdList productionGain, constants::victoryPointsPtr victoryPoints, constants::resourceProdList productionGainFaceB, EmpireLand empire, bool isFaceA) :
        Card(name, productionGain, victoryPoints),
        empire(empire),
        isFaceA(isFaceA)
    {
        for(constants::resourceProdPtr resource : productionGainFaceB)
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
    EmpireCard::EmpireCard (std::string name, constants::resourceProdList productionGain, std::string relativePathToTexture, constants::victoryPointsPtr victoryPoints, constants::resourceProdList productionGainFaceB, EmpireLand empire, std::string relativePathToTextureFaceB, bool isFaceA) :
        Card(name, productionGain, relativePathToTexture, victoryPoints),
        empire(empire),
        isFaceA(isFaceA),
        relativePathToTextureFaceB(relativePathToTextureFaceB)
    {
        for(constants::resourceProdPtr resource : productionGainFaceB)
        {
            this->productionGainFaceB.push_back(resource);
        }
    }
    
    /// @brief Destructor for the EmpireCard class
    EmpireCard::~EmpireCard ()
    {
    }

    ///@brief Convert the Empire to a JSON format. Usefull when the game is saved.
	///@return Readable JSON of the empire.
    Json::Value EmpireCard::toJSON () const
    {
        // Instanciation of the empire card into a JSON format.
        Json::Value empireCardJSON = Card::toJSON();
        
        // Serialize the vector of the cost to build
        Json::Value productionGainFaceBArray;
        for (const constants::resourceProdPtr& prodGain : this->productionGainFaceB)
        {
            productionGainFaceBArray.append(CreateJSONFormatStructures::jsonOfResourceToProduce(*prodGain));
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
    constants::resourceProdList EmpireCard::getProductionGain () const
    {
        if (isFaceA)
        {
            return this->productionGain;
        }
        return this->productionGainFaceB;
    }

    /// @brief Number of victory points, according to the face that is played.
    /// @return Victory points of the Empire.
    constants::victoryPointsPtr EmpireCard::getVictoryPoints () const
    {
        if (this->isFaceA)
        {
            return this->victoryPoints;
        }
        return nullptr;
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