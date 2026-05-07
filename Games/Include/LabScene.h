#pragma once
#include "Scene/Scene.h"
#include "CharacterManager/PlayerCharacter.h"
#include "CharacterManager/Managers/Config/PlayerStatsConfig.h"

namespace LabScene
{

    class Lab : public Scene
    {
    private:
        PlayerCharacter player;
        sf::RectangleShape playerHitBox;

        sf::Sprite background;

    public:
        Lab(EngineContext &);

        void InitChar();

        void Start();
        void Update();
        void Render() const;
        void OnPause(bool);
        void OnCleanup();
    };

};