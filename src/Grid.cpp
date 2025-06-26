#include "Grid.h"
#include <stdexcept>

// Tile constructor
Tile::Tile(float x, float y, float size)
: shape({ size - 1.f, size - 1.f })
, buildingType(BuildingType::None)
{
    shape.setPosition({ x, y });
    shape.setFillColor(sf::Color::Green);
}

// Load textures for each building type
void Grid::loadBuildingTextures() {
    // Map building types to asset paths
    std::map<BuildingType, std::string> paths = {
        { BuildingType::PowerPlant,  "assets/c79a2673-280c-43db-9fd3-83edc3ade4ab.jpg" },
        { BuildingType::Habitat,     "assets/c4d6018f-428c-45e9-b12e-cb67c8f44a24.jpg" },
        { BuildingType::ResearchLab, "assets/19911.jpg" }
    };

    for (auto& [type, path] : paths) {
        sf::Texture tex;
        if (!tex.loadFromFile(path)) {
            throw std::runtime_error("Failed to load texture: " + path);
        }
        buildingTextures[type] = std::move(tex);
    }
}

// Grid constructor
Grid::Grid(int rows, int cols, float tileSize)
: rows(rows)
, cols(cols)
, tileSize(tileSize)
{
    loadBuildingTextures();

    tiles.resize(rows);
    for (int r = 0; r < rows; ++r) {
        tiles[r].reserve(cols);
        for (int c = 0; c < cols; ++c) {
            tiles[r].emplace_back(c * tileSize, r * tileSize, tileSize);
        }
    }
}

// Draw all tiles and any buildings
void Grid::render(sf::RenderWindow& window) {
    for (const auto& row : tiles) {
        for (const auto& tile : row) {
            window.draw(tile.shape);

            if (tile.buildingType != BuildingType::None) {
                // Create a sprite from the stored texture
sf::Sprite sprite(buildingTextures.at(tile.buildingType));
sprite.setPosition(tile.shape.getPosition());

sf::Vector2f tileSizeVector(tile.shape.getSize());
sf::Vector2u textureSize = sprite.getTexture()->getSize();

// Calculate scaling factor
sf::Vector2f scaleFactor(
    tileSizeVector.x / textureSize.x,
    tileSizeVector.y / textureSize.y
);

sprite.setScale(scaleFactor);

window.draw(sprite);


            }
        }
    }
}

// Check if a tile is free
bool Grid::isTileEmpty(int row, int col) const {
    return tiles[row][col].buildingType == BuildingType::None;
}

// Place a building of a specific type on the tile
void Grid::placeBuilding(int row, int col, BuildingType type) {
    tiles[row][col].buildingType = type;
}

// Convert mouse position to tile indices
sf::Vector2i Grid::getTileFromMouse(sf::Vector2i mousePos) {
    int col = mousePos.x / tileSize;
    int row = mousePos.y / tileSize;
    if (row >= 0 && row < rows && col >= 0 && col < cols)
        return { row, col };
    return { -1, -1 };  // invalid
}
