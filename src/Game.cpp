#include "Game.h"
#include <optional> // for std::optional

// Constructor
Game::Game()
: window(sf::VideoMode({800, 600}), "Space Colonizer")
, isRunning(true)
, selectedBuilding(BuildingType::PowerPlant) // Default selected building
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
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        // Window close
        if (event->is<sf::Event::Closed>()) {
            isRunning = false;
            window.close();
        }
        // Keyboard input to change building selection
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Num1) {
                selectedBuilding = BuildingType::PowerPlant;
            } else if (keyPressed->code == sf::Keyboard::Key::Num2) {
                selectedBuilding = BuildingType::Habitat;
            } else if (keyPressed->code == sf::Keyboard::Key::Num3) {
                selectedBuilding = BuildingType::ResearchLab;
            }
        }
        // Mouse button pressed to place building
        else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressed->button == sf::Mouse::Button::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2i tilePos = grid->getTileFromMouse(mousePos);
                if (tilePos.x != -1 && tilePos.y != -1 && grid->isTileEmpty(tilePos.x, tilePos.y)) {
                    grid->placeBuilding(tilePos.x, tilePos.y, selectedBuilding);
                }
            }
        }
    }
}

// Update game logic (empty for now)
void Game::update() {
    // Placeholder for future updates
}

// Render everything
void Game::render() {
    window.clear();
    grid->render(window);
    window.display();
}
