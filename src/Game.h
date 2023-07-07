#pragma once

#include "rl.h"
#include <optional>
#include "Event.h"

class Game {
    public:
        Game(int width, int height, rl::Window& window);

        /// Clamp all the meters between 0 and 100
        void ClampMeters();
        /// Draw the meters to the screen
        void DrawMeters();

        /// This set currentEvent to a new event
        void NewEvent();
        /// This draws the currentEvent if it exists
        void DrawEvent();
        void ApplyEventOption(EventOption& option);

        void Loop();

        int width;
        int height;
        rl::Window& window;

        /// All these are between 0 and 100
        const int metersCount = 5;
        float workerHappiness = 50;
        float productivity = 50;
        float customerSatisfaction = 50;
        float boardConfidence = 50;
        float money = 50;

        std::vector<Event> events;

        // Can't use a ref here
        std::optional<Event*> currentEvent;
};

