#include <boost/test/unit_test.hpp>

#include "../../src/client/render/Button.h"

#include <memory>

using namespace ::render;

BOOST_AUTO_TEST_CASE(ButtonTest)
{
    sf::Vector2f position(16.5f, 24.f);
    sf::Vector2f size(16.5f, 24.f);
    std::unique_ptr<Button> testingButton(new Button(position,  size, "Name", sf::Color::White, nullptr));
    testingButton->setEnabled(true);
}