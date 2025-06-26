#include "Grid.h"

Tile::Tile(float x, float y, float size) : occupied(false) {
    shape.setSize(sf::Vector2f(size - 1, size - 1)); // Small gap for grid lines
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Green);
}

Grid::Grid(int rows, int cols, float tileSize) : rows(rows), cols(cols), tileSize(tileSize) {
    tiles.resize(rows, std::vector<Tile>(cols, Tile(0, 0, tileSize)));

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            tiles[row][col] = Tile(col * tileSize, row * tileSize, tileSize);
        }
    }
}

void Grid::render(sf::RenderWindow& window) {
    for (const auto& row : tiles) {
        for (const auto& tile : row) {
            window.draw(tile.shape);
        }
    }
}

bool Grid::isTileEmpty(int row, int col) const {
    return !tiles[row][col].occupied;
}

void Grid::occupyTile(int row, int col) {
    tiles[row][col].occupied = true;
    tiles[row][col].shape.setFillColor(sf::Color::Blue); // Color change when occupied
}

sf::Vector2i Grid::getTileFromMouse(sf::Vector2i mousePos) {
    int col = mousePos.x / tileSize;
    int row = mousePos.y / tileSize;

    if (row >= 0 && row < rows && col >= 0 && col < cols)
        return sf::Vector2i(row, col);
    else
        return sf::Vector2i(-1, -1); // Invalid tile
}
