#include "CharacterManager/PlayerCharacter.h"
#include "InputActions.h"

PlayerCharacter::PlayerCharacter(EngineContext &context)
    : BaseCharacter(),
      playerStats(),
      playerTexture(PlayerStatsConfig::PlayerTexture),
      sprite(playerTexture.texture)
{
    sprite.setTexture(playerTexture.texture);
}

void PlayerCharacter::ApplyDamage(float amount)
{
    int newHealth = playerStats.getHP() - static_cast<int>(amount);
    if (newHealth < 0)
        newHealth = 0;
    playerStats.setHP(newHealth);
}

void PlayerCharacter::Attack(BaseCharacter &target)
{
    // Use speed as placeholder for attack damage (replace when you have real attack power)
    target.ApplyDamage(1.0f);
}

void PlayerCharacter::Update(float dt)
{
    // Integrate with your framework/game loop
}

void PlayerCharacter::Draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

void PlayerCharacter::pcAction(const InputManager &input, float dt,

                               float gravity,
                               const sf::RectangleShape &playerHitBox,
                               float leftWall, float rightWall, float ceiling, float floor)
{
    handleMovement(input, dt);
    handleJump(input);
    applyGravity(gravity, dt);
    WallCollisionDetection(playerHitBox, leftWall, rightWall, ceiling, floor);
}

void PlayerCharacter::handleMovement(const InputManager &input, float dt)
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
        velocityY = -400.f;
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

void PlayerCharacter::initChar()
{
    sprite.setTexture(playerTexture.texture);

    const auto texSize = playerTexture.texture.getSize();
    sprite.setOrigin({texSize.x / 2.f, texSize.y / 2.f}); // center origin

    sprite.setPosition({200.f, 200.f});
    sprite.setScale({0.05f, 0.05f}); // much smaller for a 3k image
    sprite.setColor(sf::Color::White);

    playerHitBox.setSize({64.f, 96.f});
    playerHitBox.setOrigin(playerHitBox.getSize() / 2.f);
    playerHitBox.setPosition({200.f, 200.f}); // spawn position

    playerHitBox.setFillColor(sf::Color(0, 0, 0, 0)); // fully transparent fill
    playerHitBox.setOutlineColor(sf::Color::Green);   // border color
    playerHitBox.setOutlineThickness(2.f);
}