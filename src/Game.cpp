#include "Game.h"

Game::Game(int width, int height, rl::Window& window):
    width(width),
    height(height),
    window(window)
{
    window.SetTargetFPS(60);
}

void Game::Loop() {
    window.BeginDrawing();
        window.ClearBackground(RAYWHITE);

        DrawCircle(100, 100, 50, RED);

    window.EndDrawing();
}

