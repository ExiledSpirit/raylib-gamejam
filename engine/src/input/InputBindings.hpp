#pragma once

#include <raylib.h>

#include <string>
#include <unordered_map>
#include <vector>

struct TouchBinding
{
    bool anyScreenTouch = true;

    // Used only when anyScreenTouch == false.
    // Coordinates should be game internal resolution, for Toy Out it is 640x360.
    Rectangle area{0.0f, 0.0f, 0.0f, 0.0f};
};

struct InputBindings
{
    std::unordered_map<std::string, std::vector<KeyboardKey>> keyboard;
    std::unordered_map<std::string, std::vector<GamepadButton>> gamepadButtons;
    std::unordered_map<std::string, std::vector<TouchBinding>> touch;

    void BindKeyboard(const std::string& action, KeyboardKey key)
    {
        keyboard[action].push_back(key);
    }

    void BindGamepadButton(const std::string& action, GamepadButton button)
    {
        gamepadButtons[action].push_back(button);
    }

    void BindTouchAnywhere(const std::string& action)
    {
        touch[action].push_back(
            TouchBinding{
                true,
                Rectangle{0.0f, 0.0f, 0.0f, 0.0f}
            }
        );
    }

    void BindTouchArea(const std::string& action, Rectangle area)
    {
        touch[action].push_back(
            TouchBinding{
                false,
                area
            }
        );
    }
};

