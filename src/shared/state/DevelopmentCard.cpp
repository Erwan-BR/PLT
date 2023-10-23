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
    quantityResourceMissing(-1) // "Error" value : Empty constructor should never be used.
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
    quantityResourceMissing(costToBuild.size()) // Because no resource is paid and the size is never 0.
    {
    }

    /// @brief Destructor of the DevelopmentCard class.
    DevelopmentCard::~DevelopmentCard ()
    {
    }

    /// @brief Add a ressource into the Card. The resource must be addable. Should also update the quantity and the isPaid value.
    /// @param resource Resource that will be added to the Card.
    /// @return True if the card is just payed. False either.
    bool DevelopmentCard::addResource (Resource* resource)
    {
        for (ResourceToPay* resourceToPay : this->costToBuild)
        {
            // Checking if the current resource is not paid, and if the type is the one of the input parameter.
            if ((!resourceToPay->isPaid) && (resourceToPay->type == resource->type))
            {
                resourceToPay->isPaid = true;
                return (this->decreaseResourceUnitNeeded());
            } 
        }
        // The following line should never be reached.
        return false;
    }

    /// @brief Add a krystallium ressource into a Card. A resource should be replaced. 
    /// @param resourceToReplace Resource that will be replaced by a krystallium.
    /// @return True if the card is just payed. False either.
    bool DevelopmentCard::addKrystallium (Resource* resourceToReplace)
    {
        // Iterating among all resources that should be paid
        for (ResourceToPay* resourceToPay : this->costToBuild)
        {
            // Checking if the current resource is not paid, and if the type is the one we want to replace.
            if ((!resourceToPay->isPaid) && (resourceToPay->type == resourceToReplace->type))
            {
                resourceToPay->isPaid = true;
                return (this->decreaseResourceUnitNeeded());
            } 
        }
        // The following line should never be reached.
        return false;
    }

    /// @brief Check if a resource can be added to the DevelopmentCard.
    /// @param resource The resource we want to know if it is addable.
    /// @return True if the resource can be added to the Card, else False.
    bool DevelopmentCard::isResourceAddable (Resource* resource) const
    {
        // First, if a card is Paid, ressources can't be added.
        if (this->isPaid)
        {
            return false;
        }
        // If this line is reached, the card is not paid.

        // Iterating among all resources that should be paid
        for (ResourceToPay* resourceToPay : this->costToBuild)
        {
            // If the current ressource is not paid, we check if the resource can be added.
            if (!resourceToPay->isPaid)
            {
                // If both types are the same, resource can be added.
                if (resourceToPay->type == resource->type)
                {
                    return true;
                }
                // If the input resource is a krysallium, and the resourceToPay is not Colonel / Financier, it can be paid.
                if ((resource->type == ResourceType::KRYSTALLIUM) &&
                (resourceToPay->type == ResourceType::MATERIAL ||
                resourceToPay->type == ResourceType::ENERGY ||
                resourceToPay->type == ResourceType::SCIENCE ||
                resourceToPay->type == ResourceType::GOLD ||
                resourceToPay->type == ResourceType::EXPLORATION))
                {
                    return true;
                }
            }
        }
        // If this line is reached, it means that none of the ressources to pay may be paid. 
        return false;
    }
    
    /// @brief Decrease the amount of resource of unit needed. Also update the isPaid boolean if needed.
    /// @return True if the card is just payed. False either.
    bool DevelopmentCard::decreaseResourceUnitNeeded ()
    {
        // Decrease the quantity of ressource which are missing.
        this->quantityResourceMissing--;

        // Update the isPaid attribute according to the quantity of ressources that must be paid.
        this->isPaid = (this->quantityResourceMissing == 0);
        
        // Return the boolean isPaid to know if everything as been paid.
        return this->isPaid; 
    }

    /// @brief Convert the DevelopmentCard to a readable string.
    /// @return Readable string that contains the information concerning DevelopmentCard.
    std::string DevelopmentCard::toString () const
    {
        // Instantiation of a string to return.
        std::string returnValue = "Name: " + this->name + "\n";
        
        // Adding some info to returnValue.
        returnValue += "Type: " + std::to_string(this->type) + "\n";
        returnValue += "Number Of Copies: " + std::to_string(this->numberOfCopies) + "\n";
        
        // Adding a diffeent sentence depending on if the card is paid or not.
        if (this->isPaid)
        {
            returnValue += "This card is paid.\n";
        }
        else
        {
            returnValue += "Resouces missing: " + std::to_string(this->quantityResourceMissing);
        }

        // Adding some other info to returnValue.
        returnValue += "Discard gain: " + std::to_string(this->discardGain->type) + "\n";
        
        // Return the constructed string.
        return returnValue;
    }
}