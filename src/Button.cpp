#include "Button.h"
#include "Simulation.h"

Button::Button(Simulation& simulation, World& world, render::Render& render, void (Button::*action)(bool leftClick), XY xy, XY size, std::string name, XY xyName, int fontSize, Text* text) : GuiComponent(simulation, world, render, xy, size, name, xyName, fontSize), action(action), text(text){
    //this->action = &Button::invertSimulation;
    //void (Button::*x)(bool leftClick) = &Button::invertSimulation;
}

void Button::click(bool leftClick){
    (this->*action)(leftClick);
    if (text){
        text->updateFromButton();
    }
}

void Button::invertSimulation([[maybe_unused]] bool leftClick){
    simulation.invertSimulation();
}

void Button::upFoodPerTick([[maybe_unused]] bool leftClick){
    if (leftClick) world.changeFoodPerTick(1);
    else world.changeFoodPerTick(20);
}

void Button::downFoodPerTick([[maybe_unused]] bool leftClick){
    if (leftClick) world.changeFoodPerTick(-1);
    else world.changeFoodPerTick(-20);
}
