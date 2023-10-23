#include "DevelopmentCard.h"

namespace state {

    /// @brief Empty constructor of the DevelopmentCard class.
    DevelopmentCard::DevelopmentCard () :
    Card(),
    type(CardType::NONETYPE),
    numberOfCopies(0),
    costToBuild({}),
    instantGain({}),
    discardGain(new Resource()),
    quantityResourceMissing(-1) // Should be computed correctly when the code will be implemented.
    {
    }

    /// @brief Full constructor of the DevelopmentCard class.
    /// @param name Name of the Card.
    /// @param productionGain Production of the Card at each turn.
    /// @param design Design of the Card.
    /// @param victoryPoints Structures that inform how the card can make some points.
    /// @param type Type of the card.
    /// @param numberOfCopies Number of copies of this card in the game.
    /// @param costToBuild Vector that contains all the resources to pay to build the Card.
    /// @param instantGain Vector that contains all the resources won at the construction of the Card.
    /// @param discardGain Pointers to the resources you get when the Card is discarded.
    DevelopmentCard::DevelopmentCard (std::string name, std::vector<ResourceToProduce*> productionGain, sf::Texture design, CardVictoryPoint* victoryPoints, CardType type, int numberOfCopies, std::vector<ResourceToPay*> costToBuild, std::vector<Resource*> instantGain, Resource* discardGain) :
    Card(name, productionGain, design, victoryPoints),
    type(CardType::NONETYPE),
    numberOfCopies(numberOfCopies),
    costToBuild(costToBuild),
    instantGain(instantGain),
    discardGain(discardGain),
    quantityResourceMissing(-1) // Should be computed correctly when the code will be implemented.
    {
    }

    /// @brief Destructor of the DevelopmentCard class.
    DevelopmentCard::~DevelopmentCard ()
    {
    }

    /// @brief Add a ressource into the Card. The resource must be addable.
    /// @param resource Resource that will be added to the Card.
    void DevelopmentCard::addResource (Resource* resource)
    {
        return;
    }

    /// @brief Check if a resource can be added to the DevelopmentCard.
    /// @param resource The resource we want to know if it is addable.
    /// @return True if the resource can be added to the Card, else False.
    bool DevelopmentCard::isResourceAddable (Resource* resource) const
    {
        return false;
    }

    /// @brief Convert the DevelopmentCard to a readable string.
    /// @return Readable string that contains the information concerning DevelopmentCard.
    std::string DevelopmentCard::toString () const
    {
        return "";
    }
}