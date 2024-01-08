#include "Button.h"

namespace engine
{
    Button::Button (sf::Vector2f position, sf::Vector2f size, std::string text, sf::Color color, Command* commandOnClick) :
        position(position),
        size(size),
        textString(text),
        buttonColor(color),
        command(commandOnClick)
    {
        sf::Font tempoFont;
        tempoFont.loadFromFile("./resources/font/arial.ttf");
        this->font = tempoFont;
        this->rectangle.setSize(size);
        this->rectangle.setPosition(position);
        this->rectangle.setFillColor(buttonColor);

        this->text.setFont(font);
        this->text.setString(textString);
        this->text.setCharacterSize(20);
        this->text.setFillColor(color);
        
        // Center the text within the button
        sf::FloatRect textBounds = this->text.getLocalBounds();
        this->text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        this->text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
    }

    Button::~Button ()
    {

    }

    void Button::draw (sf::RenderWindow& window)
    {
        // Do not display anything if the button is not enabled.
        if (!this->isVisible)
        {
            return ;
        }
        // 
        window.draw(this->rectangle);
        window.draw(this->text);
    }

    /// @brief Handle the event of a click on the window. It will launch the command only if 
    /// @param event Event that occurs on the window.
    /// @param window Displayed window to the player.
    void Button::handleEvent (sf::Event event, sf::RenderWindow& window)
    {
        // Check if the button is enabled, and pressed with a left click
        if (this->isEnable && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            
            // Check if the click is inside the button.
            if (rectangle.getGlobalBounds().contains(mousePos))
            {
                this->command->launchCommand();
            }
        }
    }

    void Button::setEnabled (bool enabled)
    {
        this->isEnable = enabled;
    }
}