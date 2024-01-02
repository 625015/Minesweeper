// Liam Ballard
// COP3504
// Project 4

#include "minesweeper.h"
#include <filesystem>

// Draws overlay textures
sf::Texture* drawOverlayTextures(const sf::Texture& topTexture, const sf::Texture& bottomTexture)
{
    Toolbox& toolbox = Toolbox::getInstance();
    sf::Sprite topSprite(topTexture);
    sf::Sprite bottomSprite(bottomTexture);

    // Create a render texture to overlay the textures
    sf::RenderTexture renderTexture;
    if (!renderTexture.create(topTexture.getSize().x, topTexture.getSize().y))
    {
        // Handle error creating render texture
        std::cerr << "Error creating render texture";
    }

    // Clear the render texture
    renderTexture.clear();

    // Draw the bottom texture onto the render texture
    renderTexture.draw(bottomSprite);

    // Draw the top texture onto the render texture with blending
    sf::BlendMode blendMode;
    blendMode.colorSrcFactor = sf::BlendMode::SrcAlpha;
    blendMode.colorDstFactor = sf::BlendMode::OneMinusSrcAlpha;
    renderTexture.draw(topSprite, blendMode);

    // Display the render texture on the window
    renderTexture.display();
    sf::Sprite resultSprite(renderTexture.getTexture());
    sf::Texture* texture = new sf::Texture();
    *texture = renderTexture.getTexture();

    // Draw the result sprite onto the window
    return texture;
}

// Checks if a tile is a mine
// Dynamic cast source:
// GeeksforGeeks. (2023d, July 7). Dynamic _cast in C++. GeeksforGeeks.
// https://www.geeksforgeeks.org/dynamic-_cast-in-cpp/
bool isMine(const Tile& tile) {
    if (const Mine* mine = dynamic_cast<const Mine*>(&tile)) {
        return true;
    }
    return false;
}

// Returns number of tiles on board
int getNumTiles() {
    Toolbox& toolbox = Toolbox::getInstance();
    int numTiles = 0;
    // Iterate through each row and increment as long as not null tile
    int x = 0;
    while (toolbox.gameState->getTile(x, 0) != nullptr) {
        int y = 0;
        while (toolbox.gameState->getTile(x, y) != nullptr) {
            Tile* currentTile = toolbox.gameState->getTile(x, y);
            if (currentTile != nullptr) {
                numTiles++;
            }
            y++;
        }
        x++;
    }
    return numTiles;
}

// Returns number of tiles in REVEALED state
int getTilesRevealed() {
    int tilesRevealed = 0;
    Toolbox& toolbox = Toolbox::getInstance();
    // Iterate through each row and increment if is REVEALED
    int x = 0;
    while (toolbox.gameState->getTile(x, 0) != nullptr) {
        int y = 0;
        while (toolbox.gameState->getTile(x, y) != nullptr) {
            Tile* currentTile = toolbox.gameState->getTile(x, y);
            if(currentTile->getState() == Tile::REVEALED) {
                tilesRevealed++;
            }
            y++;
        }
        x++;
    }
    return tilesRevealed;
}

// Reveals all mines
void revealAllMines() {
    Toolbox& toolbox = Toolbox::getInstance();
    int x = 0;
    // Iterate through each row and set each mine to EXPLODED
    while (toolbox.gameState->getTile(x, 0) != nullptr) {
        int y = 0;
        while (toolbox.gameState->getTile(x, y) != nullptr) {
            Tile* currentTile = toolbox.gameState->getTile(x, y);
            if (currentTile != nullptr && isMine(*currentTile)) {
                currentTile->setState(Tile::EXPLODED);
            }
            y++;
        }
        x++;
    }
}

