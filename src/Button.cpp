#include "Button.h"
#include "Simulation.h"

Button::Button(Simulation& simulation, World& world, void (Button::*action)(bool leftClick), XY xy, XY size, std::string name, XY xyName) : simulation(simulation), world(world), action(action), xy(xy), size(size), name(name), xyName(xyName){
    //this->action = &Button::invertSimulation;
    //void (Button::*x)(bool leftClick) = &Button::invertSimulation;
}

void Button::click(bool leftClick){
    (this->*action)(leftClick);
}

XY Button::getXY(){return xy;}

XY Button::getSize(){return size;}

std::string Button::getName(){return name;}

XY Button::getXYName(){return xyName;}

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
