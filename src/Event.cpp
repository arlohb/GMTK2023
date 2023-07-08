#include "Event.h"

std::vector<Event> CreateEvents() {
    return {
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
    };
}
