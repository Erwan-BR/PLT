#include <boost/test/unit_test.hpp>

#include "../../src/client/render/Button.h"

BOOST_AUTO_TEST_CASE(test_Buttons)
{
    // Instanciation of the button
    std::mutex locker ;
    render::Button* buttonForTest = new render::Button({0, 0}, {10, 10}, "Click Me!", sf::Color::Green, nullptr, locker);

    // Calling different methods, that can't be checked because getters are not implemented.
    buttonForTest->setEnabled(true);
    buttonForTest->setText("Click Me Again!");
    buttonForTest->setVisible(true);
    buttonForTest->changeCommand(nullptr);

    // Cal the destructor of button
    delete buttonForTest;
}

/* vim: set sw=2 sts=2 et : */
