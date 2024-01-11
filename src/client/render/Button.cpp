#include "Button.h"
#include <iostream>

namespace render
{
    /// @brief Cnstructor of a button.
    /// @param position Position of the button.
    /// @param size Size of the button.
    /// @param text Text that is inside the button.
    /// @param color Color of the button.
    /// @param commandOnClick Command executed on click.
    /// @param locker mutex that allow to send securely the command to the engine.
    Button::Button (sf::Vector2f position, sf::Vector2f size, std::string text, sf::Color color, engine::Command* commandOnClick, std::mutex & locker) :
        position(position),
        size(size),
        textString(text),
        color(color),
        command(commandOnClick),
        locker(locker)
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

    /// @brief Destructor of the button. Do not destroy anything because commands can be shared.
    Button::~Button ()
    {

    }

    /// @brief Draw the button on the main window.
    /// @param window Window where the button is displayed.
    void Button::draw (sf::RenderWindow& window)
    {
        if (nullptr == this->command)
        {
            this->isEnable = false;
        }
        // Do not display anything if the button is not enabled.
        if (!this->isVisible)
        {
            return ;
        }
        if(this->isEnable)
        {
            window.draw(this->rectangle);
            window.draw(this->text);
        }
        else
        {
            this->rectangle.setFillColor(sf::Color::White);
            window.draw(this->rectangle);
            window.draw(this->text);
        }

    }

    /// @brief Handle the event of a click on the window. It will launch the command only if 
    /// @param event Event that occurs on the window.
    /// @param window Displayed window to the player.
    /// @param engineOfGame Engine that will receive the game.
    void Button::handleEvent (sf::Event event, sf::RenderWindow& window, engine::Engine* engineOfGame, Scene* scene)
    {
        // Check if the button is enabled, and pressed with a left click
        if (this->isEnable && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            
            // Check if the click is inside the button and if the command is not a nullptr to avoid sending something for nothing.
            if (rectangle.getGlobalBounds().contains(mousePos) && nullptr != this->command)
            {
                Json::Value jsonCommand = this->command->toJSON();
                if(this->command->getCommandId() == (engine::CommandID) -1){        //Catch Actions which are executed by render and not by the engine
                    scene->changePlayerInfoPlayer(jsonCommand["playerIndex"].asInt());
                }
                else{
                    // Lock the mutex, send the JSON of the command and unlock the mutex.
                    this->locker.lock();
                    engineOfGame->receiveCommand(jsonCommand);
                    this->locker.unlock();
                }
            }
        }
    }

    /************************************* Setters & Getters *************************************/

    /// @brief Set the button enable or not. It indicates if the button can be clicked.
    /// @param enabled New state of the button.
    void Button::setEnabled (bool enabled)
    {
        this->isEnable = enabled;
    }

    /// @brief Set visible or not the button, to display it or not according to the window.
    /// @param visible State of the button.
    void Button::setVisible (bool visible)
    {
        this->isVisible = visible;
    }

    /// @brief Change the text of the button.
    /// @param newText New string that is inside the button.
    void Button::setText(std::string newText)
    {
        this->text.setString(newText);
    }

    /// @brief Change the command performed by the button when clicked.
    /// @param command New command performed by the click.
    void Button::changeCommand(engine::Command* command)
    {
        this->command = command;
    }
}