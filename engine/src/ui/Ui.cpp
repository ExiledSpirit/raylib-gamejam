#include "Ui.hpp"

#include "UiContext.hpp"

#include "../ecs/resources/TimeResource.hpp"
#include "../input/InputResource.hpp"

#include <algorithm>
#include <cmath>

static float ApproachExp(float current, float target, float speed, float dt)
{
    float t = 1.f - std::exp(-speed * dt);
    return current + (target - current) * t;
}

static void DrawTextCentered(
    const char* text,
    Rectangle rect,
    int fontSize,
    Color color
)
{
    int width =
        MeasureText(text, fontSize);

    DrawText(
        text,
        static_cast<int>(rect.x + rect.width * 0.5f - width * 0.5f),
        static_cast<int>(rect.y + rect.height * 0.5f - fontSize * 0.5f),
        fontSize,
        color
    );
}

void UiBeginFrame(World& world)
{
    auto& ui =
        world.GetResource<UiContext>();

    auto& input =
        world.GetResource<InputResource>();

    ui.previousItemCount =
        std::max(ui.previousItemCount, 1);

    ui.upPressed = input.IsPressed("ui_up");
    ui.downPressed = input.IsPressed("ui_down");
    ui.leftPressed = input.IsPressed("ui_left");
    ui.rightPressed = input.IsPressed("ui_right");
    ui.acceptPressed = input.IsPressed("ui_accept");
    ui.cancelPressed = input.IsPressed("ui_cancel");

    if(ui.downPressed)
    {
        ui.focusedIndex++;
    }

    if(ui.upPressed)
    {
        ui.focusedIndex--;
    }

    if(ui.focusedIndex < 0)
    {
        ui.focusedIndex = ui.previousItemCount - 1;
    }

    if(ui.focusedIndex >= ui.previousItemCount)
    {
        ui.focusedIndex = 0;
    }

    ui.itemIndex = 0;
    ui.itemCount = 0;
}

void UiEndFrame(World& world)
{
    auto& ui =
        world.GetResource<UiContext>();

    auto& time =
        world.GetResource<TimeResource>();

    ui.previousItemCount =
        ui.itemCount;

    if(ui.itemCount <= 0)
    {
        ui.focusedIndex = 0;
        ui.previousItemCount = 0;
        return;
    }

    ui.focusedIndex =
        std::clamp(ui.focusedIndex, 0, ui.itemCount - 1);

    if(!ui.selectorInitialized)
    {
        ui.selectorPosition = ui.selectorTarget;
        ui.selectorInitialized = true;
    }

    ui.selectorPosition.x =
        ApproachExp(ui.selectorPosition.x, ui.selectorTarget.x, 28.f, time.deltaTime);

    ui.selectorPosition.y =
        ApproachExp(ui.selectorPosition.y, ui.selectorTarget.y, 28.f, time.deltaTime);

    ui.selectorRotation +=
        360.f * time.deltaTime;

    DrawRectanglePro(
        Rectangle{
            ui.selectorPosition.x,
            ui.selectorPosition.y,
            6.f,
            6.f
        },
        Vector2{3.f, 3.f},
        ui.selectorRotation,
        ui.style.selector
    );
}

void UiPanel(Rectangle rect)
{
    DrawRectangleRec(
        rect,
        Color{10, 8, 24, 225}
    );

    DrawRectangleLinesEx(
        rect,
        1.f,
        Color{80, 78, 140, 255}
    );
}

void UiLabel(Rectangle rect, const char* text, int fontSize, Color color)
{
    DrawTextCentered(text, rect, fontSize, color);
}

bool UiButton(World& world, Rectangle rect, const char* text)
{
    auto& ui =
        world.GetResource<UiContext>();

    int index =
        ui.itemIndex++;

    ui.itemCount++;

    bool focused =
        index == ui.focusedIndex;

    bool activated =
        focused && ui.acceptPressed;

    Color color =
        ui.style.button;

    if(focused)
    {
        color = activated
            ? ui.style.buttonPressed
            : ui.style.buttonFocused;

        ui.selectorTarget = Vector2{
            rect.x - 10.f,
            rect.y + rect.height * 0.5f
        };
    }

    DrawRectangleRec(rect, color);
    DrawRectangleLinesEx(rect, 1.f, ui.style.panelBorder);

    DrawTextCentered(
        text,
        rect,
        10,
        ui.style.text
    );

    return activated;
}

