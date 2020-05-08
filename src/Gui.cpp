#include "Gui.h"
#include "Simulation.h"

Gui::Gui(Simulation& simulation, World& world) : simulation(simulation), world(world){
    posNextButton.x = 0;
    posNextButton.y = simulation.getWindowSize().y - 60;
    addBigButton(&Button::invertSimulation);
    //updateSize();
}

void Gui::click(XY cursor, bool leftClick){
    for (auto &it : buttons){
        const XY& xy = it.getXY();
        const XY& size = it.getSize();
        if (cursor.x >= xy.x && cursor.x <= xy.x + size.x && cursor.y >= xy.y && cursor.y <= xy.y + size.y){
            it.click(leftClick);
        }
    }
}

unsigned Gui::getButtonsAmount(){return buttons.size();}

XY Gui::getXYButton(unsigned int i){return buttons[i].getXY();}

XY Gui::getSizeButton(unsigned int i){return buttons[i].getSize();}

XY Gui::getSize(){return size;}

void Gui::addBigButton(void (Button::*action)(bool leftClick)){
    buttons.push_back(Button(simulation, world, action, posNextButton, XY(60, 60)));
    posNextButton.x += 60;
}

void Gui::addSmallButton(void (Button::*action)(bool leftClick)){

}

void Gui::updateSize(){
    for (auto &it : buttons){
        XY xy = it.getXY() + it.getSize();
        size.x = xy.x > size.x ? xy.x : size.x;
        size.y = it.getSize().y > size.y ? it.getSize().y : size.y; //TODO: need to make this better
    }
}
