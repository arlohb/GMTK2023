#include "rl.h"

const int WIDTH = 800;
const int HEIGHT = 600;

int main() {
    SetTraceLogLevel(TraceLogLevel::LOG_ERROR);
    rl::Window window(WIDTH, HEIGHT, "GMTK2023");

    window.SetTargetFPS(60);

    while (!window.ShouldClose()) {
        window.BeginDrawing();
            window.ClearBackground(RAYWHITE);

            DrawCircle(100, 100, 50, RED);

        window.EndDrawing();
    }
}
