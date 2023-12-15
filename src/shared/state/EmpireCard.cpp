#include "EmpireCard.h"

namespace state {

    /// @brief Empty constructor for the EmpireCard class
    EmpireCard::EmpireCard() :
    Card(),
    productionGainAdvanced(),
    victoryPointsAdvanced(),
    empire(EmpireLand::AFRICA)
    {
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
    EmpireCard::EmpireCard(std::string name, std::vector<ResourceToProduce*> productionGain, sf::Texture design, CardVictoryPoint* victoryPoints, std::vector<ResourceToProduce*> productionGainAdvanced, CardVictoryPoint* victoryPointsAdvanced, EmpireLand empire, sf::Texture designFaceB) :
    Card(name, productionGain, design, victoryPoints),
    victoryPointsAdvanced(victoryPointsAdvanced),
    empire(empire),
    designFaceB(designFaceB)
    {
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

    /// @brief Convert the current EmpireCard to a readable string.
    /// @return String returned after conversion
    std::string EmpireCard::toString () const
    {
        return "";
    }

    /************************************* Setters & Getters *************************************/

    /// @brief Getter for the deisgn of the face B.
    /// @return Design of the face B.
    sf::Texture EmpireCard::getDesignFaceB () const
    {
        return this->designFaceB;
    }
}