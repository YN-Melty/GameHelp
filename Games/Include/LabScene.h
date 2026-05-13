#pragma once
#include "Scene/Scene.h"
#include "CharacterManager/PlayerCharacter.h"
#include "EnemiesManager/FinalBoss.h"

namespace LabScene
{

    class Lab : public Scene
    {
    private:
        PlayerCharacter player;
        FinalBoss finalBoss;

        static constexpr const char *BackgroundPath = "Content/Textures/Background.png";
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;

    public:
        Lab(EngineContext &);

        void InitChar();
        void InitBackground();

        void Start();
        void Update();
        void Render() const;
        void OnPause(bool);
        void OnCleanup();
    };

};