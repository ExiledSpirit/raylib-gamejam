#include "ShopInfoRenderSystem.hpp"

#include "../../resources/GameScreenResource.hpp"
#include "../../resources/ShopResource.hpp"
#include "../../resources/SkillCheckResource.hpp"
#include "../../resources/PowerUpDatabaseResource.hpp"
#include "../../resources/EconomyResource.hpp"

#include "../../utils/PowerUpOwnershipHelper.hpp"

#include "utils/SkillCheckUtils.hpp"
#include "utils/PlayerStatsHelper.hpp"
static Color GetTextStyleColor(TextStyle style)
{
    switch(style)
    {
        case TextStyle::Good:
            return Color{255, 170, 70, 255};

        case TextStyle::Bad:
            return Color{140, 140, 150, 255};

        case TextStyle::Muted:
            return Color{110, 110, 120, 255};

        case TextStyle::Gold:
            return GOLD;

        case TextStyle::Keyword:
            return Color{90, 190, 255, 255};

        case TextStyle::Normal:
        default:
            return WHITE;
    }
}
static const char* GetPowerUpTypeLabel(PowerUpType type)
{
    switch(type)
    {
        case PowerUpType::Passive:
            return "PASSIVE";

        case PowerUpType::Active:
            return "ACTIVE";

        default:
            return "UNKNOWN";
    }
}

static Color GetPowerUpTypeColor(PowerUpType type)
{
    switch(type)
    {
        case PowerUpType::Passive:
            return Color{90, 190, 255, 255};

        case PowerUpType::Active:
            return Color{255, 170, 70, 255};

        default:
            return WHITE;
    }
}
static void DrawRichTextLine(
    Font font,
    const RichTextLine& line,
    Vector2 position,
    float fontSize,
    float spacing
)
{
    Vector2 cursor = position;

    for(const RichTextPart& part : line.parts)
    {
        Color color =
            GetTextStyleColor(part.style);

        DrawText(
            part.text.c_str(),
            cursor.x,
            cursor.y,
            fontSize,
            color
        );

        Vector2 size =
            MeasureTextEx(
                font,
                part.text.c_str(),
                fontSize,
                spacing
            );

        cursor.x += size.x;
    }
}

static void DrawRichTextLines(
    Font font,
    const std::vector<RichTextLine>& lines,
    Vector2 position,
    float fontSize,
    float spacing,
    float lineHeight
)
{
    Vector2 cursor = position;

    for(const RichTextLine& line : lines)
    {
        DrawRichTextLine(
            font,
            line,
            cursor,
            fontSize,
            spacing
        );

        cursor.y += lineHeight;
    }
}
static void DrawPowerUpPanel(
    const EconomyResource& economy,
    const PowerUpDefinition& power,
    const std::string& displayName,
    Vector2 position,
    bool hovered
)
{
    bool canPay = economy.gold >= power.price;
    Font font =
        GetFontDefault();

    constexpr float panelWidth = 178.0f;
    constexpr float panelHeight = 112.0f;

    Color backgroundColor =
        hovered && canPay
            ? Color{34, 30, 48, 245}
            : Color{20, 18, 28, 225};

    Color borderColor =
        hovered
            ? Color{255, 220, 120, 255}
            : Color{90, 90, 110, 255};

    borderColor = canPay ? borderColor : GRAY;

    Rectangle panelRect{
        position.x,
        position.y,
        panelWidth,
        panelHeight
    };

    DrawRectangleRec(
        panelRect,
        backgroundColor
    );

    DrawRectangleLinesEx(
        panelRect,
        hovered ? 2.0f : 1.0f,
        borderColor
    );

    Vector2 cursor{
        position.x + 8.0f,
        position.y + 7.0f
    };

    // Name
    DrawText(
        displayName.c_str(),
        cursor.x,
        cursor.y,
        14.0f,
        WHITE
    );

    cursor.y += 17.0f;

    // Passive / Active label
    // DrawText(
    //     GetPowerUpTypeLabel(power.type),
    //     cursor.x,
    //     cursor.y,
    //     9.0f,
    //     GetPowerUpTypeColor(power.type)
    // );

    // Price on the right side
    std::string priceText =
        "$" + std::to_string(power.price);

    Vector2 priceSize =
        MeasureTextEx(
            font,
            priceText.c_str(),
            20.0f,
            1.0f
        );

    DrawText(
        priceText.c_str(),
        position.x + panelWidth - priceSize.x - 8.0f,
        cursor.y,
        20.0f,
        canPay ? GOLD : GRAY
    );

    cursor.y += 17.0f;

    // Description
    DrawRichTextLines(
        font,
        power.descriptionLines,
        cursor,
        9.0f,
        1.0f,
        11.0f
    );
}

void ShopInfoRenderSystem(World& world)
{
    auto& screen = world.GetResource<GameScreenResource>();

    if(screen.current != GameScreen::Shop)
    {
        return;
    }

    auto& shop = world.GetResource<ShopResource>();
    auto& database = world.GetResource<PowerUpDatabaseResource>();
    auto& skill = world.GetResource<SkillCheckResource>();
    auto& owned = world.GetResource<PlayerPowerUpsResource>();
    auto& economy = world.GetResource<EconomyResource>();

    const SkillCheckTarget* hovered =
        GetCurrentHoveredSkillCheckTarget(skill);

    DrawText(TextFormat("$%i", economy.gold), 50, 50, 20, GOLD);
    DrawText(TextFormat("REROLL $%i", shop.rerollCost), 292, 54, 12, GOLD);
    DrawText("EXIT", 304, 300, 12, RED);

    for(int i = 0; i < static_cast<int>(shop.slots.size()); ++i)
    {
        const ShopSlot& slot = shop.slots[i];

        const PowerUpDefinition* power =
            FindPowerUp(database, slot.powerUpId);

        int ownedCount =
            GetPowerUpCount(
                owned,
                power->id
            );

        std::string displayName =
            GetPowerUpDisplayName(
                power->name,
                ownedCount
            );
        if(power == nullptr)
        {
            continue;
        }

        bool isHovered =
            hovered != nullptr &&
            hovered->kind == SkillCheckTargetKind::ShopItem &&
            hovered->itemIndex == i;

        Vector2 panelPosition =
            i == 0
                ? Vector2{32.0f, 120.0f}
                : Vector2{430.0f, 120.0f};

        DrawPowerUpPanel(
            economy,
            *power,
            displayName,
            panelPosition,
            isHovered
        );
    }
}
