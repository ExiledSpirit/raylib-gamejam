#include "PowerUpFactory.hpp"

#include "../utils/RichTextUtils.hpp"

PowerUpDefinition CreateHeavyBatPowerUp()
{
    PowerUpDefinition power{};

    power.id = "anger";
    power.name = "Anger";
    power.type = PowerUpType::Passive;
    power.price = 5;
    power.rarity = 1;

    power.modifiers.push_back({
        PowerUpModifierType::BasePowerMultiplier,
        1.f
    });

    power.modifiers.push_back({
        PowerUpModifierType::ExtraBalls,
        -1.0f
    });

    power.descriptionLines = {
        RichTextLine{
            {
                Good("Increase "),
                T(" bat strength by "),
                Good(" 200% ")
            }
        },
        RichTextLine{
            {
                T("But "),
                Bad(" lowers "),
                T(" total balls by "),
                Bad(" 1 "),
                T(".")
            }
        }
    };

    return power;
}

PowerUpDefinition CreateLuckyGreatPowerUp()
{
    PowerUpDefinition power{};

    power.id = "high_risk_high_reward";
    power.name = "High Risk High Reward";
    power.type = PowerUpType::Passive;
    power.price = 4;
    power.rarity = 1;

    power.modifiers.push_back({
        PowerUpModifierType::GreatPowerBonusMultiplier,
        0.25f
    });

    power.descriptionLines = {
        RichTextLine{
            {
                Good("Great "),
                T(" skill checks give ")
            }
        },
        RichTextLine{
            {
                Good(" +25% "),
                T(" more power.")
            }
        }
    };

    return power;
}

PowerUpDefinition CreateExtraBallPowerUp()
{
    PowerUpDefinition power{};

    power.id = "ball_caddy";
    power.name = "Ball Caddy";
    power.type = PowerUpType::Passive;
    power.price = 6;
    power.rarity = 1;

    power.modifiers.push_back({
        PowerUpModifierType::ExtraBalls,
        1.0f
    });

    power.descriptionLines = {
        RichTextLine{
            {
                Good("Increases "),
                T(" total balls by "),
                Good(" 1")
            }
        }
    };

    return power;
}

PowerUpDefinition CreateGiantBallPowerUp()
{
    PowerUpDefinition power{};

    power.id = "giant_ball";
    power.name = "Giant Ball";
    power.type = PowerUpType::Passive;
    power.price = 5;
    power.rarity = 1;

    power.modifiers.push_back({
        PowerUpModifierType::BallSizeMultiplier,
        0.35f
    });

    power.descriptionLines = {
        RichTextLine{
            {
                T("Increases ball "),
                Good(" size"),
                T(" by "),
                Good(" +35% "),
                T(".")
            }
        },
    };

    return power;
}

PowerUpDefinition CreateMultiBallPowerUp()
{
    PowerUpDefinition power{};

    power.id = "ball_printer";
    power.name = "Ball Printer";
    power.type = PowerUpType::Passive;
    power.price = 8;
    power.rarity = 2;

    power.modifiers.push_back({
        PowerUpModifierType::ExtraLaunchedBalls,
        1.0f
    });

    power.modifiers.push_back({
        PowerUpModifierType::MultiBallAngleStep,
        0.0f
    });

    power.descriptionLines = {
        RichTextLine{
            {
                T("Launches "),
                Good(" +1 "),
                T(" ball.")
            }
        },
    };

    return power;
}

PowerUpDefinition CreateConcentrationPillPowerUp()
{
    PowerUpDefinition power{};

    power.id = "concentration_pill";
    power.name = "Concentration Pill";
    power.type = PowerUpType::Passive;
    power.price = 8;
    power.rarity = 2;

    power.modifiers.push_back({
        PowerUpModifierType::ExtraSkillChecks,
        1.0f
    });

    power.descriptionLines = {
        RichTextLine{
            {
                Good("Increases "),
                T(" Skill Check by "),
                Good(" +1"),
            }
        }
    };

    return power;
}

void LoadCppPowerUps(PowerUpDatabaseResource& database)
{
    database.definitions.clear();

    database.definitions.push_back(CreateHeavyBatPowerUp());
    database.definitions.push_back(CreateLuckyGreatPowerUp());
    database.definitions.push_back(CreateExtraBallPowerUp());

    database.definitions.push_back(CreateGiantBallPowerUp());
    database.definitions.push_back(CreateMultiBallPowerUp());
    database.definitions.push_back(CreateConcentrationPillPowerUp());
}
