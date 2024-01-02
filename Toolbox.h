// Liam Ballard
// COP3504
// Project 4

#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Tile.h"
#include "minesweeper.h"
class GameState;

class Toolbox {
public:
    sf::RenderWindow window; // SFML application window
    GameState* gameState; // Primary game state representation
    Button* debugButton; // Reveals mines in debug mode
    Button* newGameButton; // Resets & starts new game
    Button* testButton1; // Loads test board #1
    Button* testButton2; // Loads test board #2
    Button* testButton3; // Loads test board *3
    sf::Sprite* victory; // Victory sprite
    sf::Sprite* loss; // Loss sprite
    sf::Sprite* newGameSprite; // New game sprite
    sf::Texture digitsTexture; // Digits texture
    sf::Texture* newGameTexture; // New game texture
    sf::Texture* victoryTexture; // Victory texure
    sf::Texture* lossTexture; // Loss Texture
    sf::Texture* debugButtonTexture; // Debug button texture
    sf::Texture* test1Texture; // test1 button texture
    sf::Texture* test2Texture; // test2 button texture
    sf::Texture* test3Texture; // test3 button texture
    sf::Sprite* digits[11]; // Holds digits image
    sf::Sprite* countUI[4]; // UI mine counter
    std::vector<sf::Vector2i> flaggedMinePositions; // Holds positions of mines that are flagged
    bool debugMode; // Says whether is on debug mode
    int debugFlaggedMines;
    float tileWidth; // Width of each tile
    float tileHeight; // Height of each tile
    float buttonWidth; // Width of each button
    float buttonHeight; // Width of each height
    static Toolbox& getInstance(); // Returns reference to the single Toolbox instance
    ~Toolbox();

private:
    // Default constructor; should be accessible only from within the class itself
    // Initializes the buttons, window, game board, and any other elements necessary to play the game
    Toolbox();
};

