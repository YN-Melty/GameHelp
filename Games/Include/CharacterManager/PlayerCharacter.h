#pragma once

#include "CharacterManager/Managers/PlayerStats.h"
#include "CharacterManager/Managers/PlayerTextures.h"
#include <SFML/Graphics/Sprite.hpp>

class PlayerCharacter
{
public:
    PlayerCharacter();

    PlayerStats playerStats;
    PlayerTextures playerTexture;
    sf::Sprite sprite;
};