bool UiToggle(
    World& world,
    Rectangle rect,
    const char* label,
    bool value
)
{
    auto& ui =
        world.GetResource<UiContext>();

    int index =
        ui.itemIndex++;

    ui.itemCount++;

    bool focused =
        index == ui.focusedIndex;

    if(focused)
    {
        ui.selectorTarget = Vector2{
            rect.x - 10.f,
            rect.y + rect.height * 0.5f
        };

        if(ui.acceptPressed || ui.leftPressed || ui.rightPressed)
        {
            value = !value;
        }
    }

    DrawRectangleRec(
        rect,
        focused ? ui.style.buttonFocused : ui.style.button
    );

    DrawRectangleLinesEx(rect, 1.f, ui.style.panelBorder);

    const char* valueText =
        value ? "ON" : "OFF";

    DrawText(
        label,
        static_cast<int>(rect.x + 6.f),
        static_cast<int>(rect.y + 5.f),
        10,
        ui.style.text
    );

    int valueWidth =
        MeasureText(valueText, 10);

    DrawText(
        valueText,
        static_cast<int>(rect.x + rect.width - valueWidth - 6.f),
        static_cast<int>(rect.y + 5.f),
        10,
        ui.style.text
    );

    return value;
}

int UiChoice(
    World& world,
    Rectangle rect,
    const char* label,
    int currentIndex,
    const char** options,
    int optionCount
)
{
    auto& ui =
        world.GetResource<UiContext>();

    int index =
        ui.itemIndex++;

    ui.itemCount++;

    bool focused =
        index == ui.focusedIndex;

    if(focused)
    {
        ui.selectorTarget = Vector2{
            rect.x - 10.f,
            rect.y + rect.height * 0.5f
        };

        if(ui.leftPressed)
        {
            currentIndex--;
        }

        if(ui.rightPressed)
        {
            currentIndex++;
        }

        if(currentIndex < 0)
        {
            currentIndex = optionCount - 1;
        }

        if(currentIndex >= optionCount)
        {
            currentIndex = 0;
        }
    }

    DrawRectangleRec(
        rect,
        focused ? ui.style.buttonFocused : ui.style.button
    );

    DrawRectangleLinesEx(rect, 1.f, ui.style.panelBorder);

    DrawText(
        label,
        static_cast<int>(rect.x + 6.f),
        static_cast<int>(rect.y + 5.f),
        10,
        ui.style.text
    );

    const char* valueText =
        options[currentIndex];

    int valueWidth =
        MeasureText(valueText, 10);

    DrawText(
        valueText,
        static_cast<int>(rect.x + rect.width - valueWidth - 6.f),
        static_cast<int>(rect.y + 5.f),
        10,
        ui.style.text
    );

    return currentIndex;
}

float UiSlider(
    World& world,
    Rectangle rect,
    const char* label,
    float value,
    float step
)
{
    auto& ui =
        world.GetResource<UiContext>();

    int index =
        ui.itemIndex++;

    ui.itemCount++;

    bool focused =
        index == ui.focusedIndex;

    if(focused)
    {
        ui.selectorTarget = Vector2{
            rect.x - 10.f,
            rect.y + rect.height * 0.5f
        };

        if(ui.leftPressed)
        {
            value -= step;
        }

        if(ui.rightPressed)
        {
            value += step;
        }

        value = std::clamp(value, 0.f, 1.f);
    }

    DrawRectangleRec(
        rect,
        focused ? ui.style.buttonFocused : ui.style.button
    );

    DrawRectangleLinesEx(rect, 1.f, ui.style.panelBorder);

    DrawText(
        label,
        static_cast<int>(rect.x + 6.f),
        static_cast<int>(rect.y + 5.f),
        10,
        ui.style.text
    );

    Rectangle bar{
        rect.x + rect.width - 58.f,
        rect.y + rect.height * 0.5f - 2.f,
        48.f,
        4.f
    };

    DrawRectangleRec(
        bar,
        Color{20, 16, 36, 255}
    );

    DrawRectangleRec(
        Rectangle{
            bar.x,
            bar.y,
            bar.width * value,
            bar.height
        },
        ui.style.text
    );

    return value;
}