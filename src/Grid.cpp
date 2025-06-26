#include "Grid.h"

// Tile constructor
Tile::Tile(float x, float y, float size) : occupied(false) {
    shape.setSize({ size - 1, size - 1 });            // small gap for grid lines
    shape.setPosition({ x, y });                       // SFML 3 now takes a Vector2f
    shape.setFillColor(sf::Color::Green);
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

// Draw all tiles
void Grid::render(sf::RenderWindow& window) {
    for (const auto& row : tiles) {
        for (const auto& tile : row) {
            window.draw(tile.shape);
        }
    }
}

// Check if a tile is free
bool Grid::isTileEmpty(int row, int col) const {
    return !tiles[row][col].occupied;
}

// Mark a tile occupied and change its color
void Grid::occupyTile(int row, int col) {
    tiles[row][col].occupied = true;
    tiles[row][col].shape.setFillColor(sf::Color::Blue);
}

// Convert mouse position to tile indices
sf::Vector2i Grid::getTileFromMouse(sf::Vector2i mousePos) {
    int col = mousePos.x / tileSize;
    int row = mousePos.y / tileSize;
    if (row >= 0 && row < rows && col >= 0 && col < cols)
        return { row, col };
    return { -1, -1 };  // invalid
}
