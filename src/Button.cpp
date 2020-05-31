#include "Button.h"
#include "Simulation.h"

Button::Button(Simulation& simulation, World& world, void (Button::*action)(bool leftClick), XY xy, XY size, std::string name, XY xyName) : GuiComponent(simulation, world, xy, size, name, xyName), action(action){
    //this->action = &Button::invertSimulation;
    //void (Button::*x)(bool leftClick) = &Button::invertSimulation;
}

void Button::click(bool leftClick){
    (this->*action)(leftClick);
}

void Button::invertSimulation([[maybe_unused]] bool leftClick){
    simulation.invertSimulation();
}

void Button::upFoodPerTick([[maybe_unused]] bool leftClick){
    if (leftClick) world.changeFoodPerTick(1);
    else world.changeFoodPerTick(20);
}

void Button::DownFoodPerTick([[maybe_unused]] bool leftClick){
    if (leftClick) world.changeFoodPerTick(-1);
    else world.changeFoodPerTick(-20);
}
