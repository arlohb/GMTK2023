#pragma once

#include <string>
#include <vector>

class EventOption {
    public:
        std::string text;

        float workerHappiness;
        float productivity;
        float customerSatisfaction;
        float boardConfidence;
        float money;
};

class Event {
    public:
        std::string text;

        std::vector<EventOption> options;

        Event(std::string text, std::vector<EventOption> options):
            text(text),
            options(options) {}
};
