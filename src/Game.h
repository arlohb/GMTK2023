#pragma once

#include "rl.h"
#include <optional>
#include "Event.h"

class Game {
    public:
        Game(int width, int height, rl::Window& window);

        ///////////////////////////////
        ///         Window          ///
        ///////////////////////////////

        int width;
        int height;
        rl::Window& window;

        bool isRunning = true;

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

        std::string endMsg;
        void DrawEnd();
        void CheckEndGame();
};

