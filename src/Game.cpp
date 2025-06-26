#include "Game.h"
#include <optional>
#include <iostream>

// Constructor
Game::Game()
: window(sf::VideoMode({1000, 600}), "Space Colonizer") // Wider window for UI
, isRunning(true)
, selectedBuilding(BuildingType::PowerPlant)
, playerMoney(1000) // Starting money
{
    grid = new Grid(10, 10, 50); // 10×10 grid, each tile 50px

    // Set building costs
    buildingCosts[BuildingType::PowerPlant] = 100;
    buildingCosts[BuildingType::Habitat] = 150;
    buildingCosts[BuildingType::ResearchLab] = 200;

    // Load UI font
    if (!uiFont.loadFromFile("assets/arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
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
                    int cost = buildingCosts[selectedBuilding];

                    if (playerMoney >= cost) {
                        playerMoney -= cost;
                        grid->placeBuilding(tilePos.x, tilePos.y, selectedBuilding);
                    } else {
                        std::cout << "Not enough money!" << std::endl;
                    }
                }
            }
        }
    }
}

// Update game logic (placeholder)
void Game::update() {
    // Future resource production can go here
}

// Draw the UI panel
void Game::drawUI() {
    // Draw player's money
    sf::Text moneyText;
    moneyText.setFont(uiFont);
    moneyText.setString("Money: " + std::to_string(playerMoney));
    moneyText.setCharacterSize(20);
    moneyText.setFillColor(sf::Color::White);
    moneyText.setPosition(520, 20); // Position in the right panel
    window.draw(moneyText);

    // Draw building selection
    sf::Text selectionText;
    selectionText.setFont(uiFont);
    std::string selectedStr = "Selected: ";
    if (selectedBuilding == BuildingType::PowerPlant)
        selectedStr += "Power Plant (1)";
    else if (selectedBuilding == BuildingType::Habitat)
        selectedStr += "Habitat (2)";
    else if (selectedBuilding == BuildingType::ResearchLab)
        selectedStr += "Research Lab (3)";

    selectionText.setString(selectedStr);
    selectionText.setCharacterSize(18);
    selectionText.setFillColor(sf::Color::White);
    selectionText.setPosition(520, 60);
    window.draw(selectionText);

    // Draw building costs
    sf::Text costText;
    costText.setFont(uiFont);
    costText.setCharacterSize(16);
    costText.setFillColor(sf::Color::White);
    costText.setPosition(520, 100);
    costText.setString("Costs:\n1. Power Plant: 100\n2. Habitat: 150\n3. Research Lab: 200");
    window.draw(costText);
}

// Render everything
void Game::render() {
    window.clear();
    grid->render(window);
    drawUI(); // Draw the side interface
    window.display();
}
