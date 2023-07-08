#include "Event.h"

std::vector<Event> CreateEvents() {
    return {
        Event("Invest in A or B?", {
            {"A", 0, 0, 0, 20, -10},
            {"B", 0, 0, 0, -10, 20},
        }),
    };
}
