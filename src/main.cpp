#include "Game.h"

int main() {
    const int width = 800;
    const int height = 600;

    SetTraceLogLevel(TraceLogLevel::LOG_WARNING);
    rl::Window window = rl::Window(width, height, "GMTK2023");

    Game game(width, height, window);

    while (!window.ShouldClose())
        game.Loop();
}
