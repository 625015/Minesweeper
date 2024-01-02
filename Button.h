// Liam Ballard
// COP3504
// Project 4

#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button {
public:
    // Constructs a new object at the specified _position, invoking _onClick callback when clicked
    Button(sf::Vector2f _position, std::function<void(void)> _onClick);

    // Returns position of the button
    sf::Vector2f getPosition();

    // Returns button's current sprite
    sf::Sprite* getSprite();

    // Sets this button's visualization to specified _sprite
    void setSprite(sf::Sprite* _sprite);

    // Invokes button's callback method (usually when clicked)
    void onClick();
private:
    sf::Vector2f currentPosition; // Holds current position of this button
    sf::Sprite* currentSprite; // Holds sprite of this button
    std::function<void(void)> currentOnClick; // Holds function to execute when button clicked
};


