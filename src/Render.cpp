#include "Render.h"
#include <string>

namespace render{

    Render::Render(sf::RenderWindow& window, World& world, Gui& gui) : window(window), world(world), gui(gui){
        /*sf::ContextSettings settings;
        settings.depthBits = 24;
        settings.stencilBits = 8;
        settings.antialiasingLevel = 4;
        settings.majorVersion = 3;
        settings.minorVersion = 0;*/
        window.create(sf::VideoMode(800, 600), "Snakes simulation", sf::Style::Default/*, settings*/);
        glOrtho(0.0, window.getSize().x, window.getSize().y, 0.0, 1.0, -1.0);
        setSizes(sizeSquare,sizeSpace);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        if (!font.loadFromFile("fonts/arial.ttf")){
            std::cout<<"Font not exist";
            std::cin.get();
        }
    }

    void Render::initButtonsName(){
        buttonsText.reserve(gui.getButtonsAmount());
        for (int i = 0; i < gui.getButtonsAmount(); i++){
            sf::Text text;
            text.setFont(font);
            text.setString(gui.getNameButton(i));
            text.setPosition(gui.getXYNameButton(i).x, gui.getXYNameButton(i).y);
            text.setCharacterSize(characterSize);
            buttonsText.push_back(text);
        }
    }

    void Render::render(XY cursorSquare){
        renderWorld();
        renderCursorXYSquare(cursorSquare);
        renderGui();
        window.pushGLStates();  //sfml render
        renderTexts();
        window.popGLStates();
    }

    void Render::renderWorld(){
        glBegin(GL_QUADS);
        for (int i = 0; i < world.getSize().y; i++){
            for (int j = 0; j < world.getSize().x; j++){
                switch (world.getChar(XY(j,i))){
                    case none: continue;
                    case snake: glColor3f(0, 0.9, 0); break;
                    case wall: glColor3f(0.9, 0, 0); break;
                    case food: glColor3f(0.7, 0.7, 0.7); break;
                    case dead: glColor3f(0.94, 0.94, 0.4); break;
                    case egg: glColor3f(0.5, 0.4, 0.2); break;
                }
                glVertex2f(j * (sizeSquare + sizeSpace) + shiftX, i * (sizeSquare + sizeSpace) + shiftY);
                glVertex2f(j * (sizeSquare + sizeSpace) + shiftX + sizeSquare, i * (sizeSquare + sizeSpace) + shiftY);
                glVertex2f(j * (sizeSquare + sizeSpace) + shiftX + sizeSquare, i * (sizeSquare + sizeSpace) + shiftY + sizeSquare);
                glVertex2f(j * (sizeSquare + sizeSpace) + shiftX, i * (sizeSquare + sizeSpace) + shiftY + sizeSquare);
            }
        }
        glEnd();
    }

    void Render::renderGui(){
        glBegin(GL_QUADS);
        glColor3f(0.16, 0.19, 0.20);
        for (int i = 0; i < (int)gui.getButtonsAmount(); i++){
            const XY& xy = gui.getXYButton(i);
            const XY& size = gui.getSizeButton(i);
            glVertex2i(xy.x, xy.y);   //top left
            glVertex2i(xy.x + size.x, xy.y);   //top right
            glVertex2i(xy.x + size.x, xy.y + size.y);   //bottom right
            glVertex2i(xy.x, xy.y + size.y);   //bottom left
        }
        glEnd();
    }

    void Render::renderCursor(XY cursor){
        renderCursor(getXYSquare(cursor));
    }

    void Render::renderCursorXYSquare(XY cursorSquare){
        if (!world.boundsCheck(cursorSquare)) return;
        glBegin(GL_QUADS);
        glColor4f(1, 1, 1, 0.5);    //TODO: need normal way to definition color
        glVertex2f(cursorSquare.x * (sizeSquare + sizeSpace) + shiftX, cursorSquare.y * (sizeSquare + sizeSpace) + shiftY);
        glVertex2f(cursorSquare.x * (sizeSquare + sizeSpace) + shiftX + sizeSquare, cursorSquare.y * (sizeSquare + sizeSpace) + shiftY);
        glVertex2f(cursorSquare.x * (sizeSquare + sizeSpace) + shiftX + sizeSquare, cursorSquare.y * (sizeSquare + sizeSpace) + shiftY + sizeSquare);
        glVertex2f(cursorSquare.x * (sizeSquare + sizeSpace) + shiftX, cursorSquare.y * (sizeSquare + sizeSpace) + shiftY + sizeSquare);
        glEnd();
    }

    void Render::renderTexts(){
        for (auto& it : buttonsText){
            window.draw(it);
        }
    }

    void Render::updateSizeWindow(){
        glViewport(0, 0, window.getSize().x, window.getSize().y);
        //glOrtho(0.0, window.getSize().x, window.getSize().y, 0.0,1.0,-1.0);
    }

    void Render::setSizes(int sizeSquare, int sizeSpace){
        this->sizeSquare = sizeSquare;
        this->sizeSpace = sizeSpace;
    }

    void Render::shift(int shiftX, int shiftY){
        this->shiftX += shiftX;
        this->shiftY += shiftY;
    }

    void Render::shiftDir(Dir dir){
        switch (dir){
            case Up:
                shiftY += shiftFactor;
            break;
            case Right:
                shiftX -= shiftFactor;
            break;
            case Down:
                shiftY -= shiftFactor;
            break;
            case Left:
                shiftX += shiftFactor;
            break;
        }
    }

    //XY Render::getShift(){return XY(shiftX, shiftY);}

    void Render::changeZoom(Dir dir){
        //int invert;
        if (dir == Up){
            zoom += zoomFactor;
            //invert = -1;
        }
        else{
            if (dir == Down && zoom > zoomFactor * 2){
                zoom -= zoomFactor;
                //invert = 1;
            }
            else return; // !
        }
        setSizes(sizeSquareDefault * zoom, sizeSpaceDefault * zoom);
        //auto cursor = sf::Mouse::getPosition(window);
        //shift(invert * (cursor.x - window.getPosition().x / 2) / 5, invert * (cursor.y - window.getPosition().y / 2) / 5);
    }

    XY Render::getXYSquare(XY cursor){
        XY xy;
        /*if ((int)(cursor.x + sizeSquare / 2 - shiftY) % (sizeSquare + sizeSpace) > sizeSquare ||
            (int)(cursor.y + sizeSquare / 2 - shiftY) % (sizeSquare + sizeSpace) > sizeSquare){
            xy.x = -1, xy.y= -1;
            return xy;
        }*/
        xy.y = (cursor.y - shiftY) / (sizeSquare + sizeSpace);
        xy.x = (cursor.x - shiftX) / (sizeSquare + sizeSpace);
        return xy;
    }
}
