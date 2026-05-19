#include "BaseCharacter.h"
#include <algorithm>
#include <cmath>
#include "Core/EngineConfig.h"

bool BaseCharacter::isHitboxOverlapping(const sf::RectangleShape &a, const sf::RectangleShape &b)
{
    sf::Vector2f aPos = a.getPosition();
    sf::Vector2f aHalf = a.getSize() / 2.f;
    float aLeft = aPos.x - aHalf.x;
    float aRight = aPos.x + aHalf.x;
    float aTop = aPos.y - aHalf.y;
    float aBottom = aPos.y + aHalf.y;

    sf::Vector2f bPos = b.getPosition();
    sf::Vector2f bHalf = b.getSize() / 2.f;
    float bLeft = bPos.x - bHalf.x;
    float bRight = bPos.x + bHalf.x;
    float bTop = bPos.y - bHalf.y;
    float bBottom = bPos.y + bHalf.y;

    bool xOverlap = (aRight > bLeft) && (aLeft < bRight);
    bool yOverlap = (aBottom > bTop) && (aTop < bBottom);

    return xOverlap && yOverlap;
}

void BaseCharacter::fightersAntiCollision(BaseCharacter &player, BaseCharacter &enemy)
{
    const float epsilon = 0.01f;

    auto &playerBox = player.getHitBox();
    auto &enemyBox = enemy.getHitBox();
    sf::Vector2f playerCenter = playerBox.getPosition();
    sf::Vector2f enemyCenter = enemyBox.getPosition();

    float playerHalfWidth = playerBox.getSize().x / 2.0f;
    float enemyHalfWidth = enemyBox.getSize().x / 2.0f;
    float playerHalfHeight = playerBox.getSize().y / 2.0f;
    float enemyHalfHeight = enemyBox.getSize().y / 2.0f;

    bool overlap = isHitboxOverlapping(playerBox, enemyBox);

    float leftWall = enemyHalfWidth;
    float arenaRight = gConfig.windowSize.x;

    bool playerAbove = (playerCenter.y + playerHalfHeight - epsilon <= enemyCenter.y - enemyHalfHeight);

    float relX = playerCenter.x - enemyCenter.x;

    auto canEnemyMoveRight = [&]() -> bool
    {
        float rightWall = gConfig.windowSize.x - enemyHalfWidth;
        return enemyCenter.x + epsilon < rightWall;
    };

    bool enemyPinnedLeft = (enemyCenter.x - enemyHalfWidth - epsilon <= 0.f);

    if (overlap)
    {
        if (playerAbove && enemyPinnedLeft)
        {
            // --- SPECIAL CASE: Player attempts crossup, enemy is pinned ---

            if (relX <= 0.f)
            {
                // Player wants to crossup by landing on left half but enemy can't move
                // So, "break open the corner": move both right just enough so player is on left, enemy is on right, still touching

                float minPlayerX = leftWall;
                float minEnemyX = minPlayerX + playerHalfWidth + enemyHalfWidth + epsilon;

                player.getSprite().setPosition({minPlayerX, player.getSprite().getPosition().y});
                player.getHitBox().setPosition({minPlayerX, player.getHitBox().getPosition().y});
                enemy.getSprite().setPosition({minEnemyX, enemy.getSprite().getPosition().y});
                enemy.getHitBox().setPosition({minEnemyX, enemy.getHitBox().getPosition().y});
            }
            else
            {
                // Player lands on the right half: push player in front (right) of enemy
                float targetPlayerX = enemyCenter.x + enemyHalfWidth + playerHalfWidth + epsilon;
                float rightWallLimit = arenaRight - playerHalfWidth;
                targetPlayerX = std::min(targetPlayerX, rightWallLimit);
                player.getSprite().setPosition({targetPlayerX, player.getSprite().getPosition().y});
                player.getHitBox().setPosition({targetPlayerX, player.getHitBox().getPosition().y});
            }
            // End special pin logic
        }
        else if (playerAbove)
        {
            // Standard "landing on top/crossup" logic for center stage (enemy is not pinned)
            if (relX <= 0.f && canEnemyMoveRight())
            {
                // Move enemy right to make space for crossup
                float targetEnemyX = playerCenter.x + enemyHalfWidth + playerHalfWidth + epsilon;
                float rightWall = arenaRight - enemyHalfWidth;
                targetEnemyX = std::min(targetEnemyX, rightWall);
                enemy.getSprite().setPosition({targetEnemyX, enemy.getSprite().getPosition().y});
                enemy.getHitBox().setPosition({targetEnemyX, enemy.getHitBox().getPosition().y});
            }
            else if (relX > 0.f && !canEnemyMoveRight())
            {
                // Enemy is right-pinned and can't move; push player to the front (applies for right-corner symmetry)
                float targetPlayerX = enemyCenter.x + enemyHalfWidth + playerHalfWidth + epsilon;
                float rightWallLimit = arenaRight - playerHalfWidth;
                targetPlayerX = std::min(targetPlayerX, rightWallLimit);
                player.getSprite().setPosition({targetPlayerX, player.getSprite().getPosition().y});
                player.getHitBox().setPosition({targetPlayerX, player.getHitBox().getPosition().y});
            }
            // Else: nothing, physics will resolve side-landing
        }
        else
        {
            // --- STANDARD SIDE-BY-SIDE RESOLUTION (no stacking/floating allowed) ---
            float separation = (playerHalfWidth + enemyHalfWidth) - std::abs(relX);
            if (separation > 0.f)
            {
                float push = separation / 2.f + epsilon;
                if (relX < 0)
                {
                    // player is left; move player left, enemy right
                    player.getSprite().move({-push, 0});
                    player.getHitBox().move({-push, 0});
                    enemy.getSprite().move({push, 0});
                    enemy.getHitBox().move({push, 0});
                }
                else
                {
                    // player is right of enemy; move player right, enemy left
                    player.getSprite().move({push, 0});
                    player.getHitBox().move({push, 0});
                    enemy.getSprite().move({-push, 0});
                    enemy.getHitBox().move({-push, 0});
                }
            }
        }
    }
    // No overlap: no correction needed
}

sf::Time BaseCharacter::restartTimer()
{
    return collisionTimer.restart();
}
sf::Time BaseCharacter::getTime() const
{
    return collisionTimer.getElapsedTime();
}

void BaseCharacter::isTouchingTrue()
{
    isTouching = true;
}

void BaseCharacter::isTouchingFalse()
{
    isTouching = false;
}