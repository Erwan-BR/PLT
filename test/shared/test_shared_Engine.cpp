#include <boost/test/unit_test.hpp>

#include "../../src/shared/state.h"
#include "../../src/shared/engine.h"
#include "../../src/shared/ai.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(test_Engine)
{
    std::vector<state::Player*> ais = {};
    for (int i = 1; i < 3; i++){
        state::Player* newAI = new ai::AIRandom("dummy", -i);
        ais.push_back(newAI);
    }

    state::Game* game = new state::Game(ais);
    engine::Engine* engine = new engine::Engine(game, {});
    engine->gameRunning();
    BOOST_CHECK_EQUAL(game->getPhase(),GamePhase::FINISHED);
    delete game;
    delete engine;
    for(state::Player* ai : ais){
        delete ai;
    }
}

BOOST_AUTO_TEST_CASE(test_Button)
{
    engine::Button* btn = new engine::Button({0.f,0.f},{0.f,0.f},"---",sf::Color::Black,NULL);
    delete btn;
}

BOOST_AUTO_TEST_CASE(test_Command)
{
    state::Player* ai = new ai::AIRandom("dummy", -1);

    engine::AddResource* command1 = new engine::AddResource(ai,ResourceType::MATERIAL,0);
    command1->launchCommand();
    delete command1;

    engine::DiscardCard* command2 = new engine::DiscardCard(ai,0,true);
    command2->launchCommand();
    delete command2;

    engine::ChooseDraftCard* command3 = new engine::ChooseDraftCard(ai,0);
    command3->launchCommand();
    delete command3;

    engine::KeepCard* command4 = new engine::KeepCard(ai,0);
    command4->launchCommand();
    delete command4;

    engine::SendResourceToEmpire* command5 = new engine::SendResourceToEmpire(ai,ResourceType::MATERIAL);
    command5->launchCommand();
    delete command5;

    engine::EndPlanification* command6 = new engine::EndPlanification(ai);
    command6->launchCommand();
    delete command6;

    engine::EndProduction* command7 = new engine::EndProduction(ai);
    command7->launchCommand();
    delete command7;

    engine::ConvertResource* command8 = new engine::ConvertResource(ai,ResourceType::MATERIAL);
    command8->launchCommand();
    delete command8;

    engine::SaveGame* command9 = new engine::SaveGame();
    command9->launchCommand();
    delete command9;
}

/* vim: set sw=2 sts=2 et : */
