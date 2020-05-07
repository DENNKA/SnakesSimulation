#include "Button.h"
#include "Simulation.h"

Button::Button(Simulation& simulation, World& world, void (Button::*action)(bool leftClick), XY xy, XY size) : simulation(simulation), world(world), action(action), xy(xy), size(size){
    //this->action = &Button::invertSimulation;
    //void (Button::*x)(bool leftClick) = &Button::invertSimulation;
}

void Button::click(bool leftClick){
    (this->*action)(leftClick);
}

XY Button::getXY(){return xy;}

XY Button::getSize(){return size;}

void Button::invertSimulation(bool leftClick){
    simulation.invertSimulation();
}
