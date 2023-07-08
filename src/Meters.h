#pragma once

#include "State.h"
#include <string>
#include <utility>

class Meters {
    public:
        // All these are between 0 and 100

        float progress = 0;

        const int count = 5;
        float workerHappiness = 30;
        float productivity = 50;
        float customerSatisfaction = 60;
        float boardConfidence = 30;
        float money = 50;

        void Clamp();
        void Draw(const int height);
        std::pair<std::string, State> CheckEnd();
};

