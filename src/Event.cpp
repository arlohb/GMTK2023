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
    };
}
