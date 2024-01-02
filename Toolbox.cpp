// Liam Ballard
// COP3504
// Project 4

#include "Toolbox.h"

// Source for lambda function:
// GeeksforGeeks. (2022, October 7). Lambda expression in C++. GeeksforGeeks.
// https://www.geeksforgeeks.org/lambda-expression-in-c/

Toolbox::Toolbox() {
    window.create(sf::VideoMode(800, 600), "P4 _ Minesweeper, <Liam Ballard>", sf::Style::Close);
    gameState = new GameState(); // Includes board info
    debugMode = false;

    debugButton = new Button(sf::Vector2f(495, 512), []() { toggleDebugMode(); });
    // Loads victory texture from png file, handles loading error
    debugButtonTexture = new sf::Texture;
    auto debugButtonSprite = new sf::Sprite;
    if (!debugButtonTexture->loadFromFile("P4-data/images/debug.png")) {
        std::cerr << "Failed to load debug button texture!" << std::endl;
    }
    debugButtonSprite->setTexture(*debugButtonTexture);
    debugButton->setSprite(debugButtonSprite);

    newGameButton = new Button(sf::Vector2f(362, 512), []() { restart(); });
    // Loads new game texture from png file, handles loading error
    newGameTexture = new sf::Texture;
    newGameSprite = new sf::Sprite;
    if (!newGameTexture->loadFromFile("P4-data/images/face_happy.png")) {
        std::cerr << "Failed to load new game texture!" << std::endl;
    }
    newGameSprite->setTexture(*newGameTexture);

    testButton1 = new Button(sf::Vector2f(559, 512), []() { loadTestBoard("P4-data/boards/testboard1.brd") ; });
    // Loads new game texture from png file, handles loading error
    test1Texture = new sf::Texture;
    auto test1Sprite = new sf::Sprite;
    if (!test1Texture->loadFromFile("P4-data/images/test_1.png")) {
        std::cerr << "Failed to load test1 texture!" << std::endl;
    }
    test1Sprite->setTexture(*test1Texture);
    testButton1->setSprite(test1Sprite);

    testButton2 = new Button(sf::Vector2f(623, 512), []() { loadTestBoard("P4-data/boards/testboard2.brd"); });
    // Loads new game texture from png file, handles loading error
    test2Texture = new sf::Texture;
    auto test2Sprite = new sf::Sprite;
    if (!test2Texture->loadFromFile("P4-data/images/test_2.png")) {
        std::cerr << "Failed to load test2 texture!" << std::endl;
    }
    test2Sprite->setTexture(*test2Texture);
    testButton2->setSprite(test2Sprite);

    testButton3 = new Button(sf::Vector2f(687, 512), []() { loadTestBoard("P4-data/boards/testboard3.brd"); });
    // Loads new game texture from png file, handles loading error
    test3Texture = new sf::Texture;
    auto test3Sprite = new sf::Sprite;
    if (!test3Texture->loadFromFile("P4-data/images/Test_3.png")) {
        std::cerr << "Failed to load test3 texture!" << std::endl;
    }
    test3Sprite->setTexture(*test3Texture);
    testButton3->setSprite(test3Sprite);

    victoryTexture = new sf::Texture;
    victory = new sf::Sprite;
    // Loads victory texture from png file, handles loading error
    if (!victoryTexture->loadFromFile("P4-data/images/face_win.png")) {
        std::cerr << "Failed to load victory texture!" << std::endl;
    }
    victory->setTexture(*victoryTexture);

    lossTexture = new sf::Texture;
    loss = new sf::Sprite;
    // Loads loss texture from png file, handles loading error
    if (!lossTexture->loadFromFile("P4-data/images/face_lose.png")) {
        std::cerr << "Failed to load loss texture!" << std::endl;
    }
    loss->setTexture(*lossTexture);

    // Create mine counter
    // Load the digits texture
    digitsTexture.loadFromFile("P4-data/images/digits.png");

    // Get tile size
    sf::Texture revealedTexture;
    if (!revealedTexture.loadFromFile("P4-data/images/tile_revealed.png")) {
        std::cerr << "Failed to load revealed texture!" << std::endl;
    }
    sf::Sprite revealedSprite;
    revealedSprite.setTexture(revealedTexture);

    // Get tile dimensions
    sf::FloatRect tileBounds = revealedSprite.getGlobalBounds();
    tileWidth = tileBounds.width;
    tileHeight = tileBounds.height;

    // Get button dimensions
    sf::FloatRect buttonBounds = test1Sprite->getGlobalBounds();
    buttonWidth = buttonBounds.width;
    buttonHeight = buttonBounds.height;

    for (int i = 0; i < 11; i++) {
        digits[i] = new sf::Sprite;
    }

    // Create individual sprites for each digit
    for (int i = 0; i < 11; ++i) {
        digits[i]->setTexture(digitsTexture);
        // Set the texture rectangle for each digit
        digits[i]->setTextureRect(sf::IntRect(i * 21, 0, 21, 32));
    }
}

Toolbox& Toolbox::getInstance() {
    static Toolbox toolbox;
    return toolbox;
}

Toolbox::~Toolbox() {
    // Delete dynamically allocated objects
    // Delete Buttons
    delete debugButton;
    delete newGameButton;
    delete testButton1;
    delete testButton2;
    delete testButton3;

    // Delete Sprites
    delete victory;
    delete loss;
    delete newGameSprite;

    // Delete Textures
    delete newGameTexture;
    delete victoryTexture;
    delete lossTexture;
    delete debugButtonTexture;
    delete test1Texture;
    delete test2Texture;
    delete test3Texture;

    // Delete Digits Sprites
    for (int i = 0; i < 11; ++i) {
        delete digits[i];
    }

    delete gameState;
}