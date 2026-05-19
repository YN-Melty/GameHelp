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
    sf::RectangleShape playerHitBox;
    float moveSpeed = 500.0f;

    float velocityY = 0.f;
    bool onGround = false;

    PlayerCharacter(EngineContext &);

    // Main update per frame
    void pcAction(const InputManager &input, float dt,

                  float gravity,
                  const sf::RectangleShape &playerHitBox,
                  float leftWall, float rightWall, float ceiling, float floor);

    void ApplyDamage(float amount) override;
    void Attack(BaseCharacter &target) override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow &window) override;
    void initChar();
    sf::RectangleShape &getHitBox() override;
    sf::Sprite &getSprite() override;

private:
    void handleMovement(const InputManager &input, float dt);
    void handleJump(const InputManager &input);
    void applyGravity(float gravity, float dt);
    void WallCollisionDetection(const sf::RectangleShape &playerHitBox,
                                float leftWall, float rightWall, float ceiling, float floor);
};