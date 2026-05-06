#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Managers/RandomManager.h"
#include "Managers/TimeManager.h"
#include "Managers/SaveManager.h"
#include "Managers/ClipboardManager.h"
#include "Managers/ResourceManager.h"
#include "Managers/AudioManager.h"
#include "Managers/InputManager.h"
#include "Managers/RenderManager.h"
#include "Managers/ScreenshotManager.h"
#include "Managers/CursorManager.h"
#include "Managers/GuiManager.h"
#include "Managers/SceneManager.h"

struct EngineContext
{
    RandomManager random;
    TimeManager time;
    SaveManager save;
    ClipboardManager clipboard;
    ResourceManager resources;
    AudioManager audio;
    InputManager input;
    RenderManager renderer;
    ScreenshotManager screenshot;
    CursorManager cursor;
    GuiManager gui;
    SceneManager scenes;

    EngineContext(sf::RenderWindow &window) : screenshot(window), cursor(window), gui(window) {}
};