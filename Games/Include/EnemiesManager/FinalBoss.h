#pragma once
#include "Scene/Scene.h"
#include "EnemiesManager/FinalBossEnemyStats.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>

class FinalBoss : public Scene
{
public:
    FinalBoss(EngineContext &context, const std::string &texturePath = FinalBossEnemyStats::FinalBossTexture);

private:
    int hp;
    float gravity;
    int speed;

    sf::Texture finalBossTexture;
    sf::Sprite finalBossSprite;
};