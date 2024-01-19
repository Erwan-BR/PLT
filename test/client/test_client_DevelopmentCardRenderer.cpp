#include <boost/test/unit_test.hpp>

#include "../../src/client/render/DevelopmentCardRenderer.h"

BOOST_AUTO_TEST_CASE(test_developmentCardRenderer)
{
    // Constructing the developmentCard
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

    constants::devCardPtr cardToRender(new state::DevelopmentCard ("Reseau de transport",{},"../resources/img/Cards/Development_Cards/reseau_de_transport.png",victoryPoints, state::CardType::STRUCTURE,2,resourceToPayList,{},state::ResourceType::MATERIAL));

    // Construct the render
    render::DevelopmentCardRenderer* renderer = new render::DevelopmentCardRenderer(cardToRender, {0, 0}, 0.f);

    // Call the update method
    renderer->update(0);

    // Call the destructor
    delete renderer;
}

/* vim: set sw=2 sts=2 et : */
