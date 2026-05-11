#include "CharacterManager/PlayerCharacter.h"
#include "InputActions.h"

PlayerCharacter::PlayerCharacter(EngineContext &context)
    : playerStats(),
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

    float halfWidth = playerHitBox.getSize().x / 2.f;
    float halfHeight = playerHitBox.getSize().y / 2.f;

    sf::Vector2f move(0.f, 0.f);
    if (input.Pressed(ACTION_MOVE_LEFT))
        move.x -= moveSpeed * dt;
    if (input.Pressed(ACTION_MOVE_RIGHT))
        move.x += moveSpeed * dt;

    if (input.Pressed(ACTION_JUMP) && onGround)
    {
        velocityY = -400.f; // Or use a config value
        onGround = false;
    }

    velocityY += gravity * dt;
    move.y += velocityY * dt;

    // --- move both sprite and hitbox ---
    sprite.move(move);
    // If you store hitBox in PlayerCharacter, use hitBox.move(move);
    // Else, let the scene update its playerHitBox

    // --- Clamp X (walls) ---
    sf::Vector2f pos = sprite.getPosition();
    pos.x = std::max(leftWall + halfWidth, std::min(rightWall - halfWidth, pos.x));

    // --- Clamp Y (floor/ceiling) ---
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
    // If you store hitBox in PlayerCharacter, do: hitBox.setPosition(pos);
    // If not, scene must update hitBox to match player position after calling this.
}