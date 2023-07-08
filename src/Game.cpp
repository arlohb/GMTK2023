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

    baseAssetPath = "../assets/";

    paintingTex = rl::Texture(AssetPath("Painting.png"));
    windowTex = rl::Texture(AssetPath("Window.png"));

    events = {
        Event("Invest in A or B?", {
            {"A", 0, 0, 0, 20, -10},
            {"B", 0, 0, 0, -10, 20},
        }),
    };
}

std::string Game::AssetPath(std::string name) {
    return baseAssetPath + name;
}

void Game::DrawBackground() {
    window.ClearBackground(RAYWHITE);

    paintingTex.Draw(V2(200, 120), 0, 12);

    windowTex.Draw(V2(width / 2.0, 110), 0, 12);
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

void Game::DrawEnd() {
    isRunning = false;

    DrawRectangle(140, 60, width - 240, height / 3, BLACK);

    rl::DrawText("GAME OVER", 220, 80, 40, WHITE);

    rl::DrawText(endMsg, 160, 140, 20, WHITE);
}

void Game::CheckEndGame() {
    if (workerHappiness == 0) {
        endMsg =
            "You were horrible to your former colleagues.\n"
            "You gave them no respect,\n"
            "And treated them like machines.\n"
            "They all quit, forcing the company to shut down."
            "\n    Click to exit";
        DrawEnd();
    } else if (productivity == 0) {
        endMsg =
            "Your former colleagues had a great time at work!\n"
            "Unfortunately, this is because no work got done.\n"
            "People will always remember there time here,\n"
            "Spending all day playing pool and eating snacks."
            "\n    Click to exit";
        DrawEnd();
    } else if (customerSatisfaction == 0) {
        endMsg =
            "There's no nice way of putting this,\n"
            "You're not put out for this job.\n"
            "You were given a chance at leadership,\n"
            "And all your customers abandoned you."
            "\n    Click to exit";
        DrawEnd();
    } else if (boardConfidence == 0) {
        endMsg =
            "Who's to say if your company could survive?\n"
            "It didn't matter if your workers or colleagues liked you,\n"
            "Because The Board(TM) doesn't care.\n"
            "You didn't play to their motives, and they fired you."
            "\n    Click to exit";
        DrawEnd();
    } else if (money == 0) {
        endMsg =
            "Your workers show up to work every single day.\n"
            "Your former colleagues, devoting their lives.\n"
            "And you failed them. They tried their hardest,\n"
            "And you drove the company into the ground."
            "\n    Click to exit";
        DrawEnd();
    }
}

bool Game::Loop() {
    window.BeginDrawing();
        DrawBackground();

        DrawMeters();

        if (isRunning) {
            if (IsKeyPressed(KEY_SPACE))
                NewEvent();
            DrawEvent();

            CheckEndGame();
        } else {
            DrawEnd();

            if (rl::Mouse::IsButtonPressed(0))
                return true;
        }

    window.EndDrawing();

    return false;
}

