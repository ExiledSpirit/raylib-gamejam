#pragma once

#include <raylib.h>

#include <string>
#include <unordered_map>
#include <vector>

struct InputBindings
{
    std::unordered_map<std::string, std::vector<KeyboardKey>> keyboard;
    std::unordered_map<std::string, std::vector<GamepadButton>> gamepadButtons;

    void BindKeyboard(const std::string& action, KeyboardKey key)
    {
        keyboard[action].push_back(key);
    }

    void BindGamepadButton(const std::string& action, GamepadButton button)
    {
        gamepadButtons[action].push_back(button);
    }
};