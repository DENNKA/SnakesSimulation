#include "Button.h"
#include "Simulation.h"

Button::Button(Simulation& simulation, World& world, render::Render& render, const std::function<void(bool)> action, XY xy, XY size, std::string name, XY xyName, int fontSize, Text* text) : GuiComponent(simulation, world, render, xy, size, name, xyName, fontSize), action(action), text(text){
    //this->action = &Button::invertSimulation;
    //void (Button::*x)(bool leftClick) = &Button::invertSimulation;
}

void Button::click(bool leftClick){
    action(leftClick);
    if (text){
        text->updateFromButton();
    }
}
