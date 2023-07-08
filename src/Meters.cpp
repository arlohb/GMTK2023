#include "Meters.h"

#include "rl.h"

void Meters::Clamp() {
    workerHappiness = ::Clamp(workerHappiness, 0, 100);
    productivity = ::Clamp(productivity, 0, 100);
    customerSatisfaction = ::Clamp(customerSatisfaction, 0, 100);
    boardConfidence = ::Clamp(boardConfidence, 0, 100);
    money = ::Clamp(money, 0, 100);
}

void Meters::Draw(const int height) {
    const float paddingCount = 1.2;
    const float spacing = 20;

    const float cellCount = count + 2.0 * paddingCount;

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
    
    for(int i = 0; i < count; i++) {
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

std::pair<std::string, State> Meters::CheckEnd() {
    if (workerHappiness <= 0) {
        return std::make_pair(
            "You were horrible to your former colleagues.\n"
            "You gave them no respect,\n"
            "And treated them like machines.\n"
            "They all quit, forcing the company to shut down.\n\n"
            "    Press any key to quit.",
            State::Lost
        );
    } else if (productivity <= 0) {
        return std::make_pair(
            "Your former colleagues had a great time at work!\n"
            "Unfortunately, this is because no work got done.\n"
            "People will always remember there time here,\n"
            "Spending all day playing pool and eating snacks.\n\n"
            "    Press any key to quit.",
            State::Lost
        );
    } else if (customerSatisfaction <= 0) {
        return std::make_pair(
            "There's no nice way of putting this,\n"
            "You're not put out for this job.\n"
            "You were given a chance at leadership,\n"
            "And all your customers abandoned you.\n\n"
            "    Press any key to quit.",
            State::Lost
        );
    } else if (boardConfidence <= 0) {
        return std::make_pair(
            "Who's to say if your company could survive?\n"
            "It didn't matter if your workers or colleagues liked you,\n"
            "Because The Board(TM) doesn't care.\n"
            "You didn't play to their motives, and they fired you.\n\n"
            "    Press any key to quit.",
            State::Lost
        );
    } else if (money <= 0) {
        return std::make_pair(
            "Your workers show up to work every single day.\n"
            "Your former colleagues, devoting their lives.\n"
            "And you failed them. They tried their hardest,\n"
            "And you drove the company into the ground.\n\n"
            "    Press any key to quit.",
            State::Lost
        );
    } else if (progress >= 99.5) {
        return std::make_pair(
            "You did it. You sit in your new office,\n"
            "The board come in. They're shocked.\n"
            "They had no faith, no hope. Well done.\n"
            "You successfully ran this company for 1 day.\n\n"
            "    Press any key to quit.",
            State::Won
        );
    }

    return std::make_pair("", State::Playing);
}

