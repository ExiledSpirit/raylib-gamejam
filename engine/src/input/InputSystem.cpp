#include "InputSystem.hpp"

#include "InputBindings.hpp"
#include "InputResource.hpp"

#include <ecs/resources/DisplayResource.hpp>

#include <raylib.h>

#include <string>
#include <unordered_map>

static bool HasValidViewport(const DisplayResource& display)
{
    return display.scale > 0.0f &&
           display.viewportSize.x > 0.0f &&
           display.viewportSize.y > 0.0f;
}

static bool IsScreenPointInsideViewport(
    Vector2 screenPosition,
    const DisplayResource& display
)
{
    if(!HasValidViewport(display))
    {
        return true;
    }

    return screenPosition.x >= display.viewportOffset.x &&
           screenPosition.y >= display.viewportOffset.y &&
           screenPosition.x <= display.viewportOffset.x + display.viewportSize.x &&
           screenPosition.y <= display.viewportOffset.y + display.viewportSize.y;
}

static Vector2 ScreenToInternalPosition(
    Vector2 screenPosition,
    const DisplayResource& display
)
{
    if(display.scale <= 0.0f)
    {
        return screenPosition;
    }

    return Vector2{
        (screenPosition.x - display.viewportOffset.x) / display.scale,
        (screenPosition.y - display.viewportOffset.y) / display.scale
    };
}

static bool TouchBindingMatchesScreenPoint(
    const TouchBinding& binding,
    Vector2 screenPosition,
    const DisplayResource& display
)
{
    if(!IsScreenPointInsideViewport(screenPosition, display))
    {
        return false;
    }

    if(binding.anyScreenTouch)
    {
        return true;
    }

    Vector2 internalPosition =
        ScreenToInternalPosition(
            screenPosition,
            display
        );

    return CheckCollisionPointRec(
        internalPosition,
        binding.area
    );
}

static bool IsTouchBindingDown(
    const TouchBinding& binding,
    const DisplayResource& display
)
{
    int touchCount =
        GetTouchPointCount();

    for(int i = 0; i < touchCount; ++i)
    {
        Vector2 screenPosition =
            GetTouchPosition(i);

        if(TouchBindingMatchesScreenPoint(
            binding,
            screenPosition,
            display
        ))
        {
            return true;
        }
    }

    // Mouse fallback. Useful for testing on desktop and for some web browsers.
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 mousePosition =
            GetMousePosition();

        if(TouchBindingMatchesScreenPoint(
            binding,
            mousePosition,
            display
        ))
        {
            return true;
        }
    }

    return false;
}

void InputSystem(World& world)
{
    auto& input =
        world.GetResource<InputResource>();

    auto& bindings =
        world.GetResource<InputBindings>();

    auto& display =
        world.GetResource<DisplayResource>();

    std::unordered_map<std::string, bool> previousDown;

    for(const auto& [name, state] : input.actions)
    {
        previousDown[name] = state.down;
    }

    for(auto& [name, state] : input.actions)
    {
        state.down = false;
        state.pressed = false;
        state.released = false;
        state.value = 0.0f;
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
            }
        }
    }

    for(const auto& [action, touchBindings] : bindings.touch)
    {
        auto& state =
            input.actions[action];

        for(const TouchBinding& binding : touchBindings)
        {
            state.down =
                state.down || IsTouchBindingDown(
                    binding,
                    display
                );
        }
    }

    for(auto& [name, state] : input.actions)
    {
        bool wasDown = false;

        auto previousIt =
            previousDown.find(name);

        if(previousIt != previousDown.end())
        {
            wasDown = previousIt->second;
        }

        state.pressed =
            state.down && !wasDown;

        state.released =
            !state.down && wasDown;

        state.value =
            state.down ? 1.0f : 0.0f;
    }
}