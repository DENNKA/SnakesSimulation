#ifndef BUTTON_H
#define BUTTON_H

#include <functional>

#include "GuiComponent.h"
#include "XY.h"
#include "World.h"
#include "Text.h"

class Simulation;

class Button : public GuiComponent{
    public:
        Button(Simulation& simulation, World& world, render::Render& render, const std::function<void(bool)> action, XY xy, XY size, std::string name, XY xyName, int fontSize, Text* text = nullptr);
        void click(bool leftClick);
        
    private:
        const std::function<void(bool)> action;
        Text* text;
        bool invert = false;
};

#endif // BUTTON_H
