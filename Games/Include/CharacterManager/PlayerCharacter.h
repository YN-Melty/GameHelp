#pragma once

#include "CharacterManager/Managers/PlayerStats.h"
#include "CharacterManager/Managers/PlayerTextures.h"
#include "CharacterManager/Managers/Config/PlayerStatsConfig.h"

class PlayerCharacter
{
    PlayerStats playerStats;
    PlayerTextures playerTexture;
    PlayerCharacter() : playerStats(), playerTexture(PlayerStatsConfig::PlayerTexture) {}
};