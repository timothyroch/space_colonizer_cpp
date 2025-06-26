#include "Game.h"
#include <optional> // for std::optional

// Constructor
Game::Game()
: window(sf::VideoMode({800, 600}), "Space Colonizer")
, isRunning(true)
{
    grid = new Grid(10, 10, 50); // 10×10 grid, each tile 50px
}

// Destructor
Game::~Game() {
    delete grid;
}

// Main game loop
void Game::run() {
    while (isRunning) {
        processEvents();
        update();
        render();
    }
}

// Handle SFML events
void Game::processEvents() {
    // pollEvent now returns std::optional<sf::Event>
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        // Window close
        if (event->is<sf::Event::Closed>()) {
            isRunning = false;
            window.close();
        }
        // Mouse button pressed
        else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressed->button == sf::Mouse::Button::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2i tilePos = grid->getTileFromMouse(mousePos);
                if (tilePos.x != -1 && tilePos.y != -1 && grid->isTileEmpty(tilePos.x, tilePos.y)) {
                    grid->occupyTile(tilePos.x, tilePos.y);
                }
            }
        }
    }
}

// Update game logic (empty for now)
void Game::update() {
    // future game-state updates
}

// Render everything
void Game::render() {
    window.clear();
    grid->render(window);
    window.display();
}
