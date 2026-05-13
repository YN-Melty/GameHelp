#include "CharacterManager/Managers/PlayerStats.h"
#include "CharacterManager/Managers/Config/PlayerStatsConfig.h"

PlayerStats::PlayerStats(int hp, int speed)
    : hp(hp), speed(speed)
{
    // You can initialize 'name' here if you want, like:
    // name = "Default";
}

int PlayerStats::getHP()
{
    return hp;
}

void PlayerStats::setHP(int newHP)
{
    hp = newHP;
}

int PlayerStats::getSpeed() { return speed; }