#pragma once
#include "Scene/Scene.h"
#include "CharacterManager/PlayerCharacter.h"

namespace LabScene
{

    class Lab : public Scene
    {
    private:
        PlayerCharacter player;
        sf::RectangleShape playerHitBox;

        sf::RectangleShape background;

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