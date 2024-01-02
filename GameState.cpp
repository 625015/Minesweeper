// Liam Ballard
// COP3504
// Project 4

#include "GameState.h"

// GameState default constructor
GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines) {
    dimensions = _dimensions;
    mineCount = _numberOfMines;
    flagCount = 0;
    status = PLAYING;
    std::vector<std::vector<bool>> mineField = placeMines(mineCount, dimensions.x, dimensions.y);
    board = setBoard(mineField, float(dimensions.x), float(dimensions.y));
}

// Source for tellg() function:
// GeeksforGeeks. (2018, June 5). Tellg() function in C++ with example. GeeksforGeeks.
// https://www.geeksforgeeks.org/tellg-function-c-example/

GameState::GameState(const char* filepath) {
    status = PLAYING;
    flagCount = 0;
    std::ifstream file(filepath);

    // Open file
    if (!file.is_open()) {
        std::cerr << "File did not open" << std::endl;
    }

    // Read dimensions of the game board
    // Find number of columns
    // Find current position of the file pointer
    std::string line;

    // Read first line
    std::getline(file, line);

    // Calculate length of the first line
    int rows = line.length();

    // Count columns
    int columns = 1;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            columns++;
        }
    }

    // sf::Vectori w/ rows, cols in file
    dimensions = sf::Vector2i(rows, columns);
    std::vector<std::vector<bool>> mineField(rows, std::vector<bool>(columns, false));

    // Reset the file pointer again
    file.clear();
    file.seekg(0, std::ios::beg);

    mineCount = 0;
    char currentChar;
    int charCount = 0;

    // Read each character and place mines
    while (file.get(currentChar)) {
        if (currentChar == '1') {
            int rowIndex = charCount % rows;
            int colIndex = charCount / rows;
            mineCount++;
            mineField[rowIndex][colIndex] = true;
        }
        // Skip newline characters
        else if (currentChar == '\n' || currentChar == '\r') {
            continue;
        }
        charCount++;
    }
    file.close();

    // Place the mines in a 2D vector
    board = setBoard(mineField, float(rows), float(columns));
}

// Returns a pointer to the Tile at the specified coordinates, or nullptr if out of bounds
Tile* GameState::getTile(int x, int y) {
    // If out of bounds, return nullptr
    if(x < 0 || x > dimensions.x - 1 || y < 0 || y > dimensions.y - 1) {
        return nullptr;
    }
    // Return tile at coordinates given
    else {
        Tile* currentTile = board[x][y];
        return currentTile;
    }
}

// Current count of the number of flags placed on the screen
int GameState::getFlagCount() {
    flagCount = 0;
    // Iterate through board, adding to flag count if a tile is FLAGGED
    for(int i = 0; i < dimensions.x; i++) {
        for (int j = 0; j < dimensions.y; j++) {
            if(board[i][j]->getState() == Tile::FLAGGED) {
                flagCount++;
            }
        }
    }
    return flagCount;
}

// Current count of the number of mines actually on the board
int GameState::getMineCount() {
    return mineCount;
}

// Returns the play status of the game
GameState::PlayStatus GameState::getPlayStatus() {
    return status;
}

// Sets the play status of the game
void GameState::setPlayStatus(GameState::PlayStatus _status) {
    status = _status;
}

GameState::~GameState() {
    // Deallocate board memory
    for (int i = 0; i < dimensions.x; i++) {
        for (int j = 0; j < dimensions.y; j++) {
            delete board[i][j];
        }
    }
}