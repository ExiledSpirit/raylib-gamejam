#pragma once

enum class RunPhase
{
    WaitingToDropBall,     // player presses SPACE to start the falling ball
    BallFalling,           // player must press SPACE at the right timing
    BallMissed,            // Player missed ball strike

    FirstStrikeAnimation,  // zoom-in + first hit animation
    SkillChecks,           // DBD-like checks
    LastStrikeAnimation,   // final hit animation

    BallRunning,           // Box2D ball is moving
    ShotFinished,

    MapWon,
    MapLost
};

struct RunResource
{
    RunPhase phase = RunPhase::WaitingToDropBall;

    int level = 1;

    float phaseTimer = 0.0f;

    int requiredScore = 250;
    int currentScore = 0;

    int ballsRemaining = 3;
};