#pragma once

#include "../resources/RunResource.hpp"

inline const char* RunPhaseToString(RunPhase phase)
{
    switch(phase)
    {
        case RunPhase::WaitingToDropBall:
            return "WaitingToDropBall";

        case RunPhase::BallFalling:
            return "BallFalling";

        case RunPhase::BallMissed:
            return "BallMissed";

        case RunPhase::FirstStrikeAnimation:
            return "FirstStrikeAnimation";

        case RunPhase::SkillChecks:
            return "SkillChecks";

        case RunPhase::LastStrikeAnimation:
            return "LastStrikeAnimation";

        case RunPhase::BallRunning:
            return "BallRunning";

        case RunPhase::ShotFinished:
            return "ShotFinished";

        case RunPhase::MapWon:
            return "MapWon";

        case RunPhase::MapLost:
            return "MapLost";
    }

    return "Unknown";
}