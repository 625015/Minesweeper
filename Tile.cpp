// Liam Ballard
// COP3504
// Project 4

#include "Tile.h"
#include "Toolbox.h"

// Constructs a new tile object at the designated _position
Tile::Tile(sf::Vector2f _position) {
    currentPosition = _position;
    currentState = HIDDEN;
    neighborTiles = std::array<Tile*, 8>{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
}

// Returns position of this tile
sf::Vector2f Tile::getLocation() {
    return currentPosition;
}

//Returns current state of this tile
Tile::State Tile::getState() {
    return currentState;
}

// Returns pointer to array of Tile pointers
std::array<Tile*, 8>& Tile::getNeighbors() {
    return neighborTiles;
}

// Sets the state of this tile, triggers other behaviors related to the state change (including visualization)
void Tile::setState(State _state) {
    currentState = _state;
}

// Populates/replaces the neighboring tile container
void Tile::setNeighbors(std::array<Tile*, 8> _neighbors) {
    neighborTiles = _neighbors;
}

// Defines the reveal behavior for a tile when the left mouse button is clicked inside its boundaries
// Reveals tile and the number of mines surrounding it
void Tile::onClickLeft() {
    if (getState() == HIDDEN || getState() == FLAGGED) {
        if (isMine(*this)) {
            setState(EXPLODED);
        }
        else {
            setState(REVEALED);
            revealNeighbors();
        }
    }
}

// Toggles this tile’s state between FLAGGED and HIDDEN
void Tile::onClickRight() {
    if (getState() == HIDDEN) {
        setState(FLAGGED);
    } else if (getState() == FLAGGED) {
        setState(HIDDEN);
    }
}

// Render this tile to the screen according to is state
void Tile::draw() {
    sf::Sprite tileSprite; // Holds sprite of this tile
    sf::Sprite revealedSprite; // Holds revealed tile sprite
    sf::Sprite hiddenSprite; // Holds hidden background sprite
    sf::Sprite mineSprite; // Holds mine sprite
    sf::Sprite explodedSprite; // Holds exploded sprite
    sf::Sprite flaggedSprite; // Holds flagged sprite
    sf::Texture revealedTexture; // Holds texture of revealed-state tile
    sf::Texture hiddenTexture; // Holds texture of hidden-state tile
    sf::Texture flaggedTexture; // Holds texture of flagged-state tile
    sf::Texture explodedTexture; // Holds texture of exploded-state tile
    sf::Texture oneTexture; // Holds sprite of number 1
    sf::Texture twoTexture; // Holds texture of number 2
    sf::Texture threeTexture; // Holds texture of number 3
    sf::Texture fourTexture; // Holds texture of number 4
    sf::Texture fiveTexture; // Holds texture of number 5
    sf::Texture sixTexture; // Holds texture of number 6
    sf::Texture sevenTexture; // Holds texture of number 7
    sf::Texture eightTexture; // Holds texture of number 8
    sf::Sprite one; // Holds texture of number 1
    sf::Sprite two; // Holds texture of number 2
    sf::Sprite three; // Holds texture of number 3
    sf::Sprite four; // Holds texture of number 4
    sf::Sprite five; // Holds texture of number 5
    sf::Sprite six; // Holds texture of number 6
    sf::Sprite seven; // Holds texture of number 7
    sf::Sprite eight; // Holds texture of number 8

    // Sets tileSprite to revealedTexture if REVEALED
    if (currentState == REVEALED) {
        Toolbox& toolbox = Toolbox::getInstance();
        sf::Texture* tileTexture;
        // Loads revealed texture from png file, handles error with loading
        if (!revealedTexture.loadFromFile("P4-data/images/tile_revealed.png")) {
            std::cerr << "Failed to load revealed texture!" << std::endl;
        }
        revealedSprite.setTexture(revealedTexture);

        // Find number of adjacent mines to current tile
        int numMinesAdjacent = 0;
        for (int i = 0; i < neighborTiles.size(); i++) {
            Tile *currentNeighbor = neighborTiles.at(i); // Holds pointer to current neighbor tile
            // Check if neighbor is not null
            if (currentNeighbor != nullptr) {
                // Check if neighbor is a mine
                bool mineStatus = isMine(*currentNeighbor);
                if(mineStatus) {
                    numMinesAdjacent += 1;
                }
            }
        }

        //Load number textures
        if (!oneTexture.loadFromFile("P4-data/images/number_1.png")) {
            std::cerr << "Failed to load number 1 texture!" << std::endl;
        }
        one.setTexture(oneTexture);

        if (!twoTexture.loadFromFile("P4-data/images/number_2.png")) {
            std::cerr << "Failed to load number 1 texture!" << std::endl;
        }
        two.setTexture(twoTexture);

        if (!threeTexture.loadFromFile("P4-data/images/number_3.png")) {
            std::cerr << "Failed to load number 1 texture!" << std::endl;
        }
        three.setTexture(threeTexture);

        if (!fourTexture.loadFromFile("P4-data/images/number_4.png")) {
            std::cerr << "Failed to load number 1 texture!" << std::endl;
        }
        four.setTexture(fourTexture);

        if (!fiveTexture.loadFromFile("P4-data/images/number_5.png")) {
            std::cerr << "Failed to load number 1 texture!" << std::endl;
        }
        five.setTexture(fiveTexture);

        if (!sixTexture.loadFromFile("P4-data/images/number_6.png")) {
            std::cerr << "Failed to load number 1 texture!" << std::endl;
        }
        six.setTexture(sixTexture);

        if (!sevenTexture.loadFromFile("P4-data/images/number_7.png")) {
            std::cerr << "Failed to load number 1 texture!" << std::endl;
        }
        seven.setTexture(sevenTexture);

        if (!eightTexture.loadFromFile("P4-data/images/number_8.png")) {
            std::cerr << "Failed to load number 1 texture!" << std::endl;
        }
        eight.setTexture(eightTexture);

        // Set texture of tileSprite to only revealed texture if no neighboring mines
        if (numMinesAdjacent == 0) {
            tileSprite.setTexture(revealedTexture);
        }

        // Draw number texture if there are neighboring mines
        if (numMinesAdjacent > 0 && numMinesAdjacent <= 8) {
            // Adjust position based on the number of digits
            float xOffset = (revealedTexture.getSize().x - oneTexture.getSize().x) / 2.0f;
            float yOffset = (revealedTexture.getSize().y - oneTexture.getSize().y) / 2.0f;

            sf::Vector2f numberPosition = tileSprite.getPosition() + sf::Vector2f(xOffset, yOffset);

            // Draw the appropriate number texture directly onto the tile sprite
            switch (numMinesAdjacent) {
                case 1: tileTexture = drawOverlayTextures(oneTexture, revealedTexture); break;
                case 2: tileTexture = drawOverlayTextures(twoTexture, revealedTexture); break;
                case 3: tileTexture = drawOverlayTextures(threeTexture, revealedTexture);; break;
                case 4: tileTexture = drawOverlayTextures(fourTexture, revealedTexture);; break;
                case 5: tileTexture = drawOverlayTextures(fiveTexture, revealedTexture);; break;
                case 6: tileTexture = drawOverlayTextures(sixTexture, revealedTexture);; break;
                case 7: tileTexture = drawOverlayTextures(sevenTexture, revealedTexture);; break;
                case 8: tileTexture = drawOverlayTextures(eightTexture, revealedTexture);; break;
            }

            tileSprite.setTexture(*tileTexture);
        }
    }

    // Sets tileSprite to hiddenTexture if HIDDEN
    else if (currentState == HIDDEN) {
        // Loads hidden texture from png file, handles error with loading
        if (!hiddenTexture.loadFromFile("P4-data/images/tile_hidden.png")) {
            std::cerr << "Failed to load hidden texture!" << std::endl;
        }
        hiddenSprite.setTexture(hiddenTexture);
        tileSprite.setTexture(hiddenTexture);
    }

    // Sets tileSprite to explodedTexture if EXPLODED
    else if (currentState == EXPLODED) {
        sf::Texture* tileTexture;
        if (!hiddenTexture.loadFromFile("P4-data/images/tile_hidden.png")) {
            std::cerr << "Failed to load hidden texture!" << std::endl;
        }
        // Loads exploded texture from png file, handles error with loading
        if (!explodedTexture.loadFromFile("P4-data/images/mine.png")) {
            std::cerr << "Failed to load mine texture!" << std::endl;
        }
        mineSprite.setTexture(explodedTexture);

        tileTexture = drawOverlayTextures(explodedTexture, hiddenTexture);
        tileSprite.setTexture(*tileTexture);
    }

    // Sets tileSprite to flaggedTexture if FLAGGED
    else if(currentState == FLAGGED) {
        sf::Texture* tileTexture;
        if (!hiddenTexture.loadFromFile("P4-data/images/tile_hidden.png")) {
            std::cerr << "Failed to load hidden texture!" << std::endl;
        }
        // Loads exploded texture from png file, handles error with loading
        if (!flaggedTexture.loadFromFile("P4-data/images/flag.png")) {
            std::cerr << "Failed to load flag texture!" << std::endl;
        }
        flaggedSprite.setTexture(flaggedTexture);

        tileTexture = drawOverlayTextures(flaggedTexture, hiddenTexture);
        tileSprite.setTexture(*tileTexture);
    }

    // Get reference of Toolbox instance
    Toolbox& toolbox = Toolbox::getInstance();

    // Set position of sprite to position of tile; ensures it loads in correct spot
    tileSprite.setPosition(currentPosition.x * toolbox.tileWidth, currentPosition.y * toolbox.tileHeight);

    // Draw the tileSprite onto the window using toolbox window variable
    toolbox.window.draw(tileSprite);
}

// Based on State and mine content of the tile neighbors, set their state to REVEALED
void Tile::revealNeighbors() {
    // Loop through all neighbor Tile pointers, set to revealed if not already
    if(getState() != FLAGGED && !isMine(*this)) {
        if(getState() != REVEALED) {
            setState(REVEALED);
        }
        bool zeroAdjacent = true;
        // zeroAdjacent if no adjacent neighborTiles are mines
        for(int i = 0; i < neighborTiles.size(); i++) {
            if(neighborTiles.at(i) != nullptr && isMine(*neighborTiles.at(i))) {
                zeroAdjacent = false;
                break;
            }
        }
        // If the current tile is a 0, reveal its adjacent tiles
        if (zeroAdjacent) {
            for (int i = 0; i < neighborTiles.size(); i++) {
                Tile* neighbor = neighborTiles.at(i);
                if (neighbor != nullptr && neighbor->getState() != REVEALED &&
                neighbor->getState() != FLAGGED) {
                    neighbor->revealNeighbors();
                }
            }
        }
        // Reveal neighbors of the current tile
        for (int i = 0; i < neighborTiles.size(); i++) {
            Tile* neighbor = neighborTiles.at(i);
            if (zeroAdjacent && neighbor != nullptr && neighbor->getState() != REVEALED &&
            neighbor->getState() != FLAGGED) {
                neighbor->setState(Tile::REVEALED);
            }
        }
    }
}

