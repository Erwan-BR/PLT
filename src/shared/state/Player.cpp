#include "Player.h"

namespace state {

    /// @brief Constructor of the class Player
    Player::Player() :
    name(""),
    id(-1),
    empire(EmpireCard()),
    builtCards({}),
    toBuildCards({}),
    draftingCards({}),
    draftCards({}),
    state(PENDING),
    financierTokensUnit(0),
    colonelTokensUnit(0),
    krystalliumTokensUnit(0),
    currentResources({}),
    tokensInEmpireUnit(0)
    {
        
    }

    /// @brief Destructor of the class Player
    Player::~Player()
    {

    }

    /// @brief Construct the card "cardToBuild"
    /// @param cardToBuild : the card to build
    void Player::construct(DevelopmentCard* cardToBuid)
    {

    }

    /// @brief Add a resource "resource" to the card "card"
    /// @param resource : resource placed on the card "card"
    /// @param card : card that will receive the resource "resource"
    void Player::addResource(Resource* ressource, DevelopmentCard* card)
    {

    }

    /// @brief Discard the card "toDiscardCard"
    /// @param toDiscardCard : card that is going to be discarded
    void Player::discardCard(DevelopmentCard* toDiscardCard)
    {

    }

    /// @brief Calculate the quantity of resource named "resourceToProduce" produced by the player
    /// @param resourceToProduce : type of the resource that will be produced
    /// @return 0 : quantity of resource "resourceToProduce" obtained by the player
    int Player::computeProduction(Resource* resourceToProduce)
    {
        return 0;
    }

    /// @brief Calculate the number of victory points the player has
    /// @return 0 : number of victory points the player on the moment
    int Player::computeVictoryPoint()
    {
        return 0;
    }

    /// @brief Takes a resource produced by the player and places it on the Empire of the player
    /// @param resource : type of resource that one will be send to the empire card of the player
    void Player::sendResourceToEmpire(Resource* resource)
    {

    }

    /// @brief Converts the empire's resources when it reaches 5 resources
    void Player::convertToKrystallium()
    {

    }

    /// @brief Add the selected card "card" from the drafting deck to the drafted one
    /// @param card : card choosed by the player
    void Player::chooseDraftCard(DevelopmentCard* card)
    {

    }

    /// @brief Return the selected token by the player (Colonel/General)
    /// @return true : boolean returned by the choice of the player (Colonel => true, General => false)
    bool Player::chooseColonelToken()
    {
        return true;
    }
}