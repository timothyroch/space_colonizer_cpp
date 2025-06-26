#include "Game.h"

// Constructor
Game::Game() : window(sf::VideoMode({800, 600}), "Space Colonizer"), isRunning(true) {
    grid = new Grid(10, 10, 50); // 10x10 grid, 50px tiles
}

// Destructor
Game::~Game() {
    delete grid;
}

// Game Loop
void Game::run() {
    while (isRunning) {
        processEvents();
        update();
        render();
    }
}

// Handle Events (including mouse clicks)
void Game::processEvents() {
    while (auto event = window.pollEvent()) {
        if (event->type == sf::Event::Closed) {
            isRunning = false;
        }

        if (event->type == sf::Event::MouseButtonPressed && event->mouseButton.button == sf::Mouse::Button::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2i tilePos = grid->getTileFromMouse(mousePos);

            if (tilePos.x != -1 && tilePos.y != -1 && grid->isTileEmpty(tilePos.x, tilePos.y)) {
                grid->occupyTile(tilePos.x, tilePos.y);
            }
        }
    }
}

// Update Game State (empty for now)
void Game::update() {
    // Placeholder for future updates
}

// Render the Game
void Game::render() {
    window.clear();
    grid->render(window);
    window.display();
}
