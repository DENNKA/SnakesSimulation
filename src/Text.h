#ifndef TEXT_H
#define TEXT_H

#include <functional>

#include "GuiComponent.h"

class Text : public GuiComponent{
    public:
        Text(Simulation& simulation, World& world, render::Render& render, const std::function<std::string(void)> watch, XY xy, XY size, const std::string& name, XY xyName, int fontSize);
        void update();
        void updateFromButton();
        std::string getText();
        void setIdentifier(int identifier);

    protected:
        void updateText();
        const std::function<std::string(void)> watch;
        bool needUpdate;
        int identifier;
};

#endif // TEXT_H
