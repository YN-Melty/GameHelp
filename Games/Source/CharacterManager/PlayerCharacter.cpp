#include "CharacterManager/PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(EngineContext &context)
    : playerStats(),
      playerTexture(PlayerStatsConfig::PlayerTexture),
      sprite(playerTexture.texture)
{
    sprite.setTexture(playerTexture.texture);
    // sprite.setPosition(...); // optional
}

void PlayerCharacter::pcAction()
{
    sf::Vector2f move(0.f, 0.f);
    if (ctx.input.Pressed(ACTION_MOVE_LEFT))
        move.x -= moveSpeed * dt;
    if (ctx.input.Pressed(ACTION_MOVE_RIGHT))
        move.x += moveSpeed * dt;

    // Jump
    if (ctx.input.Pressed(ACTION_JUMP) && onGround)
    {
        velocityY = -400.f;
        onGround = false;
    }

    // Apply gravity
    velocityY += gravity * dt;
    move.y += velocityY * dt;

    // Move
    player.sprite.move(move);
    playerHitBox.move(move);

    // Clamp X (walls)
    sf::Vector2f pos = player.sprite.getPosition();
    pos.x = std::max(LEFT_WALL + halfWidth, std::min(RIGHT_WALL - halfWidth, pos.x));

    // Clamp Y (floor/ceiling)
    if (pos.y >= FLOOR - halfHeight)
    {
        pos.y = FLOOR - halfHeight;
        velocityY = 0.f;
        onGround = true;
    }
    if (pos.y <= CEILING + halfHeight)
    {
        pos.y = CEILING + halfHeight;
        velocityY = 0.f;
    }

    player.sprite.setPosition(pos);
    playerHitBox.setPosition(pos);
}