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

    engine::Command commandToExport1 = engine::Command(engine::CommandID::ADDRESOURCE, 0, 0);
    engine::Command commandToExport2 = engine::Command(engine::CommandID::DISCARDCARD, 0, 0);
    engine::Command commandToExport3 = engine::Command(engine::CommandID::KEEPCARD, 0, 0);
    engine::Command commandToExport4 = engine::Command(engine::CommandID::SENDRESOURCETOEMPIRE, 0, 0);
    engine::Command commandToExport5 = engine::Command(engine::CommandID::ENDPRODUCTION, 0, 0);
    engine::Command commandToExport6 = engine::Command(engine::CommandID::ENDPLANIFICATION, 0, 0);
    engine::Command commandToExport7 = engine::Command(engine::CommandID::CONVERTRESOURCE, 0, 0);
    engine::Command commandToExport8 = engine::Command(engine::CommandID::SETPREFFEREDPERSONNAGE, 0, 0);
    engine::Command commandToExport9 = engine::Command(engine::CommandID::CHOOSEDRAFTCARD, 0, 0);
    engine::Command commandToExport10 = engine::Command(engine::CommandID::SAVEGAME, 0, 0);

    Json::Value jsonContent  = commandToExport1.toJSON();
    Json::Value jsonContent2  = commandToExport2.toJSON();
    Json::Value jsonContent3  = commandToExport3.toJSON();
    Json::Value jsonContent4  = commandToExport4.toJSON();
    Json::Value jsonContent5  = commandToExport5.toJSON();
    Json::Value jsonContent6  = commandToExport6.toJSON();
    Json::Value jsonContent7  = commandToExport7.toJSON();
    Json::Value jsonContent8  = commandToExport8.toJSON();
    Json::Value jsonContent9  = commandToExport7.toJSON();
    Json::Value jsonContent10  = commandToExport8.toJSON();

    engine::DiscardCard command2             = engine::DiscardCard(jsonContent);
    engine::ChooseDraftCard command3         = engine::ChooseDraftCard(jsonContent);
    engine::KeepCard command4                = engine::KeepCard(jsonContent);
    engine::SendResourceToEmpire command5    = engine::SendResourceToEmpire(jsonContent);
    engine::EndPlanification command6        = engine::EndPlanification(jsonContent);
    engine::EndProduction command7           = engine::EndProduction(jsonContent);
    engine::ConvertResource command8         = engine::ConvertResource(jsonContent);
    engine::SetPreferredPersonnage command9  = engine::SetPreferredPersonnage(jsonContent);
    engine::SaveGame command10                = engine::SaveGame(jsonContent);

    engine->receiveCommand(jsonContent);
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
    std::shared_ptr<Player> ai = std::make_shared<ai::AIRandom>("dummy", -1);
    constants::playersList ais = {ai};
    std::shared_ptr<state::Game> game = std::make_shared<state::Game>(ais);


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
