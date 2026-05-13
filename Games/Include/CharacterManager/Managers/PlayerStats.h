#pragma once

#include <string>

#include "CharacterManager/Managers/Config/PlayerStatsConfig.h"

class PlayerStats
{
    std::string name;
    int hp;
    int speed;

public:
    PlayerStats(int hp = PlayerStatsConfig::HP,
                int speed = PlayerStatsConfig::Speed);

    int getHP();
    int getGravity();
    float getVelocityY();
    void setHP(int newHP);
    int getSpeed();
};