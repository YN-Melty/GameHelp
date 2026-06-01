#pragma once
#include "CharacterManager/PlayerCharacter.h"
#include "EnemiesManager/FinalBoss.h"
#include "PauseMenu/PauseMenu.h"

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
        float crossupTimer;

        PauseMenu pauseMenu;

    public:
        Lab(EngineContext &);

        void InitChar();
        void InitBackground();

        void Start() override;
        void Update() override;
        void Render() const override;
        void OnPause(bool);
        void OnCleanup();
    };

};