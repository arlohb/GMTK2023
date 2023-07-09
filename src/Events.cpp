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

void Events::Draw(Meters& meters, Assets& assets, const int width, const int height, bool interactable) {
    if (!current.has_value()) return;
    Event& event = current.value();

    const int eventX = width / 2.9;
    const int eventY = 50;
    const int eventWidth = width / 1.6;
    const int eventHeight = height - eventY - 50;

    rl::Rectangle rect(eventX, eventY, eventWidth, eventHeight);
    assets.event.Draw(Assets::TexRect(assets.event), rect);

    const rl::Color textColour = rl::Color(34, 32, 52);

    const int textPadX = 85;
    const int textPadY = 120;
    rl::Rectangle textRect(eventX + textPadX, eventY + textPadY, rect.width - textPadX * 2, rect.height - textPadY * 2);
    DrawTextBoxed(event.text.c_str(), textRect, 20, 1, 1, textColour);

    const float paddingCount = 0.2;
    const float spacing = 4;
    const float cellCount = event.options.size() + 2.0 * paddingCount;
    // This doesn't take into account cell spacing
    const float cellWidth = eventWidth / cellCount;
    const float cellHeight = 200;
    
    int i = 0;
    for(EventOption& option : event.options) {
        const float cell = i++ + paddingCount;
        const float btnX = eventX + cell * cellWidth + spacing / 2;
        const float btnY = eventY + eventHeight - cellHeight - 10;
        const int textPadX = 30;
        const int textPadY = 35;

        rl::Rectangle btnRect(btnX, btnY, cellWidth - spacing, cellHeight);
        const int dimTint = 210;
        assets.event.Draw(Assets::TexRect(assets.event), btnRect, {0, 0}, 0, rl::Color(dimTint, dimTint, dimTint));
        rl::Rectangle textRect(btnX + textPadX, btnY + textPadY, btnRect.width - textPadX * 2, btnRect.height - textPadY * 2);
        DrawTextBoxed(option.text.c_str(), textRect, 14, 0.8, 1, textColour);

        bool overBtn = btnRect.CheckCollision(rl::Mouse::GetPosition());
        if (rl::Mouse::IsButtonPressed(0) && overBtn && interactable) {
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
        Event(
            "Some employees were sharing their salaries with each other,\n"
            "And they found some were paid more than others at the same level.\n"
            "More often than not, the women are paid less than men in equal roles.\n"
            "You didn't decide on their pay, but you could fix your predecessor's mistakes.",
            {
                {"Bring up everyone's pay in line with each other.", 15, 5, 0, 0, -10},
                {"Reduce everyone's pay to make everyone equal.", -15, -5, 0, 0, 10},
                {"Do nothing.", -10, 0, 0, 0, 0},
            }
        ),
        Event(
            "The previous boss promised the paperclip prices would stay static for the next 5 years.\n"
            "In hindsight that was a stupid promise, and you've got to fix his mistake.\n"
            "Prices of all the raw materials and factory running costs are going up.\n"
            "Do you raise the prices?",
            {
                {"I didn't make the promise, we can't afford this.", 0, 0, -10, -5, 15},
                {"A promise is a promise, we can't disapoint all our customers.", 0, 0, 10, 5, -15},
            }
        ),
        Event(
            "The average rent in the office's area is increasing,\n"
            "And employees are complaining about struggling to afford rent.\n"
            "Other companies are raising wages,\n"
            "And the board is woried we'll lose some paperclip manufacture talent.",
            {
                {"Raise the wages.", 10, 0, 0, 5, -10},
                {"Do nothing.", -5, 0, 0, -5, 0},
            }
        ),
        Event(
            "A study was done into various paperclip manufacturers,\n"
            "And our paperclips had a 10% failure rate.\n"
            "The board are saying this is just unnacceptable.\n"
            "You could commit to raising quality, but people are gonna buy your paperclips anyway.",
            {
                {"Launch an internal paperclip quality investigation.", -5, -5, 20, 5, -10},
                {"Do nothing, people will soon forget this study.", 0, 0, -10, -5, 0},
            }
        ),
        Event(
            "One of our factories overseas was found to be relying on child labour.\n"
            "The press made a big thing of this, but every other paperclip company does this.\n"
            "You could become the better company here, and stop this.\n"
            "Or you could dilute the negative press against you...",
            {
                {"Stop this. Child labour is unnacceptable.", 0, 0, 15, 0, -10},
                {"Pay for some articles uncovering other companies' child labour in paperclip manufacture.", 0, 0, -5, 0, -5},
                {"Do nothing, the press will move on.", 0, 0, -15, -5, -5},
            }
        ),
        Event(
            "Some of the board is suggesting we are out of touch with the next generation of paperclip enjoyers.\n"
            "Somebody brought up YouTube or TikTok as a solution to this.\n"
            "Plenty of companies have big success on these platforms,\n"
            "And this could solidify your position in the market.",
            {
                {"Create a TikTok account in the style of many small businesses.", 0, 0, 15, 10, 10},
                {"Create a corporate feeling YouTube account.", 0, 0, -5, 15, 5},
                {"Collaborate with a well known tech YouTuber giving them a tour.", 0, 0, 10, 10, 5},
                {"Do nothing, we don't need social media to survive.", 0, 0, 0, -5, -5},
            }
        ),
        Event(
            "A few recent batches of paperclips had a 90% failure rate.\n"
            "We can contact the customers who recieved this batch and refund them.\n"
            "There is a legal loophole that means we don't necessarily *have* to.\n"
            "And this would cost a significant amount to sort out.",
            {
                {"Refund them, we have a duty to supply working paperclips.", 0, 0, 20, 0, -15},
                {"Don't reach out, but if any companies contact us refund them.", 0, 0, 10, 0, -5},
                {"Do nothing, why do more than what we legally have to?", 0, 0, -10, 0, 0},
            }
        ),
        Event(
            "The workers want to join a union.\n"
            "You know exactly who the organisers are.\n"
            "The board are saying you should threaten to fire them,\n"
            "Either way, the board need something doing.",
            {
                {"Threaten the organisers.", -20, 0, 0, 20, 0},
                {"Send out flyers containing 'real facts' discouraging union membership.", -10, 0, 0, 10, 0},
                {"Do nothing, unions are part of a healthy worker-employer relationship.", 20, 0, -10, 0, 0},
            }
        ),
    };

    eventsInDay = events.size();
}
