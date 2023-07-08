#pragma once

#include "rl.h"
#include <optional>
#include "Event.h"

enum class State {
    Playing,
    End,
};

class Game {
    public:
        Game(int width, int height, rl::Window& window);

        ///////////////////////////////
        ///         Window          ///
        ///////////////////////////////

        int width;
        int height;
        rl::Window& window;

        State state = State::Playing;

        /// Returns true if game exited
        bool Loop();

        void DrawBackground();

        ///////////////////////////////
        ///         Assets          ///
        ///////////////////////////////

        std::string baseAssetPath;
        std::string AssetPath(std::string name);

        rl::Texture paintingTex;
        rl::Texture windowTex;
        rl::Texture wallTex;
        rl::Texture clockTex;
        rl::Texture hourHandTex;
        rl::Texture minHandTex;

        ///////////////////////////////
        ///         Meters          ///
        ///////////////////////////////

        // All these are between 0 and 100

        const int metersCount = 5;
        float workerHappiness = 50;
        float productivity = 50;
        float customerSatisfaction = 50;
        float boardConfidence = 50;
        float money = 50;

        void ClampMeters();
        void DrawMeters();

        ///////////////////////////////
        ///          Day            ///
        ///////////////////////////////

        // The day goes from 9:00 to 17:00,
        const int hoursInDay = 8;

        const int eventsInDay = 20;

        // Progress goes from 0 to 100
        float progress = 0;
        
        void DrawDay();

        ///////////////////////////////
        ///         Events          ///
        ///////////////////////////////

        std::vector<Event> events;

        // Can't use a ref here
        std::optional<Event*> currentEvent;

        /// This set currentEvent to a new event
        void NewEvent();
        /// This draws the currentEvent if it exists
        void DrawEvent();
        void ApplyEventOption(EventOption& option);

        ///////////////////////////////
        ///        End game         ///
        ///////////////////////////////

        bool won = false;
        std::string endMsg;
        void DrawEnd();
        void CheckEndGame();
};

