#pragma once

#include "rl.h"
#include <string>

class Assets {
    public:
        Assets();

        const std::string basePath = "../assets/";
        std::string Path(std::string name);

        rl::Texture painting;
        rl::Texture window;
        rl::Texture wall;
        rl::Texture clock;
        rl::Texture hourHand;
        rl::Texture minHand;
        rl::Texture nextEventBtn;
        rl::Texture tutorial;
        rl::Texture event;

        static rl::Rectangle TexRect(rl::Texture& tex);
};

