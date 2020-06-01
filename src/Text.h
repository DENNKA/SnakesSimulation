#ifndef TEXT_H
#define TEXT_H

#include "GuiComponent.h"

class Text : public GuiComponent{
    public:
        Text(Simulation& simulation, World& world, render::Render& render, int (Text::*watch)(), XY xy, XY size, const std::string& name, XY xyName, int fontSize);
        void update();
        void updateFromButton();
        std::string getText();
        void setIdentifier(int identifier);

        int watchFoodPerTick();
    protected:
        void updateText();
        int (Text::*watch)();
        bool needUpdate;
        int identifier;
};

#endif // TEXT_H
