#ifndef BUTTON_H
#define BUTTON_H

#include "XY.h"

class Button{
    public:
        Button(void (*action)(bool leftClick));
        void click(bool leftClick);
    private:
        void (*action)(bool leftClick);
        XY xy;
        int width, height;
        bool visible;
};

#endif // BUTTON_H
