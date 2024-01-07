// Liam Ballard

#include "Button.h"

// Constructs new object at specified _position w/ _onClick callback when clicked
Button::Button(sf::Vector2f _position, std::function<void(void)> _onClick) {
    currentPosition = _position;
    currentSprite = nullptr;
    currentOnClick = _onClick;
}

// Returns the position of the button
sf::Vector2f Button::getPosition() {
    return currentPosition;
}

// Returns button's current sprite
sf::Sprite* Button::getSprite() {
    return currentSprite;
}

// Sets this button's visualization to specified _sprite
// First deallocates old sprite
void Button::setSprite(sf::Sprite* _sprite) {
    currentSprite = nullptr;
    delete currentSprite;
    currentSprite = _sprite;
}

// Invokes button's callback method
void Button::onClick() {
    if (currentOnClick != nullptr) {
        currentOnClick();
    }
}
