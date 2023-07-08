#pragma once

#include "Assets.h"
#include "Meters.h"
#include "rl.h"
#include <optional>
#include "Events.h"

class Game {
    public:
        Game(int width, int height, rl::Window& window);

        // The day goes from 9:00 to 17:00,
        const int hoursInDay = 8;

        int width;
        int height;
        rl::Window& window;

        State state = State::Intro;
        std::string endMsg;

        Assets assets;
        Meters meters;
        Events events;

        /// Returns true if game exited
        bool Loop();

        void DrawIntro();
        void DrawBackground();
        void DrawDay();
        bool DrawEventBtn();
        void DrawEnd();
};

