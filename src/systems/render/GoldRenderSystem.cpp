#include "GolfRenderSystem.hpp"

#include "../../resources/LauncherResource.hpp"

#include <raylib.h>
#include <cmath>

void GolfRenderSystem(World& world)
{
    auto& launcher = world.GetResource<LauncherResource>();

    ClearBackground(Color{8, 7, 18, 255});

    DrawCircleV(launcher.position, 5.0f, WHITE);

    Vector2 dir{
        std::cos(launcher.aimAngle),
        std::sin(launcher.aimAngle)
    };

    Vector2 end{
        launcher.position.x + dir.x * 28.0f,
        launcher.position.y + dir.y * 28.0f
    };

    DrawLineEx(launcher.position, end, 2.0f, YELLOW);

    if(launcher.charging)
    {
        DrawRectangle(20, 160, 80, 6, DARKGRAY);
        DrawRectangle(
            20,
            160,
            static_cast<int>(80.0f * (launcher.power / launcher.maxPower)),
            6,
            GREEN
        );
    }
}
