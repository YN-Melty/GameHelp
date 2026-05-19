#pragma once
#include "Scene/Scene.h"
#include "EnemiesManager/FinalBossEnemyStats.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include "BaseCharacter.h"

class FinalBoss : public BaseCharacter
{
public:
    FinalBoss(EngineContext &context, const std::string &texturePath = FinalBossEnemyStats::texturePath);

private:
    int hp;

    int speed;

    bool onGround = false;
    float velocityY = 0.f;

    sf::Texture finalBossTexture;
    sf::Sprite finalBossSprite;
    sf::RectangleShape FinalBossHitBox;

public:
    void initChar();

    void WallCollisionDetection(const sf::RectangleShape &playerHitBox,
                                float leftWall, float rightWall, float ceiling, float floor);

    virtual sf::RectangleShape &getHitBox();
    const sf::RectangleShape &getHitBox() const;
    const sf::Sprite &getSprite() const;
    sf::Sprite &getSprite();

    void ApplyDamage(float amount) override;

    void Attack(BaseCharacter &target) override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow &window) override;
    void setHitBoxToSprite();

    void EnemyAction(float dt,

                     float gravity,
                     sf::RectangleShape &hitbox,
                     float leftWall, float rightWall, float ceiling, float floor);
    void handleJump();
    void handleMovement(float dt);
    void WallCollisionDetection(sf::RectangleShape &hitbox,
                                float leftWall, float rightWall, float ceiling, float floor);
    void applyGravity(float gravity, float dt);
};