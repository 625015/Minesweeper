// Liam Ballard
// COP3504
// Project 4

#pragma once
#include "Tile.h"

class Mine : public Tile {
public:
    // Mine Constructor
    Mine(sf::Vector2f position);

    // Different left-click behavior if is mine
    void onClickLeft() override;
};
