#include <boost/test/unit_test.hpp>

#include "../../src/shared/state.h"
#include "../../src/shared/engine.h"
#include "../../src/shared/ai.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(test_Random_AI)
{
    ai::AIRandom* rAI = new ai::AIRandom("dummy", -1);
    rAI->AIUseProducedResources();
    rAI->AIChooseColonelToken();

    Json::Value aiIntoJSON = rAI->toJSON();
    ai::AIRandom rAI_Imported = ai::AIRandom(aiIntoJSON);

    delete rAI;
}

BOOST_AUTO_TEST_CASE(test_Advanced_AI)
{
    ai::AIAdvanced* aAI = new ai::AIAdvanced("dummy", -1);
    aAI->AIChooseColonelToken();

    Json::Value aiIntoJSON = aAI->toJSON();
    ai::AIAdvanced aAI_Imported = ai::AIAdvanced(aiIntoJSON);
    
    delete aAI;
}

/* vim: set sw=2 sts=2 et : */
