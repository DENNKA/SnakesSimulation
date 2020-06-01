#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H

#include "XY.h"
#include "World.h"

class Simulation;
namespace render{
    class Render;
}

class GuiComponent{
    public:
        GuiComponent(Simulation& simulation, World& world, render::Render& render, XY xy, XY size, std::string name, XY xyName, int fontSize);
        XY getXY();
        XY getSize();
        int getFontSize();
        std::string getName();
        XY getXYName();
    protected:
        Simulation& simulation;
        World& world;
        render::Render& render;
        XY xy;
        XY size;
        std::string name;
        XY xyName;
        int fontSize;
        bool visible;
};

#endif // GUICOMPONENT_H
