#pragma once

#include <string>
#include <unordered_map>

struct InputActionState
{
    bool down = false;
    bool pressed = false;
    bool released = false;

    float value = 0.f;
};

struct InputResource
{
    std::unordered_map<std::string, InputActionState> actions;

    bool IsDown(const std::string& action) const
    {
        auto it = actions.find(action);
        return it != actions.end() && it->second.down;
    }

    bool IsPressed(const std::string& action) const
    {
        auto it = actions.find(action);
        return it != actions.end() && it->second.pressed;
    }

    bool IsReleased(const std::string& action) const
    {
        auto it = actions.find(action);
        return it != actions.end() && it->second.released;
    }

    float GetValue(const std::string& action) const
    {
        auto it = actions.find(action);
        return it != actions.end()
            ? it->second.value
            : 0.f;
    }
};