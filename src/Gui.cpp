#include "Gui.h"
#include "Simulation.h"

Gui::Gui(Simulation& simulation, World& world) : simulation(simulation), world(world){
    pos.x = 0;
    pos.y = simulation.getWindowSize().y - 60;
    addBigButton();
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

void Gui::addBigButton(){
    buttons.push_back(Button(simulation, world, &Button::invertSimulation, pos, XY(60, 60)));
}

void Gui::addSmallButton(){

}
