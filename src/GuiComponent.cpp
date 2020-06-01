#include "GuiComponent.h"
#include "Render.h"

GuiComponent::GuiComponent(Simulation& simulation, World& world, render::Render& render, XY xy, XY size, std::string name, XY xyName, int fontSize) : simulation(simulation), world(world), render(render), xy(xy), size(size), name(name), xyName(xyName), fontSize(fontSize){

}

XY GuiComponent::getXY(){return xy;}

XY GuiComponent::getSize(){return size;}

int GuiComponent::getFontSize(){return fontSize;}

std::string GuiComponent::getName(){return name;}

XY GuiComponent::getXYName(){return xyName;}
