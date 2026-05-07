/*#pragma once

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
*/
#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <string_view>
#include <iostream>

class PlayerTextures
{
public:
    sf::Texture texture;

    explicit PlayerTextures(std::string_view playerTexturePath)
    {
        const std::string path(playerTexturePath);
        if (!texture.loadFromFile(path))
        {
            std::cerr << "FAILED to load texture: " << path << "\n";
        }
        else
        {
            std::cerr << "Loaded texture: " << path << "\n";
        }
    }
};