#include "BaseCharacter.h"
#include <algorithm>
#include <cmath>
#include "Core/EngineConfig.h"
#include <iostream>

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
    float allowCrossUpPush = 10.0f;

    const float arenaLeft = 0.0f;
    const float arenaRight = gConfig.windowSize.x;
    const float epsilon = 0.01f;
    const float wallBuffer = 50.0f;
    const float yOverlapThreshold = 8.0f; // Y overlap in pixels required to push

    // Helper: get rectangle properties for both
    auto getBox = [](BaseCharacter &c, float &left, float &right, float &top, float &bottom, float &centerX, float &centerY, float &halfW, float &halfH)
    {
        auto pos = c.getHitBox().getPosition();
        auto size = c.getHitBox().getSize();
        halfW = size.x * 0.5f;
        halfH = size.y * 0.5f;
        left = pos.x - halfW;
        right = pos.x + halfW;
        top = pos.y - halfH;
        bottom = pos.y + halfH;
        centerX = pos.x;
        centerY = pos.y;
    };

    float pLeft, pRight, pTop, pBottom, pCenterX, pCenterY, pHalfW, pHalfH;
    float eLeft, eRight, eTop, eBottom, eCenterX, eCenterY, eHalfW, eHalfH;

    getBox(player, pLeft, pRight, pTop, pBottom, pCenterX, pCenterY, pHalfW, pHalfH);
    getBox(enemy, eLeft, eRight, eTop, eBottom, eCenterX, eCenterY, eHalfW, eHalfH);

    // 1. Clamp to arena boundaries (no passing the walls)
    if (pLeft < arenaLeft + wallBuffer)
        player.getHitBox().setPosition({arenaLeft + wallBuffer + pHalfW, pCenterY});
    if (pRight > arenaRight - wallBuffer)
        player.getHitBox().setPosition({arenaRight - wallBuffer - pHalfW, pCenterY});
    if (eLeft < arenaLeft + wallBuffer)
        enemy.getHitBox().setPosition({arenaLeft + wallBuffer + eHalfW, eCenterY});
    if (eRight > arenaRight - wallBuffer)
        enemy.getHitBox().setPosition({arenaRight - wallBuffer - eHalfW, eCenterY});

    // Refresh after wall snaps
    getBox(player, pLeft, pRight, pTop, pBottom, pCenterX, pCenterY, pHalfW, pHalfH);
    getBox(enemy, eLeft, eRight, eTop, eBottom, eCenterX, eCenterY, eHalfW, eHalfH);

    // --- Special: push grounded character away from LEFT wall if other is 10+ px above ---
    float gLeft, gRight, gTop, gBottom, gCenterX, gCenterY, gHalfW, gHalfH;
    float oLeft, oRight, oTop, oBottom, oCenterX, oCenterY, oHalfW, oHalfH;

    // Case 1: Player is grounded at left wall, enemy is above them
    getBox(player, gLeft, gRight, gTop, gBottom, gCenterX, gCenterY, gHalfW, gHalfH);
    getBox(enemy, oLeft, oRight, oTop, oBottom, oCenterX, oCenterY, oHalfW, oHalfH);

    bool playerGroundedAtLeftWall = player.isGrounded() && (std::abs(gLeft - (arenaLeft + wallBuffer)) < 4.f);
    bool enemyAbovePlayer = (oBottom < gTop - 10.0f);

    if (playerGroundedAtLeftWall && enemyAbovePlayer)
    {
        player.getHitBox().move({-allowCrossUpPush, 0.f}); // Drastic push right
        std::cout << "PLAYER PUSHED FROM LEFT WALL!\n";
    }

    // Case 2: Enemy is grounded at left wall, player is above them
    getBox(enemy, gLeft, gRight, gTop, gBottom, gCenterX, gCenterY, gHalfW, gHalfH);
    getBox(player, oLeft, oRight, oTop, oBottom, oCenterX, oCenterY, oHalfW, oHalfH);

    bool enemyGroundedAtLeftWall = enemy.isGrounded() && (std::abs(gLeft - (arenaLeft + wallBuffer)) < 4.f);
    bool playerAboveEnemy = (oBottom < gTop - 10.0f);

    if (enemyGroundedAtLeftWall && playerAboveEnemy)
    {
        enemy.getHitBox().move({allowCrossUpPush, 0.f}); // Drastic push right
        std::cout << "ENEMY PUSHED FROM LEFT WALL!\n";
    }

    // --- Special: push grounded character away from RIGHT wall if other is 10+ px above ---

    // Case 1: Player is grounded at right wall, enemy is above them
    getBox(player, gLeft, gRight, gTop, gBottom, gCenterX, gCenterY, gHalfW, gHalfH);
    getBox(enemy, oLeft, oRight, oTop, oBottom, oCenterX, oCenterY, oHalfW, oHalfH);

    bool playerGroundedAtRightWall = player.isGrounded() && (std::abs(gRight - (arenaRight - wallBuffer)) < 4.f);
    bool enemyAbovePlayerRight = (oBottom < gTop - 10.0f);

    if (playerGroundedAtRightWall && enemyAbovePlayerRight)
    {
        player.getHitBox().move({-allowCrossUpPush, 0.f}); // Drastic push left
        std::cout << "PLAYER PUSHED FROM RIGHT WALL!\n";
    }

    // Case 2: Enemy is grounded at right wall, player is above them
    getBox(enemy, gLeft, gRight, gTop, gBottom, gCenterX, gCenterY, gHalfW, gHalfH);
    getBox(player, oLeft, oRight, oTop, oBottom, oCenterX, oCenterY, oHalfW, oHalfH);

    bool enemyGroundedAtRightWall = enemy.isGrounded() && (std::abs(gRight - (arenaRight - wallBuffer)) < 4.f);
    bool playerAboveEnemyRight = (oBottom < gTop - 10.0f);

    if (enemyGroundedAtRightWall && playerAboveEnemyRight)
    {
        enemy.getHitBox().move({-allowCrossUpPush, 0.f}); // Drastic push left
        std::cout << "ENEMY PUSHED FROM RIGHT WALL!\n";
    }

    // --- Special: push grounded character away from wall if other is 10+ px above ---

    // Assumption: You have an isGrounded() method for your characters.
    // For left and right wall

    // Re-sync positions in case they were moved
    getBox(player, pLeft, pRight, pTop, pBottom, pCenterX, pCenterY, pHalfW, pHalfH);
    getBox(enemy, eLeft, eRight, eTop, eBottom, eCenterX, eCenterY, eHalfW, eHalfH);

    float yOverlapAmount = std::min(pBottom, eBottom) - std::max(pTop, eTop);
    bool ySignificantOverlap = yOverlapAmount > yOverlapThreshold;
    bool xOverlap = (pRight > eLeft + epsilon) && (pLeft < eRight - epsilon);

    // --- Vertical (Landing On Head) Split, only if significant Y overlap ---
    if (ySignificantOverlap && xOverlap)
    {
        // Headstomp rule: determine who is on top
        bool playerAbove = pTop < eTop;
        BaseCharacter *top = playerAbove ? &player : &enemy;
        BaseCharacter *bottom = playerAbove ? &enemy : &player;

        float topLeft, topRight, topTop, topBottom, topCenterX, topCenterY, topHalfW, topHalfH;
        float bottomLeft, bottomRight, bottomTop, bottomBottom, bottomCenterX, bottomCenterY, bottomHalfW, bottomHalfH;
        getBox(*top, topLeft, topRight, topTop, topBottom, topCenterX, topCenterY, topHalfW, topHalfH);
        getBox(*bottom, bottomLeft, bottomRight, bottomTop, bottomBottom, bottomCenterX, bottomCenterY, bottomHalfW, bottomHalfH);

        float landingX = topCenterX - bottomLeft;
        float bottomW = bottomRight - bottomLeft;

        // Split by landing "pixel" (right/left band)
        if (landingX >= 1.f && landingX <= 5.f)
        {
            top->getHitBox().setPosition({bottomLeft - topHalfW - epsilon, top->getHitBox().getPosition().y});
        }
        else if (landingX >= (bottomW - 10.f) && landingX <= (bottomW - 6.f))
        {
            top->getHitBox().setPosition({bottomRight + topHalfW + epsilon, top->getHitBox().getPosition().y});
        }
    }

    // --- Corner Crossup: only if both in right corner, full X overlap, Y overlap ---
    getBox(player, pLeft, pRight, pTop, pBottom, pCenterX, pCenterY, pHalfW, pHalfH);
    getBox(enemy, eLeft, eRight, eTop, eBottom, eCenterX, eCenterY, eHalfW, eHalfH);

    float yOverlapAmount2 = std::min(pBottom, eBottom) - std::max(pTop, eTop);
    bool ySignificantOverlap2 = yOverlapAmount2 > yOverlapThreshold;
    bool xOverlapNow = (pRight > eLeft + epsilon) && (pLeft < eRight - epsilon);

    float rightCornerThreshold = arenaRight - wallBuffer - std::max(pHalfW, eHalfW);
    bool bothInRightCorner = (pRight >= rightCornerThreshold - epsilon && eRight >= rightCornerThreshold - epsilon);
    bool perfectXOverlap = std::abs(pCenterX - eCenterX) < epsilon;

    if (bothInRightCorner && perfectXOverlap && ySignificantOverlap2)
    {
        bool playerAbove = pTop < eTop;
        BaseCharacter *bottom = playerAbove ? &enemy : &player;
        float minStage = arenaRight - wallBuffer - bottom->getHitBox().getSize().x * 0.5f - epsilon;
        bottom->getHitBox().setPosition({minStage, bottom->getHitBox().getPosition().y});
    }

    // --- Final: Standard X anti-overlap, only if significant Y overlap (prevents push-on-jump) ---
    getBox(player, pLeft, pRight, pTop, pBottom, pCenterX, pCenterY, pHalfW, pHalfH);
    getBox(enemy, eLeft, eRight, eTop, eBottom, eCenterX, eCenterY, eHalfW, eHalfH);

    float lastYOverlapAmount = std::min(pBottom, eBottom) - std::max(pTop, eTop);
    bool doXPush = lastYOverlapAmount > yOverlapThreshold;
    bool finalXOverlap = (pRight > eLeft + epsilon) && (pLeft < eRight - epsilon);

    if (finalXOverlap && doXPush)
    {
        float overlap = std::min(pRight, eRight) - std::max(pLeft, eLeft) + epsilon;
        float push = overlap * 0.5f + epsilon;
        if (pCenterX < eCenterX)
        {
            player.getHitBox().move({-push, 0.f});
            enemy.getHitBox().move({push, 0.f});
        }
        else
        {
            player.getHitBox().move({push, 0.f});
            enemy.getHitBox().move({-push, 0.f});
        }
    }

    // Sync sprites
    player.getSprite().setPosition(player.getHitBox().getPosition());
    enemy.getSprite().setPosition(enemy.getHitBox().getPosition());
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