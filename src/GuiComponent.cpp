#include "GuiComponent.h"

GuiComponent::GuiComponent(Simulation& simulation, World& world, XY xy, XY size, std::string name, XY xyName) : simulation(simulation), world(world), xy(xy), size(size), name(name), xyName(xyName){

}

XY GuiComponent::getXY(){return xy;}

XY GuiComponent::getSize(){return size;}

std::string GuiComponent::getName(){return name;}

XY GuiComponent::getXYName(){return xyName;}
