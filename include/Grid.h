#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "Building.h"

struct Tile {
    sf::RectangleShape shape;
    BuildingType buildingType;
    sf::Sprite buildingSprite;

    Tile(float x, float y, float size);
};

class Grid {
public:
    Grid(int rows, int cols, float tileSize);

    void render(sf::RenderWindow& window);
    bool isTileEmpty(int row, int col) const;
    void placeBuilding(int row, int col, BuildingType buildingType);
    sf::Vector2i getTileFromMouse(sf::Vector2i mousePos);

private:
    std::vector<std::vector<Tile>> tiles;
    std::map<BuildingType, sf::Texture> buildingTextures; // Central texture storage
    int rows, cols;
    float tileSize;

    void loadBuildingTextures(); // Load all textures once
};

#endif
