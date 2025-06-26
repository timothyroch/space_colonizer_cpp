#include "Grid.h"

// Tile constructor
Tile::Tile(float x, float y, float size) {
    shape.setSize({ size - 1, size - 1 });  // Small gap for grid lines
    shape.setPosition({ x, y });            // SFML 3 position format
    shape.setFillColor(sf::Color::Green);
    building = Building(BuildingType::None);
}

// Grid constructor
Grid::Grid(int rows, int cols, float tileSize)
: rows(rows)
, cols(cols)
, tileSize(tileSize)
{
    tiles.resize(rows, std::vector<Tile>(cols, Tile(0, 0, tileSize)));
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            tiles[row][col] = Tile(col * tileSize, row * tileSize, tileSize);
        }
    }
}

// Draw all tiles and buildings
void Grid::render(sf::RenderWindow& window) {
    for (const auto& row : tiles) {
        for (const auto& tile : row) {
            window.draw(tile.shape);
            if (tile.building.type != BuildingType::None) {
                window.draw(tile.building.sprite);
            }
        }
    }
}

// Check if a tile is free
bool Grid::isTileEmpty(int row, int col) const {
    return tiles[row][col].building.type == BuildingType::None;
}

// Place a building of a specific type on the tile
void Grid::placeBuilding(int row, int col, BuildingType buildingType) {
    tiles[row][col].building = Building(buildingType);
    tiles[row][col].building.setPosition(
        tiles[row][col].shape.getPosition().x,
        tiles[row][col].shape.getPosition().y
    );
}

// Convert mouse position to tile indices
sf::Vector2i Grid::getTileFromMouse(sf::Vector2i mousePos) {
    int col = mousePos.x / tileSize;
    int row = mousePos.y / tileSize;
    if (row >= 0 && row < rows && col >= 0 && col < cols)
        return { row, col };
    return { -1, -1 };  // invalid
}
