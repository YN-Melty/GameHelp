#include "CharacterManager/PlayerCharacter.h"
#include "CharacterManager/Managers/Config/PlayerStatsConfig.h"

PlayerCharacter::PlayerCharacter()
    : playerStats(),
      playerTexture(PlayerStatsConfig::PlayerTexture)
{
    sprite.setTexture(playerTexture.texture);
    // sprite.setPosition(...); // optional
}