// Places mines on board
std::vector<std::vector<bool>> placeMines(int numMines, int rows, int columns) {
    int minesPlaced = 0;
    // 2D vector holding minefield data
    std::vector<std::vector<bool>> mineField(rows, std::vector<bool>(columns, false));
    while (minesPlaced < numMines) {
        // Row and col selected randomly
        int row = std::rand() % rows;
        int col = std::rand() % columns;
        // Mine added to minefield if not already in minefield[row][col]
        if (!mineField[row][col]) {
            mineField[row][col] = true;
            minesPlaced++;
        }
    }
    return mineField;
}

// sets Tiles for Board (default)
std::vector<std::vector<Tile*>> setBoard(std::vector<std::vector<bool>> field, float rows, float columns) {
    std::vector<std::vector<Tile*>> board;
    board.resize(rows, std::vector<Tile*>(columns, nullptr));
    // Set to Tile if is not mine
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (field[i][j] == 0) {
                board[i][j] = new Tile(sf::Vector2f(i, j));
            }
            // Set to Mine if is mine
            else if(field[i][j] == 1) {
                board[i][j] = new Mine(sf::Vector2f(i, j));
            }
        }
    }
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            // Set neighbor locations
            std::array<Tile*, 8> neighbors;
            for (int k = 0; k < neighbors.size(); k++) {
                neighbors.at(k) = nullptr;
            }
            if(i - 1 >= 0 && j - 1 >= 0) {
                neighbors.at(0) = board[i-1][j-1];
            }
            if(j - 1 >= 0) {
                neighbors.at(1) = board[i][j-1];
            }
            if(i + 1 < rows && j - 1 >= 0) {
                neighbors.at(2) = board[i+1][j - 1];
            }
            if(i - 1 >= 0) {
                neighbors.at(3) = board[i-1][j];
            }
            if(i + 1 < rows) {
                neighbors.at(4) = board[i+1][j];
            }
            if(i - 1 >= 0 && j + 1 < columns) {
                neighbors.at(5) = board[i-1][j+1];
            }
            if(j + 1 < columns) {
                neighbors.at(6) = board[i][j + 1];
            }
            if(i + 1 < rows && j + 1 < columns) {
                neighbors.at(7) = board[i+1][j+1];
            }
            board[i][j]->setNeighbors(neighbors);
        }
    }
    // Set up neighbor tiles
    return board;
}

// Invoked directly by main() and is responsible for the game’s launch. It should be possible to
// directly invoke this function after including the submitted source and header files in the test suite
int launch() {
    return gameLoop();
}
// Resets all states/objects and generates a default game state (random board) and turns off debug mode if active.
// The new state should be a default game state (25x16 with 50 randomly placed mines).
void restart() {
    GameState* currentGameState = Toolbox::getInstance().gameState;
    delete currentGameState;
    Toolbox::getInstance().gameState = new GameState();
    Toolbox::getInstance().debugFlaggedMines = 0;
    Toolbox::getInstance().flaggedMinePositions.clear();
}

