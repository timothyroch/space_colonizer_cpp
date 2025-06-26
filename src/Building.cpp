#include "Building.h"

Building::Building(BuildingType type) : type(type) {
    switch (type) {
        case BuildingType::PowerPlant:
            name = "Power Plant";
            cost = 100;
            break;
        case BuildingType::Habitat:
            name = "Habitat";
            cost = 150;
            break;
        case BuildingType::ResearchLab:
            name = "Research Lab";
            cost = 200;
            break;
        default:
            name = "None";
            cost = 0;
            break;
    }
}

sf::Color Building::getColor() const {
    switch (type) {
        case BuildingType::PowerPlant:
            return sf::Color::Yellow;
        case BuildingType::Habitat:
            return sf::Color::Magenta;
        case BuildingType::ResearchLab:
            return sf::Color::Cyan;
        default:
            return sf::Color::Green;
    }
}
