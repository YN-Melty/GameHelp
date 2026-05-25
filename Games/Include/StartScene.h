#pragma once
#include "Scene/Scene.h"

namespace StartMenu
{

    class StartScreen : public Scene
    {
    private:
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;

        static constexpr const char *menuStartPath = "Content/Textures/StartMenu/startMenuBackground.png";

        sf::Texture startButtonTexture;
        sf::Sprite startButtonSprite;
        static constexpr const char *startButtonPath = "Content/Textures/StartMenu/startButton.png";
        static constexpr const char *startButtonPressed = "Content/Textures/StartMenu/startButtonPressed.png";

    public:
        StartScreen(EngineContext &);

        void InitBackground();
        void StartGame();
        void Update();
        void Render() const;
        void OnPause(bool);
    };

};