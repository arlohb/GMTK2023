#pragma once

#include "rl.h";

class Game {
    public:
        Game(int width, int height, rl::Window& window);

        void Loop();

        int width;
        int height;
        rl::Window& window;
};

