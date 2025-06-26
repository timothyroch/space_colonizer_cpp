#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "Grid.h"
#include "Building.h"

class Game {
public:
    Game();         // Constructor
    ~Game();        // Destructor

    void run();     // Main game loop

private:
    void processEvents();   // Handle input events
    void update();          // Update game logic (placeholder for now)
    void render();          // Draw the game and UI

    void drawUI();          // Draw the side UI panel

    sf::RenderWindow window;    // Game window
    Grid* grid;                 // Pointer to the grid system
    bool isRunning;             // Game loop control flag

    BuildingType selectedBuilding;  // Currently selected building type

    // New for resource system
    int playerMoney;                       // Current player money
    std::map<BuildingType, int> buildingCosts; // Building costs

    // New for UI
    sf::Font uiFont;                       // UI font
};

#endif
