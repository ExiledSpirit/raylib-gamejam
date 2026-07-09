enum class GameScreen
{
    Menu,
    Playing
};

enum class MenuPanel
{
    Main,
    LoadGame,
    Options
};

struct GameScreenResource
{
    GameScreen screen = GameScreen::Menu;
    MenuPanel menuPanel = MenuPanel::Main;
};
