#include "Player.h"

namespace state {

    /// @brief Constructor of the class Player
    Player::Player()
    {

    }

    /// @brief Destructor of the class Player
    Player::~Player()
    {

    }

    /// @brief Construct the card "cardToBuild"
    /// @param cardToBuild 
    void Player::construct(DevelopmentCard* cardToBuid)
    {

    }

    /// @brief Add a resource "resource" to the card "card"
    /// @param resource
    /// @param card
    void Player::addResource(Resource* ressource, DevelopmentCard* card)
    {

    }

    /// @brief Discard the card "toDiscardCard"
    /// @param toDiscardCard
    void Player::discardCard(DevelopmentCard* toDiscardCard)
    {

    }

    /// @brief Calculate the quantity of resource named "resourceToProduce" produced by the player
    /// @param resourceToProduce
    /// @return
    int Player::computeProduction(Resource* resourceToProduce)
    {
        return 0;
    }

    /// @brief Calculate the number of victory points the player has
    /// @return
    int Player::computeVictoryPoint()
    {
        return 0;
    }

    /// @brief Takes a resource produced by the player and places it on the Empire of the player
    /// @param resource
    void Player::sendResourceToEmpire(Resource* resource)
    {

    }

    /// @brief Converts the empire's resources when it reaches 5 resources
    void Player::convertToKrystallium()
    {

    }

    /// @brief Add the selected card "card" from the drafting deck to the drafted one
    /// @param card 
    void Player::chooseDraftCard(DevelopmentCard* card)
    {

    }

    /// @brief Return the selected token by the player (Colonel/General)
    /// @return
    bool Player::chooseColonelToken()
    {
        return true;
    }
}