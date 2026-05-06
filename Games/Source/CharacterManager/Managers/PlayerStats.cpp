#include "CharacterManager/Managers/PlayerStats.h"
#include "CharacterManager/Managers/Config/PlayerStatsConfig.h"

PlayerStats::PlayerStats(int hp, float gravity, int speed)
    : hp(hp), gravity(gravity), speed(speed)
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