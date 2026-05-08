#include "CharacterManager/Managers/PlayerStats.h"
#include "CharacterManager/Managers/Config/PlayerStatsConfig.h"

PlayerStats::PlayerStats(int hp, float gravity, int speed, const float velocityY)
    : hp(hp), gravity(gravity), speed(speed), velocityY(velocityY)
{
    // You can initialize 'name' here if you want, like:
    // name = "Default";
}

int PlayerStats::getHP()
{
    return hp;
}
int PlayerStats::getGravity()
{
    return gravity;
}

void PlayerStats::setHP(int newHP)
{
    hp = newHP;
}
float PlayerStats::getVelocityY()
{
    return velocityY;
}