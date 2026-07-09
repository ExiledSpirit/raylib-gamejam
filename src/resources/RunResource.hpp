enum class RunPhase
{
    WaitingForShot,
    BallRunning,
    ShotFinished,
    MapWon,
    MapLost
};

struct RunResource
{
    int level = 1;

    int requiredScore = 250;
    int currentScore = 0;

    int ballsRemaining = 3;
    int money = 0;

    RunPhase phase = RunPhase::WaitingForShot;
};
