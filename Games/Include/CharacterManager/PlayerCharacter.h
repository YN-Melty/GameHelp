#pragma once

#include "CharacterManager/Managers/PlayerStats.h"
#include "CharacterManager/Managers/PlayerTextures.h"
#include <SFML/Graphics/Sprite.hpp>

class PlayerCharacter
{
public:
    PlayerStats playerStats;
    PlayerTextures playerTexture;
    sf::Sprite sprite;

    PlayerCharacter();
};