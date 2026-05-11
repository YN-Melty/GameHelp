#pragma once

#include "CharacterManager/Managers/PlayerStats.h"
#include "CharacterManager/Managers/PlayerTextures.h"
#include <SFML/Graphics/Sprite.hpp>
#include "Scene/Scene.h"

class PlayerCharacter
{
public:
    PlayerStats playerStats;
    PlayerTextures playerTexture;
    sf::Sprite sprite;

    float velocityY = 0.f;
    bool onGround = false;

    PlayerCharacter(EngineContext &);
    void pcAction(const InputManager &input, float dt,
                  float moveSpeed,
                  float gravity,
                  const sf::RectangleShape &playerHitBox,
                  float leftWall, float rightWall, float ceiling, float floor);
};