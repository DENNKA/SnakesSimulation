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
            void initButtonsName();
            void initTexts();   //TODO: one init func
            void render(XY cursorSquare);
            void renderWorld();
            void renderGui();
            void renderCursor(XY cursor);
            void renderCursorXYSquare(XY cursorSquare);
            void renderTexts();
            void updateSizeWindow();
            void updateOneText(int i, const std::string& string);
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

            typedef unsigned char ubyte;
            template <typename T>
            struct Color4{
                Color4(){};
                Color4(T red, T green, T blue, T alpha = 255){colors[0] = red; colors[1] = green; colors[2] = blue; colors[3] = alpha;}
                T colors[4];
            };
            typedef Color4<ubyte> Color4ub;
            Color4ub colorSnake = Color4ub(0, 240, 0);
            Color4ub colorWall = Color4ub(230, 0, 0);
            Color4ub colorFood = Color4ub(93, 161, 48, 100);
            Color4ub colorDead = Color4ub(230, 230, 100);
            Color4ub colorEgg = Color4ub(255, 255, 255);
            Color4ub colorButton = Color4ub(41, 48, 51);
            Color4ub colorCursor = Color4ub(255, 255, 255, 125);

            std::vector<sf::Text> texts;

            std::vector<sf::Text> buttonsText;
            sf::Font font;

            sf::RenderWindow& window;
            World& world;
            Gui& gui;
    };
}

#endif // RENDER_H_INCLUDED
