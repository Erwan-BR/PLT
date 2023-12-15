#include "Card.h"

namespace state {

    /// @brief Create an empty card
    Card::Card() :
    Observable(),
    name(""),
    productionGain(),
    design(new sf::Texture()),
    victoryPoints()
    {
    }

    /// @brief Create a card with all informations.
    Card::Card(std::string name, std::vector<ResourceToProduce*> productionGain, sf::Texture* design, CardVictoryPoint* victoryPoints) :
    Observable(),
    name(name),
    design(design),
    victoryPoints(victoryPoints)
    {
        for(ResourceToProduce* resource : productionGain){this->productionGain.push_back(resource);}
    }

    /// @brief Card destructor
    Card::~Card()
    {
        for(ResourceToProduce* resource : this->productionGain)delete(resource);
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
}