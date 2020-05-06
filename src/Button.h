#ifndef BUTTON_H
#define BUTTON_H

#include "XY.h"

class Button{
    public:
        Button();
        void click();
    private:
        XY xy;
        int width, height;
        bool visible;
};

#endif // BUTTON_H
