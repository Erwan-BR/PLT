#include <boost/test/unit_test.hpp>

#include "../../src/shared/state.h"
#include "../../src/shared/engine.h"
#include "../../src/shared/ai.h"
#include "../../src/constants/constants/CustomTypes.h"

using namespace ::state;
using namespace std;

BOOST_AUTO_TEST_CASE(test_Engine)
{
    constants::playersList ais = {};
    std::shared_ptr<Player> rAI = std::make_shared<ai::AIRandom>("dummy", -1);
    ais.push_back(rAI);
    std::shared_ptr<Player> aAI = std::make_shared<ai::AIAdvanced>("dummy", -2);
    ais.push_back(aAI);

    std::shared_ptr<state::Game> game = std::make_shared<state::Game>(ais);
    std::mutex locker;
    engine::Engine* engine = new engine::Engine(game, locker);
    
    engine->gameRunning(true);
    BOOST_CHECK_EQUAL(game->getPhase(),GamePhase::FINISHED);
    delete engine;
}

BOOST_AUTO_TEST_CASE(test_ExecutingCommand)
{
    constants::playersList ais = {};
    std::shared_ptr<Player> rAI = std::make_shared<ai::AIRandom>("dummy", -1);
    ais.push_back(rAI);
    std::shared_ptr<Player> aAI = std::make_shared<ai::AIAdvanced>("dummy", -2);
    ais.push_back(aAI);

    std::shared_ptr<state::Game> game = std::make_shared<state::Game>(ais);
    std::mutex locker;
    engine::Engine* engine = new engine::Engine(game, locker);

    engine::Command commandToExport1  = engine::Command(engine::CommandID::ADDRESOURCE, 0, 0);
    engine::Command commandToExport2  = engine::Command(engine::CommandID::DISCARDCARD, 0, 0);
    engine::Command commandToExport3  = engine::Command(engine::CommandID::KEEPCARD, 0, 0);
    engine::Command commandToExport4  = engine::Command(engine::CommandID::SENDRESOURCETOEMPIRE, 0, 0);
    engine::Command commandToExport5  = engine::Command(engine::CommandID::ENDPRODUCTION, 0, 0);
    engine::Command commandToExport6  = engine::Command(engine::CommandID::ENDPLANIFICATION, 0, 0);
    engine::Command commandToExport7  = engine::Command(engine::CommandID::CONVERTRESOURCE, 0, 0);
    engine::Command commandToExport8  = engine::Command(engine::CommandID::SETPREFFEREDPERSONNAGE, 0, 0);
    engine::Command commandToExport9  = engine::Command(engine::CommandID::CHOOSEDRAFTCARD, 0, 0);
    engine::Command commandToExport10 = engine::Command(engine::CommandID::SAVEGAME, 0, 0);

    Json::Value jsonContent1  = commandToExport1.toJSON();
    Json::Value jsonContent2  = commandToExport2.toJSON();
    Json::Value jsonContent3  = commandToExport3.toJSON();
    Json::Value jsonContent4  = commandToExport4.toJSON();
    Json::Value jsonContent5  = commandToExport5.toJSON();
    Json::Value jsonContent6  = commandToExport6.toJSON();
    Json::Value jsonContent7  = commandToExport7.toJSON();
    Json::Value jsonContent8  = commandToExport8.toJSON();
    Json::Value jsonContent9  = commandToExport9.toJSON();
    Json::Value jsonContent10 = commandToExport10.toJSON();

    engine::AddResource command1             = engine::AddResource(jsonContent1);
    engine::DiscardCard command2             = engine::DiscardCard(jsonContent2);
    engine::KeepCard command3                = engine::KeepCard(jsonContent3);
    engine::SendResourceToEmpire command4    = engine::SendResourceToEmpire(jsonContent4);
    engine::EndProduction command5           = engine::EndProduction(jsonContent5);
    engine::EndPlanification command6        = engine::EndPlanification(jsonContent6);
    engine::ConvertResource command7         = engine::ConvertResource(jsonContent7);
    engine::SetPreferredPersonnage command8  = engine::SetPreferredPersonnage(jsonContent8);
    engine::ChooseDraftCard command9         = engine::ChooseDraftCard(jsonContent9);
    engine::SaveGame command10                = engine::SaveGame(jsonContent10);

    engine->receiveCommand(jsonContent1);
    engine->receiveCommand(jsonContent2);
    engine->receiveCommand(jsonContent3);
    engine->receiveCommand(jsonContent4);
    engine->receiveCommand(jsonContent5);
    engine->receiveCommand(jsonContent6);
    engine->receiveCommand(jsonContent7);
    engine->receiveCommand(jsonContent8);
    engine->receiveCommand(jsonContent9);
    engine->receiveCommand(jsonContent10);
}

BOOST_AUTO_TEST_CASE(test_Command)
{
    std::shared_ptr<Player> playerFoTests = std::make_shared<state::Player>("player", 1);
    std::shared_ptr<Player> aiIntelligent = std::make_shared<ai::AIAdvanced>("advanced", -2);
    constants::playersList ais = {playerFoTests, aiIntelligent};
    std::shared_ptr<state::Game> game = std::make_shared<state::Game>(ais);
    game->initGame();


    engine::Command* command0 = new engine::Command(engine::CommandID::ADDRESOURCE);
    command0->launchCommand(game);
    delete command0;

    engine::AddResource* command1 = new engine::AddResource(0,ResourceType::MATERIAL,0);
    command1->launchCommand(game);
    BOOST_CHECK_EQUAL(command1->getCommandId(),engine::CommandID::ADDRESOURCE);
    delete command1;

    engine::DiscardCard* command2 = new engine::DiscardCard(0,0,true);
    command2->launchCommand(game);
    delete command2;

    engine::ChooseDraftCard* command3 = new engine::ChooseDraftCard(0,0);
    command3->launchCommand(game);
    delete command3;

    engine::KeepCard* command4 = new engine::KeepCard(0,0);
    command4->launchCommand(game);
    delete command4;

    engine::SendResourceToEmpire* command5 = new engine::SendResourceToEmpire(0,ResourceType::MATERIAL);
    command5->launchCommand(game);
    delete command5;

    engine::EndPlanification* command6 = new engine::EndPlanification(0);
    command6->launchCommand(game);
    delete command6;

    engine::EndProduction* command7 = new engine::EndProduction(0);
    command7->launchCommand(game);
    delete command7;

    engine::ConvertResource* command8 = new engine::ConvertResource(0,ResourceType::MATERIAL);
    command8->launchCommand(game);
    delete command8;

    engine::SetPreferredPersonnage* command9 = new engine::SetPreferredPersonnage(0,ResourceType::MATERIAL);
    command9->launchCommand(game);
    delete command9;

    engine::SaveGame* command10 = new engine::SaveGame();
    command10->launchCommand(game);
    delete command10;
}

/* vim: set sw=2 sts=2 et : */
