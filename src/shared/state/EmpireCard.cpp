#include "EmpireCard.h"

namespace state {

    /// @brief Create an empire card from a json file.
    EmpireCard::EmpireCard(Json::Value jsonValue) :
        Card(jsonValue)
    {
        // To-Do
    }

    /// @brief Full constructor for the EmpireCard class
    /// @param name Name of the empire
    /// @param productionGain Production provided by the empire
    /// @param victoryPoints Victory points provided by the empire
    /// @param design Sprite of the empire card
    /// @param productionGainAdvanced Advanced production provided by the empire
    /// @param victoryPointsAdvanced Advanced victory points provided by the empire
    /// @param empire Region the empire belongs to
    /// @param designFaceB Design of the backside of the card.
    EmpireCard::EmpireCard(std::string name, std::vector<ResourceToProduce*> productionGain, sf::Texture* design, CardVictoryPoint* victoryPoints, std::vector<ResourceToProduce*> productionGainAdvanced, CardVictoryPoint* victoryPointsAdvanced, EmpireLand empire, sf::Texture* designFaceB, bool isFaceA) :
        Card(name, productionGain, design, victoryPoints),
        victoryPointsAdvanced(victoryPointsAdvanced),
        empire(empire),
        designFaceB(designFaceB),
        isFaceA(isFaceA)
    {
        for(ResourceToProduce* resource : productionGainAdvanced)
        {
            this->productionGainAdvanced.push_back(resource);
        }
    }

    /// @brief Full constructor for the EmpireCard class
    /// @param name Name of the empire
    /// @param productionGain Production provided by the empire
    /// @param victoryPoints Victory points provided by the empire
    /// @param relativePathOfTexture Path to find the image of the player face A of the card.
    /// @param productionGainAdvanced Advanced production provided by the empire
    /// @param victoryPointsAdvanced Advanced victory points provided by the empire
    /// @param empire Region the empire belongs to
    /// @param relativePathOfTextureFaceB Path to find the image of the player face B of the card.
    EmpireCard::EmpireCard (std::string name, std::vector<ResourceToProduce*> productionGain, std::string relativePathOfTexture, CardVictoryPoint* victoryPoints, std::vector<ResourceToProduce*> productionGainAdvanced, CardVictoryPoint* victoryPointdAdvanced, EmpireLand empire, std::string relativePathOfTextureFaceB, bool isFaceA) :
        Card(name, productionGain, relativePathOfTexture, victoryPoints),
        victoryPointsAdvanced(victoryPointdAdvanced),
        empire(empire),
        isFaceA(isFaceA),
        relativePathOfTextureFaceB(relativePathOfTextureFaceB)
    {
        this->designFaceB = new sf::Texture;
        this->designFaceB->loadFromFile(relativePathOfTextureFaceB);
        
        for(ResourceToProduce* resource : productionGainAdvanced)
        {
            this->productionGainAdvanced.push_back(resource);
        }
    }
    
    /// @brief Destructor for the EmpireCard class
    EmpireCard::~EmpireCard ()
    {
        delete(this->victoryPointsAdvanced);
        for(ResourceToProduce* resource : productionGainAdvanced)
        {
            delete(resource);
        }
    }

    ///@brief Convert the Empire to a JSON format. Usefull when the game is saved.
	///@return Readable JSON of the empire.
    Json::Value EmpireCard::toJSON () const
    {
        // Instanciation of the empire card into a JSON format.
        Json::Value empireCardJSON;

        return empireCardJSON;
    }

    /************************************* Setters & Getters *************************************/

    /// @brief Getter for the deisgn of the face B.
    /// @return Design of the face B.
    sf::Texture* EmpireCard::getDesignFaceB () const
    {
        return this->designFaceB;
    }

    /// @brief Returns the production gain, according to the face that is played.
    /// @return Production gain of the Empire.
    std::vector<ResourceToProduce*> EmpireCard::getProductionGain () const
    {
        if (isFaceA)
        {
            return this->productionGain;
        }
        return this->productionGainAdvanced;
    }

    /// @brief Number of victory points, according to the face that is played.
    /// @return Victory points of the Empire.
    CardVictoryPoint* EmpireCard::getVictoryPoints () const
    {
        if (isFaceA)
        {
            return this->victoryPoints;
        }
        return this->victoryPointsAdvanced;
    }

    /// @brief Retrieve the path of the texture of the second face of the card.
    /// @return Path to the design of the face B.
    std::string EmpireCard::getRelativePathOfTextureFaceB () const
    {
        return this->relativePathOfTextureFaceB;
    }
}