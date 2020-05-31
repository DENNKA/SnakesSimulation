#ifndef BUTTON_H
#define BUTTON_H

#include "GuiComponent.h"
#include "XY.h"
#include "World.h"

class Simulation;

class Button : public GuiComponent{
    public:
        Button(Simulation& simulation, World& world, void (Button::*action)(bool leftClick), XY xy, XY size, std::string name, XY xyName);
        void click(bool leftClick);

        void invertSimulation(bool leftClick);
        void upFoodPerTick(bool leftClick);
        void DownFoodPerTick(bool leftClick);
    private:
        void (Button::*action)(bool leftClick);
        bool invert = false;
};

#endif // BUTTON_H
