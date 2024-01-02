// Liam Ballard
// COP3504
// Project 4

#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
class Toolbox;
class minesweeper;

class Tile {
public:
    // Represents tile’s current UI state (visualization)
    enum State { REVEALED, HIDDEN, FLAGGED, EXPLODED };

    // Constructs a new tile object at the designated _position
    explicit Tile (sf::Vector2f position);

    // Returns the position of this tile
    sf::Vector2f getLocation();

    // Returns current State of this tile
    State getState();

    // Returns pointer to array of Tile pointers
    std::array<Tile*, 8>& getNeighbors();

    // Sets state of this tile
    // Triggers other behaviors related to state change
    void setState(State _state);

    // Populates/replaces neighboring tile container
    void setNeighbors(std::array<Tile*, 8> _neighbors);

    // Defines reveal behavior for a tile when left mouse button is clicked inside its boundaries
    virtual void onClickLeft();

    // Toggles this tile's state between FLAGGED and HIDDEN
    void onClickRight();

    // Renders this tile to screen according to its state
    void draw();

protected:
    // Based on State and mine content of the tile neighbors, set their state to REVEALED
    void revealNeighbors();

private:
    sf::Vector2f currentPosition; // Tile's position
    State currentState; // Current state of the tile
    std::array<Tile*, 8> neighborTiles; // Neighboring tiles
};

