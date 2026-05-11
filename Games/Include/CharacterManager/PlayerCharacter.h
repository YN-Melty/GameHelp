#pragma once

#include "CharacterManager/Managers/PlayerStats.h"
#include "CharacterManager/Managers/PlayerTextures.h"
#include <SFML/Graphics/Sprite.hpp>
#include "Scene/Scene.h"
#include "BaseCharacter.h"

class PlayerCharacter : public BaseCharacter
{
public:
    PlayerStats playerStats;
    PlayerTextures playerTexture;
    sf::Sprite sprite;

    float velocityY = 0.f;
    bool onGround = false;

    PlayerCharacter(EngineContext &);

    // Main update per frame
    void pcAction(const InputManager &input, float dt,
                  float moveSpeed,
                  float gravity,
                  const sf::RectangleShape &playerHitBox,
                  float leftWall, float rightWall, float ceiling, float floor);

private:
    // Modular action handlers
    void handleMovement(const InputManager &input, float dt, float moveSpeed);
    void handleJump(const InputManager &input);
    void applyGravity(float gravity, float dt);
    void WallCollisionDetection(const sf::RectangleShape &playerHitBox,
                                float leftWall, float rightWall, float ceiling, float floor);
};