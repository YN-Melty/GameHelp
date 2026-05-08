#pragma once

#include <string>

#include "CharacterManager/Managers/Config/PlayerStatsConfig.h"

class PlayerStats
{
    std::string name;
    int hp;
    float gravity;
    int speed;
    const float velocityY;
    static bool onGround;
    const float gravity;

public:
    PlayerStats(int hp = PlayerStatsConfig::HP,
                const float gravity = PlayerStatsConfig::Gravity,
                int speed = PlayerStatsConfig::Speed,
                const float velocityY = 0.f);

    int getHP();
    int getGravity();
    void setHP(int newHP);
};