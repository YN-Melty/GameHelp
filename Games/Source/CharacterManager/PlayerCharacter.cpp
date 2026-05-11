#include "CharacterManager/PlayerCharacter.h"
#include "InputActions.h"

PlayerCharacter::PlayerCharacter(EngineContext &context)
    : BaseCharacter(),
      playerStats(),
      playerTexture(PlayerStatsConfig::PlayerTexture),
      sprite(playerTexture.texture)
{
    sprite.setTexture(playerTexture.texture);
    // sprite.setPosition(...); // optional
}

void PlayerCharacter::pcAction(const InputManager &input, float dt,
                               float moveSpeed,
                               float gravity,
                               const sf::RectangleShape &playerHitBox,
                               float leftWall, float rightWall, float ceiling, float floor)
{
    handleMovement(input, dt, moveSpeed);
    handleJump(input);
    applyGravity(gravity, dt);
    WallCollisionDetection(playerHitBox, leftWall, rightWall, ceiling, floor);
}

void PlayerCharacter::handleMovement(const InputManager &input, float dt, float moveSpeed)
{
    sf::Vector2f move(0.f, 0.f);
    if (input.Pressed(ACTION_MOVE_LEFT))
        move.x -= moveSpeed * dt;
    if (input.Pressed(ACTION_MOVE_RIGHT))
        move.x += moveSpeed * dt;

    sprite.move(move);
}

void PlayerCharacter::handleJump(const InputManager &input)
{
    if (input.Pressed(ACTION_JUMP) && onGround)
    {
        velocityY = -400.f; // Or use a config value
        onGround = false;
    }
}

void PlayerCharacter::applyGravity(float gravity, float dt)
{
    velocityY += gravity * dt;
    sprite.move({0.f, velocityY * dt});
}

void PlayerCharacter::WallCollisionDetection(const sf::RectangleShape &playerHitBox,
                                             float leftWall, float rightWall, float ceiling, float floor)
{
    float halfWidth = playerHitBox.getSize().x / 2.f;
    float halfHeight = playerHitBox.getSize().y / 2.f;

    sf::Vector2f pos = sprite.getPosition();
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

    sprite.setPosition(pos);
}