#include "Core/EngineConfig.h"
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include <fstream>
#include <cassert>

EngineConfig::EngineConfig()
{
    std::ifstream file("Content/Config.json");
    assert(file);

    nlohmann::json json = nlohmann::json::parse(file);
    windowTitle = json["windowTitle"];
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    windowSize = {static_cast<float>(desktop.size.x), static_cast<float>(desktop.size.y)}; // windowSize = {json["windowSize"][0], json["windowSize"][1]};
    disableSfmlLogs = json["disableSfmlLogs"];
    maximumDeltaTime = sf::seconds(json["maximumDeltaTime"]);
    globalVolume = json["globalVolume"];
    backgroundColor = {json["backgroundColor"][0],
                       json["backgroundColor"][1],
                       json["backgroundColor"][2]};
    cursorRadius = json["cursorRadius"];
    cursorSpeed = json["cursorSpeed"];
    cursorColor = {json["cursorColor"][0],
                   json["cursorColor"][1],
                   json["cursorColor"][2]};
    joystickDeadzone = json["joystickDeadzone"];
}