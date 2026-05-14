#include "EnemiesManager/FinalBoss.h"
#include <iostream>

FinalBoss::FinalBoss(EngineContext &context, const std::string &texturePath)
    : BaseCharacter(),

      hp(FinalBossEnemyStats::HP),

      speed(FinalBossEnemyStats::Speed),
      finalBossTexture(),               // Default construct texture first
      finalBossSprite(finalBossTexture) // Construct sprite WITH the texture (even if not loaded yet)

{
    finalBossTexture.loadFromFile(texturePath);   // Now actually load the image file
    finalBossSprite.setTexture(finalBossTexture); // Attach the fully loaded texture just in case

    if (!finalBossTexture.loadFromFile(texturePath))
    {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }
    finalBossSprite.setTexture(finalBossTexture);
}

void FinalBoss::Draw(sf::RenderWindow &window)
{
    window.draw(finalBossSprite);
}

void FinalBoss::WallCollisionDetection(const sf::RectangleShape &playerHitBox,
                                       float leftWall, float rightWall, float ceiling, float floor)
{
    float halfWidth = playerHitBox.getSize().x / 2.f;
    float halfHeight = playerHitBox.getSize().y / 2.f;

    sf::Vector2f pos = finalBossSprite.getPosition();
    pos.x = std::max(leftWall + halfWidth, std::min(rightWall - halfWidth, pos.x));

    if (pos.y >= floor - halfHeight)
    {
        pos.y = floor - halfHeight;
        velocityY = 0.f;
        onGround = true;
    }
    if (pos.y <= ceiling + halfHeight)
    {
        pos.y = ceiling + halfHeight;
        velocityY = 0.f;
    }

    finalBossSprite.setPosition(pos);
}

void FinalBoss::initChar()
{
    finalBossSprite.setTexture(finalBossTexture);

    const auto texSize = finalBossTexture.getSize();
    finalBossSprite.setOrigin({texSize.x / 2.f, texSize.y / 2.f}); // center origin

    finalBossSprite.setPosition({500.f, 500.f});
    finalBossSprite.setScale({1.0f, 1.0f}); // much smaller for a 3k image
    finalBossSprite.setColor(sf::Color::White);

    FinalBossHitBox.setSize({64.f, 96.f});
    FinalBossHitBox.setOrigin(FinalBossHitBox.getSize() / 2.f);
    FinalBossHitBox.setPosition({500.f, 500.f}); // spawn position

    FinalBossHitBox.setFillColor(sf::Color(0, 0, 0, 0)); // fully transparent fill
    FinalBossHitBox.setOutlineColor(sf::Color::Green);   // border color
    FinalBossHitBox.setOutlineThickness(2.f);
}

void FinalBoss::ApplyDamage(float amount)
{
}
void FinalBoss::Attack(BaseCharacter &target)
{
}

void FinalBoss::Update(float dt)
{
}
void FinalBoss::applyGravity(float gravity, float dt)
{
    velocityY += gravity * dt;
    finalBossSprite.move({0.f, velocityY * dt});
}

void FinalBoss::setHitBoxToSprite()
{
    FinalBossHitBox.setPosition(finalBossSprite.getPosition());
}

void FinalBoss::EnemyAction(float dt,
                            float moveSpeed,
                            float gravity,
                            sf::RectangleShape &hitbox,
                            float leftWall, float rightWall, float ceiling, float floor)
{
    handleMovement(dt, moveSpeed);
    handleJump();
    applyGravity(gravity, dt);
    WallCollisionDetection(FinalBossHitBox, leftWall, rightWall, ceiling, floor);
}

void FinalBoss::handleJump()
{ /*
     if (onGround)
     {
         velocityY = -400.f;
         onGround = false;
     }
         */
}
void FinalBoss::handleMovement(float dt, float moveSpeed)
{
    sf::Vector2f move(0.f, 0.f);

    finalBossSprite.move(move);
}
void FinalBoss::WallCollisionDetection(sf::RectangleShape &hitbox,
                                       float leftWall, float rightWall, float ceiling, float floor)

{
    float halfWidth = FinalBossHitBox.getSize().x / 2.f;
    float halfHeight = FinalBossHitBox.getSize().y / 2.f;

    sf::Vector2f pos = finalBossSprite.getPosition();
    pos.x = std::max(leftWall + halfWidth, std::min(rightWall - halfWidth, pos.x));

    if (pos.y >= floor - halfHeight)
    {
        pos.y = floor - halfHeight;
        velocityY = 0.f;
        onGround = true;
    }
    if (pos.y <= ceiling + halfHeight)
    {
        pos.y = ceiling + halfHeight;
        velocityY = 0.f;
    }

    finalBossSprite.setPosition(pos);
}

const sf::RectangleShape &FinalBoss::getHitBox() const
{
    return FinalBossHitBox;
}

sf::RectangleShape &FinalBoss::getHitBox()
{
    return FinalBossHitBox;
}

const sf::Sprite &FinalBoss::getSprite() const
{
    return finalBossSprite;
}
