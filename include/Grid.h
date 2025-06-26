#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <vector>

struct Tile {
    sf::RectangleShape shape;
    bool occupied;

    Tile(float x, float y, float size);
};

class Grid {
public:
    Grid(int rows, int cols, float tileSize);

    void render(sf::RenderWindow& window);
    bool isTileEmpty(int row, int col) const;
    void occupyTile(int row, int col);
    sf::Vector2i getTileFromMouse(sf::Vector2i mousePos);

private:
    std::vector<std::vector<Tile>> tiles;
    int rows, cols;
    float tileSize;
};

#endif