// Draws the all UI elements according to the current gameState and debug mode
void render() {
    Toolbox& toolbox = Toolbox::getInstance();
    // Start from a clean slate
    toolbox.window.clear(sf::Color::White);

    // Draw board
    if (getDebugMode()) {
        revealAllMines();
    }

    // Iterate through every tile and draw it
    int x = 0;
    while (toolbox.gameState->getTile(x, 0) != nullptr) {
        int y = 0;
        while (toolbox.gameState->getTile(x, y) != nullptr) {
            Tile* currentTile = toolbox.gameState->getTile(x, y);
            if (currentTile != nullptr) {
                currentTile->draw();
            }
            y++;
        }
        x++;
    }

    // Draw buttons
    // Set gameState button based on playStatus
    if(toolbox.gameState->getPlayStatus() == GameState::PLAYING) {
        if(toolbox.newGameButton->getSprite() != toolbox.newGameSprite) {
            toolbox.newGameButton->setSprite(toolbox.newGameSprite);
        }
    }
    else if(toolbox.gameState->getPlayStatus() == GameState::WIN) {
        if(toolbox.newGameButton->getSprite() != toolbox.victory) {
            toolbox.newGameButton->setSprite(toolbox.victory);
        }
    }
    else if(toolbox.gameState->getPlayStatus() == GameState::LOSS) {
        if(toolbox.newGameButton->getSprite() != toolbox.loss) {
            toolbox.newGameButton->setSprite(toolbox.loss);
        }
    }
    toolbox.newGameButton->getSprite()->setPosition(toolbox.newGameButton->getPosition());
    toolbox.window.draw(*toolbox.newGameButton->getSprite());

    toolbox.debugButton->getSprite()->setPosition(toolbox.debugButton->getPosition());
    toolbox.window.draw(*toolbox.debugButton->getSprite());

    toolbox.testButton1->getSprite()->setPosition(toolbox.testButton1->getPosition());
    toolbox.window.draw(*toolbox.testButton1->getSprite());

    toolbox.testButton2->getSprite()->setPosition(toolbox.testButton2->getPosition());
    toolbox.window.draw(*toolbox.testButton2->getSprite());

    toolbox.testButton3->getSprite()->setPosition(toolbox.testButton3->getPosition());
    toolbox.window.draw(*toolbox.testButton3->getSprite());

    // Draw mine counter
    int mineCount = toolbox.gameState->getMineCount();
    int flagCount = toolbox.gameState->getFlagCount();
    int counter = 0;
    // Set counter based on mineCount - number of flagged tiles
    if(getDebugMode()) {
        counter = mineCount - toolbox.debugFlaggedMines;
    }
    else {
        counter = mineCount - flagCount;
    }

    // Set counter digits
    if (counter >= 0) {
        int xPosition = 42;
        int onesDigit = counter % 10;
        int tensDigit = (counter / 10) % 10;
        int hundredsDigit = (counter / 100) % 10;
        toolbox.countUI[0] = toolbox.digits[onesDigit];
        toolbox.countUI[1] = toolbox.digits[tensDigit];
        toolbox.countUI[2] = toolbox.digits[hundredsDigit];
        for (int i = 0; i < 3; i++) {
            toolbox.countUI[i]->setPosition((xPosition - (i * 21)), 512);  // Adjust the y-position as needed
            toolbox.window.draw(*toolbox.countUI[i]);
        }
    }

    else {
        int xPosition = 63;
        int onesDigit = abs(counter % 10);
        int tensDigit = abs((counter / 10) % 10);
        int hundredsDigit = abs((counter / 100) % 10);
        toolbox.countUI[0] = toolbox.digits[onesDigit];
        toolbox.countUI[1] = toolbox.digits[tensDigit];
        toolbox.countUI[2] = toolbox.digits[hundredsDigit];
        toolbox.countUI[3] = toolbox.digits[10]; // holds negative sign
        for (int i = 0; i < 4; i++) {
            toolbox.countUI[i]->setPosition((xPosition - (i * 21)), 512);  // Adjust the y-position as needed
            toolbox.window.draw(*toolbox.countUI[i]);
        }
    }

    // Display window
    toolbox.window.display();
}

// Flips the debug mode on/off. (Debug mode should initially be off/false.)
void toggleDebugMode() {
    Toolbox& toolbox = Toolbox::getInstance();

    if (!Toolbox::getInstance().debugMode) {
        // If entering debug mode
        Toolbox::getInstance().debugMode = true;
        toolbox.debugFlaggedMines = 0;
        storeFlaggedMines();  // Store flagged mines before entering debug mode
        revealAllMines();
    }
    else {
        // If exiting debug mode
        Toolbox::getInstance().debugMode = false;

        // Reset exploded mines to hidden
        int x = 0;
        while (toolbox.gameState->getTile(x, 0) != nullptr) {
            int y = 0;
            while (toolbox.gameState->getTile(x, y) != nullptr) {
                Tile* currentTile = toolbox.gameState->getTile(x, y);
                if (isMine(*currentTile) && currentTile->getState() == Tile::EXPLODED) {
                    currentTile->setState(Tile::HIDDEN);
                }
                y++;
            }
            x++;
        }

        reapplyFlaggedMines();  // Reapply flagged mines after exiting debug mode
    }
}

