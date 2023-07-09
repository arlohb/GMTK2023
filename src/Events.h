#pragma once

#include "Assets.h"
#include "Meters.h"
#include <optional>
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

class Events {
    public:
        Events();

        int eventsInDay;

        std::vector<Event> events;

        std::optional<Event> current;

        void Next();
        void Draw(Meters& meters, Assets& assets, const int width, const int height, bool interactable);
        void ApplyOption(Meters& meters, EventOption& option);
};

