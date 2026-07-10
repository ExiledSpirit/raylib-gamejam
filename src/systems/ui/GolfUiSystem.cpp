#include "GolfUiSystem.hpp"

#include "../../resources/RunResource.hpp"

#include <raylib.h>

void GolfUiSystem(World& world)
{
    auto& run = world.GetResource<RunResource>();

    DrawText(TextFormat("Score: %d / %d", run.currentScore, run.requiredScore), 8, 8, 10, WHITE);
    DrawText(TextFormat("Balls: %d", run.ballsRemaining), 8, 20, 10, WHITE);

    if(run.phase == RunPhase::BallFalling)
    {
        DrawText("Hold SPACE", 8, 34, 10, YELLOW);
    }

    if(run.phase == RunPhase::MapWon)
    {
        DrawText("MAP WON", 130, 84, 12, GREEN);
    }

    if(run.phase == RunPhase::MapLost)
    {
        DrawText("MAP LOST", 128, 84, 12, RED);
    }
}