// Function to store the positions of flagged mines
void storeFlaggedMines() {
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.flaggedMinePositions.clear();

    int x = 0;
    while (toolbox.gameState->getTile(x, 0) != nullptr) {
        int y = 0;
        while (toolbox.gameState->getTile(x, y) != nullptr) {
            Tile* currentTile = toolbox.gameState->getTile(x, y);
            if (currentTile != nullptr && currentTile->getState() == Tile::FLAGGED) {
                toolbox.flaggedMinePositions.push_back(sf::Vector2i(x, y));
                toolbox.debugFlaggedMines++;
            }
            y++;
        }
        x++;
    }
}

// Function to reapply flags after exiting debug mode
void reapplyFlaggedMines() {
    Toolbox& toolbox = Toolbox::getInstance();
    for (const sf::Vector2i& position : toolbox.flaggedMinePositions) {
        Tile* currentTile = toolbox.gameState->getTile(position.x, position.y);
        if (currentTile != nullptr && !Toolbox::getInstance().debugMode) {
            currentTile->setState(Tile::FLAGGED);
        }
    }
}

// Returns true if debug mode is active, and false otherwise.
bool getDebugMode() {
    return Toolbox::getInstance().debugMode;
}

void loadTestBoard(const char* filepath) {
    // Clear debug-related data when loading a new board
    GameState* currentGameState = Toolbox::getInstance().gameState;
    delete currentGameState;
    Toolbox::getInstance().gameState = new GameState();
    Toolbox::getInstance().debugFlaggedMines = 0;
    Toolbox::getInstance().flaggedMinePositions.clear();

    // Check if the file exists
    if (!std::filesystem::exists(filepath)) {
        std::cerr << "Error: File not found - " << filepath << std::endl;
        return; // Exit the function if the file doesn't exist
    }

    // Attempt to open the file
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file - " << filepath << std::endl;
        return; // Exit the function if the file can't be opened
    }

    // Attempt to create a new GameState from the file
    try {
        Toolbox::getInstance().gameState = new GameState(filepath);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Encapsulates event-polling, rendering, and other logic necessary to handle input and output for the game
int gameLoop() {
    Toolbox& toolbox = Toolbox::getInstance();
    render();
    while (toolbox.window.isOpen()) {
        sf::Event event;
        while (toolbox.window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                // Game logic
                handleMouseClick(event.mouseButton);
                render();
            } else if (event.type == sf::Event::Closed) {
                toolbox.window.close();
            }
            // Check for game end conditions
            if((getTilesRevealed() + toolbox.gameState->getMineCount()) == getNumTiles()) {
                toolbox.gameState->setPlayStatus(GameState::WIN);
                toolbox.newGameButton->setSprite(toolbox.victory);
                revealAllMines();
                render();
            }
            else if (toolbox.gameState->getPlayStatus() == GameState::LOSS) {
                toolbox.window.draw(*toolbox.loss);
                revealAllMines();
                render();
            }
        }
    }

    //std::cout << "Exited game loop with play status: " << toolbox.gameState->getPlayStatus() << std::endl;
    return 0; // Exit code
}

