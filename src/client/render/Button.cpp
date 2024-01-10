#include "Button.h"
#include <iostream>

namespace render
{
    Button::Button (sf::Vector2f position, sf::Vector2f size, std::string text, sf::Color color, engine::Command* commandOnClick) :
        position(position),
        size(size),
        textString(text),
        color(color),
        command(commandOnClick)
    {
        sf::Font tempoFont;
        tempoFont.loadFromFile("./resources/font/arial.ttf");
        this->font = tempoFont;
        this->rectangle = sf::RectangleShape();
        this->rectangle.setSize(size);
        this->rectangle.setPosition(position);
        this->rectangle.setFillColor(color);

        this->text.setFont(font);
        this->text.setString(textString);
        this->text.setCharacterSize(20);
        this->text.setFillColor(sf::Color::Black);

        while(this->text.getLocalBounds().width > this->rectangle.getLocalBounds().width && this->text.getCharacterSize()>0){
            this->text.setCharacterSize(this->text.getCharacterSize()-1);
        }
        
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
        if (this->command == NULL)
        {
            this->isEnable = false;
        }
        // Do not display anything if the button is not enabled.
        if (!this->isVisible)
        {
            return ;
        }
        if(this->isEnable){
            window.draw(this->rectangle);
            window.draw(this->text);
        }
        else{
            this->rectangle.setFillColor(sf::Color::Black);
            window.draw(this->rectangle);
            window.draw(this->text);
        }

    }

    /// @brief Handle the event of a click on the window. It will launch the command only if 
    /// @param event Event that occurs on the window.
    /// @param window Displayed window to the player.
    void Button::handleEvent (sf::Event event, sf::RenderWindow& window)
    {
        // Check if the button is enabled, and pressed with a left click
        if (this->isEnable && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            
            // Check if the click is inside the button.
            if (rectangle.getGlobalBounds().contains(mousePos))
            {
                std::cout<<"Button Clicked:"<<this->textString<<std::endl;
                //this->command->launchCommand();
            }
        }
    }

    void Button::setEnabled (bool enabled)
    {
        this->isEnable = enabled;
    }

    void Button::setVisible (bool visible)
    {
        this->isVisible = visible;
    }

    void Button::setText(std::string newText){
        this->text.setString(newText);
    }

    void Button::changeCommand(engine::Command* command){
        this->command = command;
    }
}