#include "BaseCharacter.h"

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