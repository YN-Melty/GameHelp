#include "CharacterManager/PlayerCharacter.h"

PlayerCharacter::PlayerCharacter()
    : playerStats(),
      playerTexture(PlayerStatsConfig::PlayerTexture),
      sprite(playerTexture.texture)
{
    sprite.setTexture(playerTexture.texture);
    // sprite.setPosition(...); // optional
}