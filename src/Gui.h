#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <vector>

#include "Button.h"

enum class guiWindow{
    simulation
};

class Gui{
    public:
        Gui();
        void addButton();
    private:
        std::vector<Button> buttons;
};

#endif // GUI_H_INCLUDED
