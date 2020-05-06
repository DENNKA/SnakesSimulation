#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <chrono>   //sleep
#include <thread>

#include "World.h"
#include "Gui.h"
#include "Render.h"

class Simulation{
    public:
        Simulation();
        void start();
        void stop();
        void shutdown();
        ~Simulation();
    private:
        bool simulation = false;
        sf::RenderWindow window;
        World world;
        render::Render render;
        Gui gui;
        bool focusOnWindow = true;
};

#endif // SIMULATION_H_INCLUDED
