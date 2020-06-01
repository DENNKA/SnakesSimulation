#ifndef BUTTON_H
#define BUTTON_H

#include "GuiComponent.h"
#include "XY.h"
#include "World.h"
#include "Text.h"

class Simulation;

class Button : public GuiComponent{
    public:
        Button(Simulation& simulation, World& world, render::Render& render, void (Button::*action)(bool leftClick), XY xy, XY size, std::string name, XY xyName, int fontSize, Text* text = nullptr);
        void click(bool leftClick);

        void invertSimulation(bool leftClick);
        void upFoodPerTick(bool leftClick);
        void downFoodPerTick(bool leftClick);
    private:
        void (Button::*action)(bool leftClick);
        Text* text;
        bool invert = false;
};

#endif // BUTTON_H
