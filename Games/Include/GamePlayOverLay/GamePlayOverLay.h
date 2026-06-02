#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include "BaseCharacter.h"
#include "Scene/Scene.h"

namespace GamePlayOverLayStuff
{
    class GamePlayOverLay : public Scene
    {
    public:
        GamePlayOverLay(EngineContext &);

        sf::RectangleShape player1HPBar;
        sf::RectangleShape player2HPBar;

        sf::RectangleShape player1Meter;
        sf::RectangleShape player2Meter;

        void DrawHPBars(BaseCharacter &Player, BaseCharacter &Enemy);
        void updateHPBars(BaseCharacter &Player, BaseCharacter &Enemy);

        void DrawMeterBars(BaseCharacter &Player, BaseCharacter &Enemy);
        void updateMeterBars(BaseCharacter &Player, BaseCharacter &Enemy);
    };
};