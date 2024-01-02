// Liam Ballard
// COP3504
// Project 4

#include "Mine.h"

// Mine Constructor; doesn't violate spec rule because subclassing Tile was encouraged
Mine::Mine(sf::Vector2f position) : Tile(position) {}

// Different left-click behavior if is mine; changes to EXPLODED instead of REVEALED
// Doesn't violate spec rule because it's overriding an already existing public method; subclassing Tile
// for this purpose was encouraged
void Mine::onClickLeft() {
    setState(EXPLODED);
}
