#pragma once

enum class RunPhase
{
    MainMenu,
    WaitingToDropBall,     // player presses SPACE to start the falling ball
    BallFalling,           // player must press SPACE at the right timing
    BallMissed,            // Player missed ball strike

    FirstStrikeAnimation,  // zoom-in + first hit animation
    SkillChecks,           // DBD-like checks
    LastStrikeAnimation,   // final hit animation

    BallRunning,           // Box2D ball is moving
    ShotFinished,

    LevelReward,
    Shop,

    MapWon,
    MapLost
};

struct RunResource
{
    RunPhase phase = RunPhase::MainMenu;

    int level = 1;

    float phaseTimer = 0.0f;

    __int128_t requiredScore = 300;
    __int128_t currentScore = 0;

    int ballsRemaining = 3;
};