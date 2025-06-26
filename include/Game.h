#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Grid.h"

class Game {
public:
    Game();         // Constructor
    ~Game();        // Destructor

    void run();     // Main game loop

private:
    void processEvents();  // Handle input events
    void update();         // Update game logic (placeholder for now)
    void render();         // Draw to the window

    sf::RenderWindow window;  // Game window
    Grid* grid;               // Pointer to the grid system
    bool isRunning;           // Game loop control flag
};

#endif