// Handle mouse events
void handleMouseClick(sf::Event::MouseButtonEvent mouseButtonEvent) {
    Toolbox& toolbox = Toolbox::getInstance();
    sf::Vector2f mousePosition(static_cast<float>(mouseButtonEvent.x), static_cast<float>(mouseButtonEvent.y));

    // Iterate through each tile in the game grid
    int i = 0;
    while (toolbox.gameState->getTile(i, 0) != nullptr) {
        int j = 0;
        while (toolbox.gameState->getTile(i, j) != nullptr) {
            Tile* currentTile = toolbox.gameState->getTile(i, j);

            // Check if the game is in playing state and the mouse is within the boundaries of the current tile
            if (currentTile != nullptr && toolbox.gameState->getPlayStatus() == GameState::PLAYING) {
                if (mousePosition.x >= i * 32 &&
                    mousePosition.x < (i + 1) * 32 &&
                    mousePosition.y >= j * 32 &&
                    mousePosition.y < (j + 1) * 32) {

                    // Handle left click
                    if (mouseButtonEvent.button == sf::Mouse::Left && currentTile->getState() != Tile::FLAGGED) {
                        currentTile->onClickLeft();
                        if (isMine(*currentTile)) {
                            toolbox.gameState->setPlayStatus(GameState::LOSS);
                        }
                    }
                        // Handle right click
                    else if (mouseButtonEvent.button == sf::Mouse::Right) {
                        // Check if in debug mode
                        if (getDebugMode()) {
                            // In debug mode, set the state to FLAGGED directly
                            currentTile->setState(Tile::FLAGGED);
                            toolbox.debugFlaggedMines++;

                            // Add currentTile to flaggedMinePositions
                            toolbox.flaggedMinePositions.push_back(sf::Vector2i(i, j));
                        }
                        else {
                            // Not in debug mode, toggle the flag as usual
                            currentTile->onClickRight();
                        }
                    }
                }
            }
            j++;
        }
        i++;
    }

    // Handles button clicks
    // Check if the mouse click is within the boundaries of the new game button
    if (mousePosition.x >= toolbox.newGameButton->getPosition().x &&
        mousePosition.x < toolbox.newGameButton->getPosition().x + toolbox.buttonWidth &&
        mousePosition.y >= toolbox.newGameButton->getPosition().y &&
        mousePosition.y < toolbox.newGameButton->getPosition().y + toolbox.buttonHeight) {
        toolbox.newGameButton->onClick();
    }
        // Checks if mouse click is within boundaries of debug button
    else if (mousePosition.x >= toolbox.debugButton->getPosition().x &&
             mousePosition.x < toolbox.debugButton->getPosition().x + toolbox.buttonWidth &&
             mousePosition.y >= toolbox.debugButton->getPosition().y &&
             mousePosition.y < toolbox.debugButton->getPosition().y + toolbox.buttonHeight) {
        toolbox.debugButton->onClick();
    }
        // Checks if mouse click is within boundaries of test1 button
    else if (mousePosition.x >= toolbox.testButton1->getPosition().x &&
             mousePosition.x < toolbox.testButton1->getPosition().x + toolbox.buttonWidth &&
             mousePosition.y >= toolbox.testButton1->getPosition().y &&
             mousePosition.y < toolbox.testButton1->getPosition().y + toolbox.buttonHeight) {
        toolbox.testButton1->onClick();
    }
        // Checks if mouse click is within boundaries of test2 button
    else if (mousePosition.x >= toolbox.testButton2->getPosition().x &&
             mousePosition.x < toolbox.testButton2->getPosition().x + toolbox.buttonWidth &&
             mousePosition.y >= toolbox.testButton2->getPosition().y &&
             mousePosition.y < toolbox.testButton2->getPosition().y + toolbox.buttonHeight) {
        toolbox.testButton2->onClick();
    }
        // Checks if mouse click is within boundaries of test3 button
    else if (mousePosition.x >= toolbox.testButton3->getPosition().x &&
             mousePosition.x < toolbox.testButton3->getPosition().x + toolbox.buttonWidth &&
             mousePosition.y >= toolbox.testButton3->getPosition().y &&
             mousePosition.y < toolbox.testButton3->getPosition().y + toolbox.buttonHeight) {
        toolbox.testButton3->onClick();
    }
}


int main() {
    return launch();
}