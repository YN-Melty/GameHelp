// Overlay.cpp

#include "PauseMenu/PauseMenu.h"
#include <magic_enum/magic_enum.hpp>
#include <utility>

void PauseMenu::Init(GuiManager &gui)
{
    group_ = tgui::Group::create();
    group_->setVisible(false);

    InitBackground();
    InitButtons();

    gui.Add(group_);
}

std::optional<PauseMenuSelection> PauseMenu::FetchSelection()
{
    return std::exchange(selection_, std::nullopt);
}

void PauseMenu::SetVisible(bool visible)
{
    if (group_)
        group_->setVisible(visible);
}

bool PauseMenu::IsVisible() const
{
    return group_ && group_->isVisible();
}

void PauseMenu::InitBackground()
{
    auto background = tgui::Panel::create();
    background->getRenderer()->setBackgroundColor({0, 0, 0, 175});

    group_->add(background);
}

void PauseMenu::InitButtons()
{
    auto layout = tgui::VerticalLayout::create();
    layout->setSize("37%", "18%");
    layout->setPosition("31%", "18%");

    for (const auto &[selection, name] : magic_enum::enum_entries<PauseMenuSelection>())
    {
        auto button = tgui::Button::create(name.data());
        button->setTextSize(30);
        button->onPress([this, selection]
                        { this->selection_ = selection; });

        layout->add(button);
    }
    group_->add(layout);
}

bool HandlePauseAction(EngineContext &ctx, PauseMenu &pauseMenu)
{
    if (ctx.input.JustPressed(ACTION_PAUSE))
    {
        pauseMenu.SetVisible(!pauseMenu.IsVisible());
        ctx.cursor.SetVisible(true);
    }

    if (pauseMenu.IsVisible())
    {
        // handle selection here if desired
        return true; // Let caller know we are paused
    }
    return false; // Not paused, run normal game logic
}