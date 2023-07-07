#pragma once

#include "rl.h";

class Game {
    public:
        Game(int width, int height, rl::Window& window);

        /// Clamp all the meters between 0 and 100
        void ClampMeters();
        /// Draw the meters to the screen
        void DrawMeters();

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
};

