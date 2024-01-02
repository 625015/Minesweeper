// Liam Ballard
// COP3504
// Project 4

#pragma once
#include "Tile.h"
#include "Mine.h"
#include "GameState.h"
#include "Toolbox.h"
#include <SFML/Graphics.hpp>
#include "Button.h"

// Draws overlay textures
sf::Texture* drawOverlayTextures(const sf::Texture& topTexture, const sf::Texture& bottomTexture);

// Checks if a tile is a mine
bool isMine(const Tile& tile);

// Gets all tiles in REVEALED state
int getTilesRevealed();

// Gets number of tiles in board
int getNumTiles();

// Reveals all mines
void revealAllMines();

// placesMines on board
std::vector<std::vector<bool>> placeMines(int numMines, int rows, int columns);

// Sets board w/ tiles according to mineField
std::vector<std::vector<Tile*>> setBoard(std::vector<std::vector<bool>> field, float rows, float columns);

// Invoked directly by main() and is responsible for the game’s launch. It should be possible to
// directly invoke this function after including the submitted source and header files in the test suite
int launch() ;

// Resets all states/objects and generates a default game state (random board) and turns off debug mode if active.
// The new state should be a default game state (25x16 with 50 randomly placed mines).
void restart();

// Draws the all UI elements according to the current gameState and debug mode
void render();

// Flips the debug mode on/off. (Debug mode should initially be off/false.)
void toggleDebugMode();

// Function to store the positions of flagged mines
void storeFlaggedMines();

// Function to reapply flags after exiting debug mode
void reapplyFlaggedMines();

// Returns the true if debug mode is active, and false otherwise.
bool getDebugMode();

// Loads board from file
void loadTestBoard(const char* filepath);

// Encapsulates event-polling, rendering, and other logic necessary to handle input and output for the game
int gameLoop();

// Handle mouse events
void handleMouseClick(sf::Event::MouseButtonEvent);

