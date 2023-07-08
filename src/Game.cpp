#include "Game.h"

#include "fmt/core.h"

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
    wallTex = rl::Texture(AssetPath("Wall.png"));
    clockTex = rl::Texture(AssetPath("Clock.png"));
    hourHandTex = rl::Texture(AssetPath("HourHand.png"));
    minHandTex = rl::Texture(AssetPath("MinHand.png"));

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

    rl::Rectangle wallFull(0, 0, wallTex.width, wallTex.height);
    rl::Rectangle backgroundFull(0, 0, width, height);
    wallTex.Draw(wallFull, backgroundFull);

    paintingTex.Draw(V2(160, height / 2.0 + 100), -90, 12);
    windowTex.Draw(V2(width / 2.0 - 30, 120), 0, 12);
}

void Game::ClampMeters() {
    workerHappiness = Clamp(workerHappiness, 0, 100);
    productivity = Clamp(productivity, 0, 100);
    customerSatisfaction = Clamp(customerSatisfaction, 0, 100);
    boardConfidence = Clamp(boardConfidence, 0, 100);
    money = Clamp(money, 0, 100);
}

void Game::DrawMeters() {
    const float paddingCount = 1.2;
    const float spacing = 20;

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

        DrawRectangle(x, y, cellWidth, cellHeight - spacing / 2, rl::Color(102, 57, 49));

        rl::DrawText(names[i], x + 10, y + 15, 16, rl::Color(238, 195, 154));

        const float barPadding = 10;
        const float barHeight = 10;
        DrawRectangle(
            x + barPadding,
            y + cellHeight - spacing * 2 - barHeight + 11,
            cellWidth - barPadding * 2,
            barHeight,
            rl::Color(118, 72, 50)
        );
        DrawRectangle(
            x + barPadding,
            y + cellHeight - spacing * 2 - barHeight + 11,
            (cellWidth - barPadding * 2) * meters[i] / 100,
            barHeight,
            rl::Color(238, 195, 154)
        );
    }
}

void Game::DrawDay() {
    clockTex.Draw(V2(120, 0), 0, 5);

    float percent = progress / 100;
    float totalHours = percent * hoursInDay;
    float totalHoursIntegral = totalHours;
    int mins = std::modf(totalHours, &totalHoursIntegral) * 60;

    // 120 brings the hand to 09:00
    int hourAngle = 120 + totalHours * 30;
    // 210 brings the hand to 00:00
    int minAngle = 210 + mins * 6;
    
    hourHandTex.Draw(V2(120 + (40 * 5), 24 * 5), hourAngle, 5);
    minHandTex.Draw(V2(120 + (40 * 5), 24 * 5), minAngle, 5);
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
    progress += 100.0 / eventsInDay;

    workerHappiness += option.workerHappiness;
    productivity += option.productivity;
    customerSatisfaction += option.customerSatisfaction;
    boardConfidence += option.boardConfidence;
    money += option.money;

    ClampMeters();
}

void Game::DrawEnd() {
    state = State::End;

    DrawRectangle(140, 60, width - 240, height / 3, BLACK);

    rl::DrawText(won ? "YOU WIN!" : "GAME OVER...", 220, 80, 40, WHITE);

    rl::DrawText(endMsg, 160, 140, 20, WHITE);
}

void Game::CheckEndGame() {
    if (workerHappiness <= 0) {
        endMsg =
            "You were horrible to your former colleagues.\n"
            "You gave them no respect,\n"
            "And treated them like machines.\n"
            "They all quit, forcing the company to shut down.\n\n"
            "    Click to exit";
        DrawEnd();
    } else if (productivity <= 0) {
        endMsg =
            "Your former colleagues had a great time at work!\n"
            "Unfortunately, this is because no work got done.\n"
            "People will always remember there time here,\n"
            "Spending all day playing pool and eating snacks.\n\n"
            "    Click to exit";
        DrawEnd();
    } else if (customerSatisfaction <= 0) {
        endMsg =
            "There's no nice way of putting this,\n"
            "You're not put out for this job.\n"
            "You were given a chance at leadership,\n"
            "And all your customers abandoned you.\n\n"
            "    Click to exit";
        DrawEnd();
    } else if (boardConfidence <= 0) {
        endMsg =
            "Who's to say if your company could survive?\n"
            "It didn't matter if your workers or colleagues liked you,\n"
            "Because The Board(TM) doesn't care.\n"
            "You didn't play to their motives, and they fired you.\n\n"
            "    Click to exit";
        DrawEnd();
    } else if (money <= 0) {
        endMsg =
            "Your workers show up to work every single day.\n"
            "Your former colleagues, devoting their lives.\n"
            "And you failed them. They tried their hardest,\n"
            "And you drove the company into the ground.\n\n"
            "    Click to exit";
        DrawEnd();
    } else if (progress >= 100) {
        won = true;
        endMsg =
            "You did it. You sit in your new office,\n"
            "The board come in. They're shocked.\n"
            "They had no faith, no hope, well done.\n"
            "You successfully ran this company for 1 day.\n\n"
            "    Click to exit";
        DrawEnd();
    }
}

bool Game::Loop() {
    window.BeginDrawing();
        DrawBackground();

        DrawMeters();
        DrawDay();

        if (state == State::Playing) {
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

