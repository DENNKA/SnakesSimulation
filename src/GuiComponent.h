#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H

#include "XY.h"
#include "World.h"

class Simulation;

class GuiComponent{
    public:
        GuiComponent(Simulation& simulation, World& world, XY xy, XY size, std::string name, XY xyName);
        XY getXY();
        XY getSize();
        std::string getName();
        XY getXYName();
    protected:
        Simulation& simulation;
        World& world;
        XY xy;
        XY size;
        std::string name;
        XY xyName;
        int fontSize;
        bool visible;
};

#endif // GUICOMPONENT_H
