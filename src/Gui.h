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
        std::string getNameButton(unsigned int i);
        XY getXYNameButton(unsigned int i);
        XY getSize();
        enum ButtonType{
            big,
            small
        };
    private:
        void addButton(ButtonType buttonType, void (Button::*action)(bool leftClick), std::string name);
        void updateSize();
        const int sizeBigButton = 60;
        const int widthOneSymbol = 17;
        const int buttonsSpace = 3;
        std::string prevName;
        int smallButtonNubmer = 0;
        XY size;
        XY posNextButton;
        std::vector<Button> buttons;
        Simulation& simulation;
        World& world;
};

#endif // GUI_H_INCLUDED
