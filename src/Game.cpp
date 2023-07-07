#include "Game.h"

#include "raylib.h"
#include "raymath.h"
#include <thread>

Game::Game(int width, int height, rl::Window& window):
    width(width),
    height(height),
    window(window)
{
    window.SetTargetFPS(60);

    SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_BILINEAR);

    events = {
        Event("Invest in A or B?", {
            {"A", 0, 0, 0, 20, -10},
            {"B", 0, 0, 0, -10, 20},
        }),
    };
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

void Game::NewEvent() {
    int index = GetRandomValue(0, events.size() - 1);
    currentEvent = &events[index];
}

void Game::DrawEvent() {
    if (!currentEvent.has_value()) return;
    Event* event = currentEvent.value();

    const int eventX = width / 4.0;
    const int eventY = 50;
    const int eventWidth = width / 2.0;
    const int eventHeight = height / 2.0;

    rl::Rectangle rect(eventX, eventY, eventWidth, eventHeight);
    DrawRectangleRounded(rect, 0.2, 6, GRAY);

    rl::DrawText(event->text, eventX + 40, eventY + 20, 40, BLACK);

    const float paddingCount = 1;
    const float spacing = 8;
    const float cellCount = event->options.size() * 2 * paddingCount;
    // This doesn't take into account cell spacing
    const float cellWidth = eventWidth / cellCount;
    const float cellHeight = 50;
    
    int i = 0;
    for(EventOption& option : event->options) {
        const float cell = i++ + paddingCount;
        const float btnX = eventX + cell * cellWidth + spacing / 2;
        const float btnY = eventY + eventHeight - cellHeight - 10;

        rl::Rectangle btnRect(btnX, btnY, cellWidth - spacing, cellHeight);
        DrawRectangleRounded(btnRect, 0.1, 6, BLACK);
        rl::DrawText(option.text, btnX + 10, btnY + 10, 24, WHITE);

        bool overBtn = btnRect.CheckCollision(rl::Mouse::GetPosition());
        if (rl::Mouse::IsButtonPressed(0) && overBtn) {
            ApplyEventOption(option);
            currentEvent.reset();
        }
    }
}

void Game::ApplyEventOption(EventOption& option) {
    workerHappiness += option.workerHappiness;
    productivity += option.productivity;
    customerSatisfaction += option.customerSatisfaction;
    boardConfidence += option.boardConfidence;
    money += option.money;

    ClampMeters();
}

void Game::Loop() {
    window.BeginDrawing();
        window.ClearBackground(RAYWHITE);

        DrawMeters();

        if (IsKeyPressed(KEY_SPACE))
            NewEvent();

        DrawEvent();

    window.EndDrawing();
}

