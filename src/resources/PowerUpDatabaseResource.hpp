#pragma once

#include <string>
#include <vector>

enum class PowerUpType
{
    Passive,
    Active
};

enum class PowerUpModifierType
{
    ExtraBalls,
    ExtraSkillChecks,
    GoodPowerBonusMultiplier,
    GreatPowerBonusMultiplier,
    SkillCheckSizeMultiplier,
    BasePowerMultiplier,

    BallSizeMultiplier,
    ExtraLaunchedBalls,
    MultiBallAngleStep,
    ExplosionChanceOnWallBounce,
    ExplosionVelocityMultiplier
};

enum class TextStyle
{
    Normal,
    Good,
    Bad,
    Muted,
    Gold,
    Keyword
};

struct RichTextPart
{
    std::string text;
    TextStyle style = TextStyle::Normal;
};

struct RichTextLine
{
    std::vector<RichTextPart> parts;
};

struct PowerUpModifier
{
    PowerUpModifierType type{};
    float value = 0.0f;
};

struct PowerUpDefinition
{
    std::string id;
    std::string name;

    PowerUpType type = PowerUpType::Passive;

    int price = 3;
    int rarity = 1;

    std::vector<PowerUpModifier> modifiers;
    std::vector<RichTextLine> descriptionLines;
};

struct PowerUpDatabaseResource
{
    std::vector<PowerUpDefinition> definitions;
};
