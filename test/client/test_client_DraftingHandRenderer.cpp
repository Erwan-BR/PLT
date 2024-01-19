#include <boost/test/unit_test.hpp>

#include "../../src/client/render/DraftingHandRenderer.h"

BOOST_AUTO_TEST_CASE(test_developmentCardRenderer)
{
    // Constructing the developmentCard that the player will receive.
    constants::victoryPointsPtr victoryPoints = std::make_shared<state::CardVictoryPoint>();
    victoryPoints->numberOfPoints = 1;
    victoryPoints->cardOrResourceType = state::CardType::VEHICLE;

    constants::resourcePayPtr resourceToPay1 = std::make_shared<state::ResourceToPay>();
    resourceToPay1->isPaid = false;
    resourceToPay1->type = state::ResourceType::MATERIAL;

    constants::resourcePayPtr resourceToPay2 = std::make_shared<state::ResourceToPay>();
    resourceToPay2->isPaid = false;
    resourceToPay2->type = state::ResourceType::MATERIAL;

    constants::resourcePayPtr resourceToPay3 = std::make_shared<state::ResourceToPay>();
    resourceToPay3->isPaid = false;
    resourceToPay3->type = state::ResourceType::MATERIAL;

    constants::resourcePayList resourceToPayList = {resourceToPay1, resourceToPay2, resourceToPay3};

    constants::devCardPtr card(new state::DevelopmentCard ("Reseau de transport",{},"../resources/img/Cards/Development_Cards/reseau_de_transport.png",victoryPoints,state::CardType::STRUCTURE,2,resourceToPayList,{},state::ResourceType::MATERIAL));

    // Construct the player
    constants::playerPtr player = constants::playerPtr(new state::Player("Erwan", 10));

    // Render the hand of the player
    render::DraftingHandRenderer* renderer = new render::DraftingHandRenderer(player, {0, 0});

    // Set the drafting hand of the player to make him launch the 'DRAFTING_CARDS_CHANGED' flag.
    player->setDraftingCards({card});

    // Call the destructor
    delete renderer;
}

/* vim: set sw=2 sts=2 et : */
