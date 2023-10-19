#include "EmpireCard.h"


namespace state {

    /// @brief Empty constructor for the EmpireCard class
    EmpireCard::EmpireCard() :
    Card(),
    productionGainAdvanced({}),
    victoryPointsAdvanced({})
    {
        this->empire = AFRICA;
    }

    /// @brief Full constructor for the EmpireCard class
    /// @param name Name of the empire
    /// @param productionGain Production provided by the empire
    /// @param victoryPoints Victory points provided by the empire
    /// @param design Sprite of the empire card
    /// @param productionGainAdvanced Advanced production provided by the empire
    /// @param victoryPointsAdvanced Advanced victory points provided by the empire
    /// @param empire Region the empire belongs to
    EmpireCard::EmpireCard(std::string name, std::vector<ResourceToProduce*> productionGain, sf::Texture design, std::vector<CardVictoryPoint*> victoryPoints, std::vector<ResourceToProduce*> productionGainAdvanced, std::vector<CardVictoryPoint*> victoryPointsAdvanced, EmpireLand* empire) :
    Card(name, productionGain, design, victoryPoints),
    productionGainAdvanced(productionGainAdvanced),
    victoryPointsAdvanced(victoryPointsAdvanced),
    empire(AFRICA)
    {
    }
    
    /// @brief Destructor for the EmpireCard class
    EmpireCard::~EmpireCard ()
    {

    }

    /// @brief Convert the current EmpireCard to a readable string.
    /// @return String returned after conversion
    std::string EmpireCard::toString () const
    {
        return "";
    }
}