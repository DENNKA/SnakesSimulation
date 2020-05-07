#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "World.h"
#include "Gui.h"

namespace render{

    enum Dir{
        Up,
        Right,
        Down,
        Left
    };

    class Render{
        public:
            Render(sf::RenderWindow& window, World& world, Gui& gui);
            void render();
            void renderButtons();
            void renderCursor(XY cursor);
            void updateSizeWindow();
            void setSizes(int sizeSquare, int sizeSpace);
            void shift(int shiftX, int shiftY);
            void shiftDir(Dir dir);
            //XY getShift();
            void changeZoom(Dir dir);
            XY getXYSquare(XY cursor);
        private:
            int sizeSquareDefault = 15, sizeSpaceDefault = 3;
            int sizeSquare = sizeSquareDefault, sizeSpace = sizeSpaceDefault;
            float shiftX = 0, shiftY = 0;
            float shiftFactor = 10;
            double zoom = 1.0;
            double zoomFactor = 0.05;
            sf::RenderWindow& window;
            World& world;
            Gui& gui;
    };
}

#endif // RENDER_H_INCLUDED
