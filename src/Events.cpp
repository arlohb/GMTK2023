#include "Events.h"

#include "TextWrap.h"
#include "rl.h"

void Events::Next() {
    // GetRandomSeed is already called when raylib loads with unix time
    int index = GetRandomValue(0, events.size() - 1);
    current = events[index];
    events.erase(events.begin() + index);
}

void Events::ApplyOption(Meters& meters, EventOption& option) {
    meters.progress += 100.0 / eventsInDay;

    meters.workerHappiness += option.workerHappiness;
    meters.productivity += option.productivity;
    meters.customerSatisfaction += option.customerSatisfaction;
    meters.boardConfidence += option.boardConfidence;
    meters.money += option.money;

    meters.Clamp();
}

void Events::Draw(Meters& meters, const int width, const int height) {
    if (!current.has_value()) return;
    Event& event = current.value();

    const int eventX = width / 2.5;
    const int eventY = 50;
    const int eventWidth = width / 1.8;
    const int eventHeight = height / 1.5;

    rl::Rectangle rect(eventX, eventY, eventWidth, eventHeight);
    DrawRectangleRounded(rect, 0.2, 6, GRAY);

    rl::Rectangle textRect(eventX + 20, eventY + 20, rect.width - 40, rect.height - 40);
    DrawTextBoxed(event.text.c_str(), textRect, 20, 1, BLACK);

    const float paddingCount = 0.1;
    const float spacing = 6;
    const float cellCount = event.options.size() + 2.0 * paddingCount;
    // This doesn't take into account cell spacing
    const float cellWidth = eventWidth / cellCount;
    const float cellHeight = 90;
    
    int i = 0;
    for(EventOption& option : event.options) {
        const float cell = i++ + paddingCount;
        const float btnX = eventX + cell * cellWidth + spacing / 2;
        const float btnY = eventY + eventHeight - cellHeight - 10;

        rl::Rectangle btnRect(btnX, btnY, cellWidth - spacing, cellHeight);
        DrawRectangleRounded(btnRect, 0.1, 6, BLACK);
        rl::Rectangle textRect(btnX + 2, btnY + 2, btnRect.width - 4, btnRect.height - 4);
        DrawTextBoxed(option.text.c_str(), textRect, 14, 1, WHITE);

        bool overBtn = btnRect.CheckCollision(rl::Mouse::GetPosition());
        if (rl::Mouse::IsButtonPressed(0) && overBtn) {
            ApplyOption(meters, option);
            current.reset();
        }
    }
}

Events::Events() {
    events = {
        Event(
            "You sell paperclips to an alt-right fascist,\n"
            "The public is pressuring you to stop providing them paperclips.\n"
            "Do you blacklist them? Or continue to sell them paperclips?",
            {
                {"Stop doing business with them.", 10, 0, 20, 0, -20},
                {"What they do with the paperclips is none of our business.", -10, 0, -20, 0, 20},
            }
        ),
        Event(
            "Your new employees want a pool table that they'll *definitely* only use in their breaks.\n"
            "They've picked out a very expensive table, clearly trying to take advantage of your inexperience.\n"
            "You've found one online that looks the exact same but half the price.",
            {
                {"They don't need a pool table.\nWork is for working.", -20, 10, 0, 10, 5},
                {"Get them the cheaper table.", 15, -15, 0, -5, -10},
                {"Get them the expensive table, they probably deserve it.", 20, -20, 0, -10, -20},
            }
        ),
        Event(
            "Apparently your predecessor had some under the table paperclip dealings.\n"
            "There was a scathing article uncovering the shadiness of the paperclip world.\n"
            "People are calling for deals like this to end, to make paperclip trading more fair and just.\n"
            "Do you end the deals, meaning everyone can buy paperclips fairly?",
            {
                {"End the deals, there's no reason for us to control who gets paperclips.", 0, 0, 20, 0, -10},
                {"We're a private company, and can do what we want. "
                    "Some people just deserve paperclips more than others.", 0, 0, -15, 0, 15},
            }
        ),
        Event(
            "The board feels like workers aren't being productive enough.\n"
            "There solution to this is to install 'Employee Monitoring Software'.\n"
            "This makes sure the mouse moves every so often, and people are always working.\n"
            "It can also monitor everything typed and done on the computer.\n"
            "Workers say this is too controlling and authoritarian.",
            {
                {"Install the software. It should't matter if they've got nothing to hide.", -25, 20, 0, 15, 10},
                {"Don't install the software. We should be able to trust our employees.", 20, -5, 0, -10, -5},
            }
        ),
        Event(
            "A competitor has entered the market with paperclips at half the price of ours.\n"
            "By chance, you went to school with the CEO of the company.\n"
            "You weren't friends, but he was a great guy when you knew him.\n"
            "You went to a few parties with him back in the day,\n"
            "And have some *very* embarrasing photos that could sink his company.",
            {
                {"Leak the photos to the press, it's just business.", 0, 0, 0, 5, 10},
                {"Do nothing, you're not a monster.", 0, 0, 0, 0, -10},
            }
        ),
        Event(
            "The board has suggested the use of an AI to manage the business.\n"
            "This AI could decide where some of our money was spent,\n"
            "And would massively cut down on personnel costs.\n"
            "This would unfortunately result in people losing jobs.\n"
            "Will you make use of the AI?",
            {
                {"Use the AI for purchasing decisions, 20% of the workforce made redundant.", -30, 30, -5, 15, 20},
                {"The AI can't be trusted, these people have done this their whole lives.", 20, 0, 5, -10, -10},
            }
        ),
        Event(
            "An employee was stealing proprietary company secrets about paperclip manufacture.\n"
            "We don't *need* to prosecute them,\n"
            "But it would set a good example.\n"
            "It could also ruin their life.",
            {
                {"Sue them for all they're worth.", -5, 0, 0, 15, 15},
                {"Just fire them, that's enough damage.", 15, 0, 0, -10, 0},
            }
        ),
    };

    eventsInDay = events.size();
}
