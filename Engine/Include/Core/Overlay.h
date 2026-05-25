#pragma once

#include <TGUI/TGUI.hpp>
#include "Managers/GuiManager.h"
#include <optional>

enum class OverlaySelection
{
    Resume,
    Restart,
    Menu,
    Quit
};

class Overlay
{
public:
    Overlay() = default; // Now a trivial constructor, does NOT create widgets

    // This method actually sets up the TGUI widgets.
    void Init(GuiManager &gui);

    std::optional<OverlaySelection> FetchSelection();
    void SetVisible(bool visible);
    bool IsVisible() const;

private:
    tgui::Group::Ptr group_;
    std::optional<OverlaySelection> selection_{std::nullopt};

    void InitBackground();
    void InitButtons();
};