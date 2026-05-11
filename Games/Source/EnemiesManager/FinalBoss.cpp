#include "EnemiesManager/FinalBoss.h"

FinalBoss::FinalBoss(EngineContext &context, const std::string &texturePath)
    : BaseCharacter(),
      Scene(context),
      hp(FinalBossEnemyStats::HP),
      gravity(FinalBossEnemyStats::Gravity),
      speed(FinalBossEnemyStats::Speed),
      finalBossTexture(),               // Default construct texture first
      finalBossSprite(finalBossTexture) // Construct sprite WITH the texture (even if not loaded yet)

{
    finalBossTexture.loadFromFile(texturePath);   // Now actually load the image file
    finalBossSprite.setTexture(finalBossTexture); // Attach the fully loaded texture just in case
}