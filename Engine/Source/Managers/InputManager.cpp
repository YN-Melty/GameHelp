#include "Managers/InputManager.h"
#include <algorithm>

void InputManager::Bind(int action, const Input::Binding &binding)
{
    bindings_.emplace(action, binding);
}
bool InputManager::Pressed(int action) const
{
    const auto [first, last] = bindings_.equal_range(action);

    return std::any_of(first, last, [this](const auto &entry)
                       { return std::visit([this](const auto &binding)
                                           { return this->Pressed(binding); }, entry.second); });
}
void InputManager::Clear()
{
    bindings_.clear();
}

bool InputManager::Pressed(const Input::Keyboard &binding) const
{
    return sf::Keyboard::isKeyPressed(binding.key);
}
bool InputManager::Pressed(const Input::Mouse &binding) const
{
    return sf::Mouse::isButtonPressed(binding.button);
}
bool InputManager::Pressed(const Input::Gamepad &binding) const
{
    const auto button = Input::LogicalToHardware(binding.button, binding.id);
    return button ? sf::Joystick::isButtonPressed(binding.id, *button) : false;
}
const bool InputManager::Pressed(const Input::Axis &binding) const
{
    const float axis = sf::Joystick::getAxisPosition(binding.id, binding.axis) / 100;
    return (binding.threshold >= 0) ? axis > binding.threshold : axis < binding.threshold;
}

void InputManager::UpdateStates()
{
    previousStates_ = currentStates_;
    for (const auto &entry : bindings_)
    {
        int action = entry.first;
        currentStates_[action] = Pressed(action);
    }
}

bool InputManager::JustPressed(int action) const
{
    auto curr = currentStates_.find(action);
    auto prev = previousStates_.find(action);
    return curr != currentStates_.end() && curr->second &&
           (prev == previousStates_.end() || !prev->second);
}