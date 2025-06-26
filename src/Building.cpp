bool Building::loadTexture() {
    std::string path;

    switch (type) {
        case BuildingType::PowerPlant:
            path = "assets/powerplant.jpg";
            break;
        case BuildingType::Habitat:
            path = "assets/habitat.jpg";
            break;
        case BuildingType::ResearchLab:
            path = "assets/researchlab.jpg";
            break;
        default:
            return false;
    }

    if (texture.loadFromFile(path)) {
        sprite.setTexture(texture);
        return true;
    }

    return false;
}
