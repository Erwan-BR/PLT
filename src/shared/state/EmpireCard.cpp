#include "EmpireCard.h"


namespace state {

    /// @brief Constructor 1 for the EmpireCard class
    EmpireCard::EmpireCard() :
    Card(),
    productiongainAdvanced({}),
    victoryPointsAdvanced({})
    {
        *(this->empire) = AFRICA;
    }

    /// @brief Constructor 2 for the EmpireCard class
    /// @param name : name of the empire
    /// @param productionGain : production provided by the empire
    /// @param victoryPoints : victory points provided by the empire
    /// @param design : sprite of the empire card
    /// @param productionGainAdvanced : advanced production provided by the empire
    /// @param victoryPointsAdvanced : advanced victory points provided by the empire
    /// @param empire : region the empire belongs to
    EmpireCard::EmpireCard(std::string name, std::vector<ResourceToProduce*> productionGain, sf::Texture design, std::vector<CardVictoryPoint*> victoryPoints, std::vector<ResourceToProduce*> productionGainAdvanced, std::vector<CardVictoryPoint*> victoryPointsAdvanced, EmpireLand* empire) :
    Card(name, productionGain, design, victoryPoints),
    productiongainAdvanced(productionGainAdvanced),
    victoryPointsAdvanced(victoryPointsAdvanced)
    {
        *(this->empire) = AFRICA;
    }
    
    /// @brief Destructor for the EmpireCard class
    EmpireCard::~EmpireCard ()
    {

    }

    /// @brief convert an attribute to string
    /// @return "" : string returned after conversion
    std::string EmpireCard::toString ()
    {
        return "";
    }

}