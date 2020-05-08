#ifndef BUTTON_H
#define BUTTON_H

#include "XY.h"
#include "World.h"

class Simulation;

class Button{
    public:
        Button(Simulation& simulation, World& world, void (Button::*action)(bool leftClick), XY xy, XY size, std::string name, XY xyName);
        void click(bool leftClick);
        XY getXY();
        XY getSize();
        std::string getName();
        XY getXYName();

        void invertSimulation(bool leftClick);
        void upFoodPerTick(bool leftClick);
        void DownFoodPerTick(bool leftClick);
    private:
        Simulation& simulation;
        World& world;
        void (Button::*action)(bool leftClick);
        std::string name;
        XY xy;
        XY size;
        XY xyName;
        bool visible;
        bool invert = false;
};

#endif // BUTTON_H
