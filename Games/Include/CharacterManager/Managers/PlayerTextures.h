#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include "CharacterManager/Managers/Config/PlayerStatsConfig.h"

class PlayerTextures
{
public:
    sf::Texture texture;
    PlayerTextures(const std::string &PlayerTexture)
    {
        texture.loadFromFile(PlayerTexture);
    }
};
