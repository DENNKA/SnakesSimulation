#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <vector>

#include "World.h"
#include "Button.h"
#include "Text.h"

class Simulation;
namespace render{
    class Render;
}

enum class guiWindow{
    simulation
};

class Gui{
    public:
        Gui(Simulation& simulation, World& world, render::Render& render);
        void click(XY cursor, bool leftClick);
        std::list<Text>& getTexts();  //don't use vector because pointers become invalidate
        std::vector<Button>& getButtons();
        XY getSize();
        enum ButtonType{
            big,
            small
        };
    private:
        void addText(int (Text::*watch)(), std::string name);
        void addButton(ButtonType buttonType, void (Button::*action)(bool leftClick), std::string name, Text* text = nullptr);
        void updateSize();
        int fontSize = 20;
        const int sizeBigButton = 60;
        const int widthOneSymbol = 17;
        const int buttonsSpace = 3;
        std::string prevName;
        int smallButtonNubmer = 0;
        XY size;
        XY nextPos;
        XY xyGui;
        std::vector<Button> buttons;
        std::list<Text> texts;
        Simulation& simulation;
        World& world;
        render::Render& render;
};

#endif // GUI_H_INCLUDED
