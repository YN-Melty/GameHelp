#pragma once

#include <TGUI/TGUI.hpp>
#include "Managers/GuiManager.h"
#include <optional>

enum class PauseMenuSelection
{
    Resume,
    Restart,
    Menu,
    Quit
};

class PauseMenu
{
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