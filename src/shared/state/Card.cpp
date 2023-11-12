#include "Card.h"

namespace state {

    /// @brief Create an empty card
    Card::Card() :
    name(""),
    productionGain(),
    design(sf::Texture()),
    victoryPoints()
    {
    }

    /// @brief Create a card
    Card::Card(std::string name, std::vector<ResourceToProduce*> productionGain, sf::Texture design, CardVictoryPoint* victoryPoints) :
    name(name),
    productionGain(productionGain),
    design(design),
    victoryPoints(victoryPoints)
    {
    }

    /// @brief Card destructor
    Card::~Card()
    {
    }
}