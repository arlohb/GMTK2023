#include "Game.h"

int main() {
    const int width = 1000;
    const int height = 800;

    SetTraceLogLevel(TraceLogLevel::LOG_WARNING);
    rl::Window window(width, height, "GMTK2023");

    Game game(width, height, window);

    while (!window.ShouldClose())
        if (game.Loop())
            break;
}
