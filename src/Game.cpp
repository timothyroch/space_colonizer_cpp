#include "Game.h"
#include <optional>
#include <iostream>

// Constructor
Game::Game()
: window(sf::VideoMode({1000, 600}), "Space Colonizer")
, isRunning(true)
, selectedBuilding(BuildingType::PowerPlant)
, playerMoney(1000)
{
    grid = new Grid(10, 10, 50);

    buildingCosts[BuildingType::PowerPlant] = 100;
    buildingCosts[BuildingType::Habitat] = 150;
    buildingCosts[BuildingType::ResearchLab] = 200;

    if (!uiFont.openFromFile("assets/arial.ttf")) { // SFML 3 uses openFromFile
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
        if (event->is<sf::Event::Closed>()) {
            isRunning = false;
            window.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Num1) {
                selectedBuilding = BuildingType::PowerPlant;
            } else if (keyPressed->code == sf::Keyboard::Key::Num2) {
                selectedBuilding = BuildingType::Habitat;
            } else if (keyPressed->code == sf::Keyboard::Key::Num3) {
                selectedBuilding = BuildingType::ResearchLab;
            }
        }
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

// Placeholder for future updates
void Game::update() {}

// Draw the UI panel
void Game::drawUI() {
    // Money text
    sf::Text moneyText(uiFont, "Money: " + std::to_string(playerMoney), 20);
    moneyText.setFillColor(sf::Color::White);
    moneyText.setPosition(sf::Vector2f(520, 20));
    window.draw(moneyText);

    // Selected building text
    std::string selectedStr = "Selected: ";
    if (selectedBuilding == BuildingType::PowerPlant)
        selectedStr += "Power Plant (1)";
    else if (selectedBuilding == BuildingType::Habitat)
        selectedStr += "Habitat (2)";
    else if (selectedBuilding == BuildingType::ResearchLab)
        selectedStr += "Research Lab (3)";

    sf::Text selectionText(uiFont, selectedStr, 18);
    selectionText.setFillColor(sf::Color::White);
    selectionText.setPosition(sf::Vector2f(520, 60));
    window.draw(selectionText);

    // Building costs text
    sf::Text costText(uiFont, "Costs:\n1. Power Plant: 100\n2. Habitat: 150\n3. Research Lab: 200", 16);
    costText.setFillColor(sf::Color::White);
    costText.setPosition(sf::Vector2f(520, 100));
    window.draw(costText);
}

// Render everything
void Game::render() {
    window.clear();
    grid->render(window);
    drawUI();
    window.display();
}
