#include "Gui.h"
#include "Simulation.h"

Gui::Gui(Simulation& simulation, World& world) : simulation(simulation), world(world){
    posNextButton.x = 0;
    posNextButton.y = simulation.getWindowSize().y - 60;
    addButton(big, &Button::invertSimulation, "Start");
    addButton(small, &Button::upFoodPerTick, "+food");
    addButton(small, &Button::DownFoodPerTick, "-food");
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

std::string Gui::getNameButton(unsigned int i){return buttons[i].getName();}

XY Gui::getXYNameButton(unsigned int i){return buttons[i].getXYName();}

XY Gui::getSize(){return size;}

void Gui::addButton(ButtonType buttonType, void (Button::*action)(bool leftClick), std::string name){
    XY sizeButton;
    XY positionText;
    //setting up size and position
    switch (buttonType){
        case big:
            sizeButton = {sizeBigButton, sizeBigButton};
            positionText = {posNextButton.x + sizeButton.x / 10, posNextButton.y + sizeButton.y / 3};
        break;
        case small:
            const int sizeSmallButton = (sizeBigButton) / 2;
            sizeButton = {sizeSmallButton, sizeSmallButton};
            positionText = {posNextButton.x + sizeButton.x, posNextButton.y};
        break;
    }
    buttons.push_back(Button(simulation, world, action, posNextButton, sizeButton, name, positionText));
    //setup position next button
    switch (buttonType){
        case big:
            posNextButton.x += sizeButton.x + buttonsSpace;
            smallButtonNubmer = 0;
        break;
        case small:
            if (smallButtonNubmer == 1){
                smallButtonNubmer = 0;
                posNextButton.x += widthOneSymbol * std::max(name.size(), prevName.size());
                posNextButton.y -= sizeButton.y + buttonsSpace;
            }
            else{
                smallButtonNubmer++;
                posNextButton.y += sizeButton.y + buttonsSpace;
            }
        break;
    }
    prevName = name;
}

void Gui::updateSize(){
    for (auto &it : buttons){
        XY xy = it.getXY() + it.getSize();
        size.x = xy.x > size.x ? xy.x : size.x;
        size.y = it.getSize().y > size.y ? it.getSize().y : size.y; //TODO: need to make this better
    }
}
