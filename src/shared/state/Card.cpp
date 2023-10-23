#include "Card.h"

namespace state {

    /// @brief Create an empty card
    Card::Card() :
    name(""),
    productionGain({}),
    design(sf::Texture()),
    victoryPoints({})
    {
    }

    /// @brief Create a card
    Card::Card(std::string name, std::vector<ResourceToProduce*> productionGain, sf::Texture design, CardVictoryPoint* victoryPoints)
    {
        this->name = name;
        this->productionGain = productionGain;
        this->design = design;
        this->victoryPoints = victoryPoints;
    }

    /// @brief Card destructor
    Card::~Card()
    {
    }

    /*

    The following lines were used when dia2code automatically generated setters and getters. As we no longer wish to do this, we'll comment on these lines.
    These lines can be uncommented if required.


    /// @brief Gets the name
    /// @return Returns the name of the card
    const std::string& Card::getName() const
    {
        return this->name;
    }

    /// @brief Sets the name
    /// @param name New name of the card
    void Card::setName(const std::string& name)
    {
        this->name = name;
    }

    /// @brief Gets the productionGain
    /// @return Returns the productionGain of the card
    const std::vector<ResourceToProduce*>& Card::getProductionGain() const
    {
        return this->productionGain;
    }

    /// @brief Sets the productionGain
    /// @param productionGain New productionGain of the card
    void Card::setProductionGain(const std::vector<ResourceToProduce*>& productionGain)
    {
        this->productionGain = productionGain;
    }

    /// @brief Gets the design
    /// @return Returns the design of the card
    const sf::Texture& Card::getDesign() const
    {
        return this->design;
    }

    /// @brief Sets the design
    /// @param design New design of the card
    void Card::setDesign(const sf::Texture& design)
    {
        this->design = design;
    }

    /// @brief Gets the victoryPoints
    /// @return Returns the victoryPoints of the card
    const CardVictoryPoint*& Card::getVictoryPoints() const
    {
        return (const CardVictoryPoint*&)(this->victoryPoints);
    }

    /// @brief Sets the victoryPoints
    /// @param victoryPoints New victoryPoints of the card
    void Card::setVictoryPoints(const CardVictoryPoint*& victoryPoints)
    {
        this->victoryPoints = (CardVictoryPoint*)victoryPoints;
    }

    */
}