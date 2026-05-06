#pragma once

#include <string>

#include "CharacterManager/Managers/Config/PlayerStatsConfig.h"

class PlayerStats
{
    std::string name;
    int hp;
    float gravity;
    int speed;

public:
    PlayerStats(int hp = PlayerStatsConfig::HP,
                float gravity = PlayerStatsConfig::Gravity,
                int speed = PlayerStatsConfig::Speed);

    int getHP();
    int getGravity();
    void setHP(int newHP);
};