#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <SFML/Graphics.hpp>

enum class BuildingType {
    None,
    PowerPlant,
    Habitat,
    ResearchLab
};

struct Building {
    BuildingType type;
    std::string name;
    int cost;

    Building(BuildingType type = BuildingType::None);

    sf::Color getColor() const; // Each building type has its own color
};

#endif
