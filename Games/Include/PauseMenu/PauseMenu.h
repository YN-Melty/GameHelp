#pragma once

#include "Core/EngineContext.h"
#include <TGUI/TGUI.hpp>
#include "Managers/GuiManager.h"
#include <optional>
#include "InputActions.h"

enum class PauseMenuSelection
{
    Resume,
    Restart,
    Menu,
    Quit
};

class PauseMenu
{
    bool visible_ = false;

public:
    PauseMenu() = default;

    void Init(GuiManager &gui);

    std::optional<PauseMenuSelection> FetchSelection();
    void SetVisible(bool visible);
    bool IsVisible() const;

private:
    tgui::Group::Ptr group_;
    std::optional<PauseMenuSelection> selection_{std::nullopt};

    void InitBackground();
    void InitButtons();
};
// global function to handle pause
bool HandlePauseAction(EngineContext &ctx, PauseMenu &pauseMenu);