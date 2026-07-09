#include "InputSystem.hpp"

#include "InputBindings.hpp"
#include "InputResource.hpp"

#include <raylib.h>

void InputSystem(World& world)
{
    auto& input =
        world.GetResource<InputResource>();

    auto& bindings =
        world.GetResource<InputBindings>();

    for(auto& [name, state] : input.actions)
    {
        state.down = false;
        state.pressed = false;
        state.released = false;
        state.value = 0.f;
    }

    for(const auto& [action, keys] : bindings.keyboard)
    {
        auto& state =
            input.actions[action];

        for(KeyboardKey key : keys)
        {
            if(key == KEY_NULL)
            {
                continue;
            }

            state.down =
                state.down || IsKeyDown(key);

            state.pressed =
                state.pressed || IsKeyPressed(key);

            state.released =
                state.released || IsKeyReleased(key);
        }
    }

    if(IsGamepadAvailable(0))
    {
        for(const auto& [action, buttons] : bindings.gamepadButtons)
        {
            auto& state =
                input.actions[action];

            for(GamepadButton button : buttons)
            {
                state.down =
                    state.down || IsGamepadButtonDown(0, button);

                state.pressed =
                    state.pressed || IsGamepadButtonPressed(0, button);

                state.released =
                    state.released || IsGamepadButtonReleased(0, button);
            }
        }
    }

    for(auto& [name, state] : input.actions)
    {
        state.value = state.down ? 1.f : 0.f;
    }
}