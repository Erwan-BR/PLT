#include "Player.h"
#include <map>

namespace state {

    /// @brief Constructor of the class Player
    Player::Player() :
    name(""),
    id(-1),
    profilePicture(sf::Texture()),
    empire(new EmpireCard()),
    builtCards({}),
    toBuildCards({}),
    draftingCards({}),
    draftCards({}),
    state(PENDING),
    financierTokensUnit(0),
    colonelTokensUnit(0),
    krystalliumTokensUnit(0),
    currentResources({}),
	resourcesInEmpireUnit(0)
    {
        resourcesProduction[MATERIAL] = 0;
        resourcesProduction[ENERGY] = 0;
        resourcesProduction[SCIENCE] = 0;
        resourcesProduction[GOLD] = 0;
        resourcesProduction[EXPLORATION] = 0;

        cardsTypeList[STRUCTURE] = 0;
        cardsTypeList[VEHICLE] = 0;
        cardsTypeList[RESEARCH] = 0;
        cardsTypeList[PROJECT] = 0;
        cardsTypeList[DISCOVERY] = 0;
    }

    /// @brief Destructor of the class Player
    Player::~Player()
    {

    }

    /// @brief Construct the card "cardToBuild"
    /// @param cardToBuild The card to build
    void Player::construct(DevelopmentCard* cardToBuid)
    {
        return ;
    }

    /// @brief Add a resource "resource" to the card "card"
    /// @param resource Resource placed on the card "card"
    /// @param card Card that will receive the resource "resource"
    void Player::addResource(Resource* resource, DevelopmentCard* card)
    {
		return ;
    }

    /// @brief Discard the card "toDiscardCard"
    /// @param toDiscardCard Card that is going to be discarded
    void Player::discardCard(DevelopmentCard* toDiscardCard)
    {
		return ;
    }

    void Player::updateProduction()
    {
		return ;
    }

    /// @brief Compute the quantity of resource named "resourceToProduce" produced by the player
    /// @param resourceToProduce Type of the resource that will be produced
    /// @return Quantity of resource "resourceToProduce" obtained by the player
    int Player::computeProduction(ResourceType resourceToProduce) const
    {
        return -1;
    }

    /// @brief Compute the number of victory points the player has
    /// @return Number of victory points of the player on the moment
    int Player::computeVictoryPoint() const
    {
        return -1;
    }

    /// @brief Take a resource produced by the player and place it on the Empire of the player
    /// @param resource Type of resource that one will be send to the empire card of the player
    void Player::sendResourceToEmpire(Resource* resource)
    {
        return ;
    }

    /// @brief Converts the empire's resources into a krystallium when it reaches 5 resources
    void Player::convertToKrystallium()
    {
        return ;
    }

    /// @brief Add the selected card "card" from the drafting deck to the selected one
    /// @param card Card choosed by the player
    void Player::chooseDraftCard(DevelopmentCard* card)
    {
		return ;
    }

    /// @brief Return the selected token by the player (Colonel/Financier)
    /// Not implementable as it ask to know on which one does the player clicks.
    /// @return Boolean returned by the choice of the player (true => Colonel, false => Financier)
    bool Player::chooseColonelToken() const
    {
        return false ;
    }
   

    /// @brief Transform the Player to a readable string.
    /// @return Readable string that represents the information of the Player.
    std::string Player::toString () const
    {
        return "";
    }
}
