#include "Game.h"

#include "raylib.h"
#include "raymath.h"

Game::Game(int width, int height, rl::Window& window):
    width(width),
    height(height),
    window(window)
{
    window.SetTargetFPS(60);

    SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_BILINEAR);
}

void Game::ClampMeters() {
    workerHappiness = Clamp(workerHappiness, 0, 100);
    productivity = Clamp(productivity, 0, 100);
    customerSatisfaction = Clamp(customerSatisfaction, 0, 100);
    boardConfidence = Clamp(boardConfidence, 0, 100);
    money = Clamp(money, 0, 100);
}

void Game::DrawMeters() {
    const float paddingCount = 1.5;
    const float spacing = 4;

    const float cellCount = metersCount + 2.0 * paddingCount;

    // This doesn't take into account cell spacing
    const float cellHeight = height / cellCount;
    // This does
    const float cellWidth = cellHeight - spacing / 2 + 26;

    const std::string names[] = {
        "  Worker\n Happiness",
        "Productivity",
        " Customer\nSatisfaction",
        "   Board\n Confidence",
        "   Money"
    };

    const float meters[] = {
        workerHappiness,
        productivity,
        customerSatisfaction,
        boardConfidence,
        money
    };
    
    for(int i = 0; i < metersCount; i++) {
        const float cell = i + paddingCount;
        const float x = 0;
        const float y = cell * cellHeight + spacing / 2;

        DrawRectangle(x, y, cellWidth, cellHeight - spacing / 2, GRAY);

        rl::DrawText(names[i], x + 10, y + 10, 16, BLACK);

        const float barPadding = 10;
        const float barHeight = 10;
        DrawRectangle(
            x + barPadding,
            y + cellHeight - spacing * 2 - barHeight,
            cellWidth - barPadding * 2,
            barHeight,
            WHITE
        );
        DrawRectangle(
            x + barPadding,
            y + cellHeight - spacing * 2 - barHeight,
            (cellWidth - barPadding * 2) * meters[i] / 100,
            barHeight,
            BLACK
        );
    }
}

void Game::Loop() {
    window.BeginDrawing();
        window.ClearBackground(RAYWHITE);

        DrawMeters();

    window.EndDrawing();
}

