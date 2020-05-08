#ifndef BUTTON_H
#define BUTTON_H

#include "XY.h"
#include "World.h"

class Simulation;

class Button{
    public:
        Button(Simulation& simulation, World& world, void (Button::*action)(bool leftClick), XY xy, XY size);
        void click(bool leftClick);
        XY getXY();
        XY getSize();

        void invertSimulation(bool leftClick);
    private:
        Simulation& simulation;
        World& world;
        void (Button::*action)(bool leftClick);
        XY xy;
        XY size;
        bool visible;
        bool invert = false;
};

#endif // BUTTON_H
