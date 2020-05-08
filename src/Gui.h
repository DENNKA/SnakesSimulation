#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <vector>

#include "World.h"
#include "Button.h"

class Simulation;

enum class guiWindow{
    simulation
};

class Gui{
    public:
        Gui(Simulation& simulation, World& world);
        void click(XY cursor, bool leftClick);
        unsigned getButtonsAmount();
        XY getXYButton(unsigned int i);
        XY getSizeButton(unsigned int i);
        XY getSize();
    private:
        XY size;
        XY posNextButton;
        void addBigButton(void (Button::*action)(bool leftClick));
        void addSmallButton(void (Button::*action)(bool leftClick));
        void updateSize();
        std::vector<Button> buttons;
        Simulation& simulation;
        World& world;
};

#endif // GUI_H_INCLUDED
