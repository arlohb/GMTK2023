#include "Game.h"

#include "TextWrap.h"
#include "fmt/core.h"

Game::Game(int width, int height, rl::Window& window):
    width(width),
    height(height),
    window(window)
{
    window.SetTargetFPS(60);
    SetExitKey(0);
}

void Game::DrawIntro() {
    DrawRectangle(0, 0, width, height, BLACK);

    std::string introMsg =
        "You are just a worker, a nobody.\n"
        "The company you work for creates paperclips.\n"
        "You don't particularly enjoy working here,\n"
        "But it's a living.\n\n"

        "One day though, you arrive at work, and everyone is frantic.\n"
        "After talking to your colleagues,\n"
        "You find out the boss went on holiday without telling the board.\n"
        "This means nobody is running the company!\n\n"

        "The board is scrambling to find someone else,\n"
        "With everyone else at the company running around,\n"
        "You stand out to them, as you sit down calmly, not really caring.\n"
        "Unfortunately, they interpret this as a calm leader getting to work,\n"
        "And before you know it, the board approach you...\n\n"

        "\"We want to make you *temporary* CEO of the company\"\n"
        "\"...\"\n"
        "\"We don't care if you're not trained!\"\n"
        "\"...\"\n"
        "\"You start immediately!\"\n"
    ;
    rl::DrawText(introMsg, 20, 20, 20, WHITE);

    rl::DrawText("The Day You Became The CEO...", 50, height - 90, 40, WHITE);
    rl::DrawText("Press any key to continue", 50, height - 30, 20, WHITE);
}

void Game::DrawTutorial() {
    assets.tutorial.Draw(Assets::TexRect(assets.tutorial), rl::Rectangle(0, 0, width, height));
}

void Game::DrawBackground() {
    window.ClearBackground(RAYWHITE);

    assets.wall.Draw(
        Assets::TexRect(assets.wall),
        rl::Rectangle(0, 0, width, height)
    );

    assets.painting.Draw(V2(160, height / 2.0 + 100), -90, 12);
    assets.window.Draw(V2(width / 2.0 - 30, 120), 0, 12);
}

void Game::DrawDay() {
    const float x = 100;
    const float y = 60;
    const float scale = 4;

    assets.clock.Draw(V2(x, y), 0, scale);

    float percent = meters.progress / 100;
    float totalHours = percent * hoursInDay;
    float totalHoursIntegral = totalHours;
    int mins = std::modf(totalHours, &totalHoursIntegral) * 60;

    // 120 brings the hand to 09:00
    int hourAngle = 120 + totalHours * 30;
    // 210 brings the hand to 00:00
    int minAngle = 210 + mins * 6;
    
    assets.hourHand.Draw(V2(x + (40 * scale), y + 24 * scale), hourAngle, scale);
    assets.minHand.Draw(V2(x + (40 * scale), y + 24 * scale), minAngle, scale);
}

bool Game::DrawEventBtn() {
    const float scale = 10;
    rl::Rectangle rect(width - 380, height - 200, assets.nextEventBtn.width * scale, assets.nextEventBtn.height * scale);

    assets.nextEventBtn.Draw(
        Assets::TexRect(assets.nextEventBtn),
        rect
    );

    return rect.CheckCollision(rl::Mouse::GetPosition()) && rl::Mouse::IsButtonPressed(0);
}

void Game::DrawEnd() {
    const int padding = 140;
    rl::Rectangle rect(padding, padding, width - padding * 2, height - padding * 2);
    assets.event.Draw(Assets::TexRect(assets.event), rect);

    const int textPad = padding + 100;
    const rl::Color textColour = rl::Color(34, 32, 52);

    rl::DrawText(state == State::Won ? "YOU WIN!" : "GAME OVER...", textPad, textPad, 40, textColour);

    rl::DrawText(endMsg, textPad, textPad + 50, 20, textColour);
}

bool AnyKeyPressed() {
    return rl::Mouse::IsButtonPressed(0) || IsKeyPressed(GetKeyPressed());
}

bool Game::Loop() {
    window.BeginDrawing();
        DrawBackground();

        meters.Draw(height);
        DrawDay();

        switch (state) {
            using enum State;
            case Intro: {
                DrawIntro();

                if (AnyKeyPressed())
                    state = State::Tutorial;

                break;
            }
            case Tutorial:
            case Playing: {
                bool interactable = true;

                if (!events.current.has_value()) {
                    bool btnPressed = DrawEventBtn();

                    if (btnPressed || IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) {
                        // End the tutorial
                        state = State::Playing;
                        events.Next();
                        // Don't want to press the options in this frame
                        interactable = false;
                    }
                }

                // Can't be done in switch case
                // as needs to be drawn after eventBtn
                if (state == State::Tutorial)
                    DrawTutorial();

                events.Draw(meters, assets, width, height, interactable);

                auto [msg, newState] = meters.CheckEnd();
                endMsg = msg;
                // Can't set this if we're still in the tutorial
                if (newState != State::Playing)
                    state = newState;

                break;
            }
            case Won:
            case Lost: {
                DrawEnd();

                if (AnyKeyPressed())
                    return true;

                break;
            }
        }

    window.EndDrawing();

    return false;
}

