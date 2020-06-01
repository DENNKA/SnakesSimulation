#include "Text.h"
#include "Render.h"

Text::Text(Simulation& simulation, World& world, render::Render& render,
           int (Text::*watch)(), XY xy, XY size, const std::string& name,
           XY xyName, int fontSize) :
           GuiComponent(simulation, world, render, xy, size, name, xyName, fontSize),
           watch(watch){

}

void Text::update(){
    if (needUpdate){
        updateText();
    }
}

void Text::updateFromButton(){
    updateText();
}

std::string Text::getText(){
    return std::to_string((this->*watch)());
}

void Text::setIdentifier(int identifier){this->identifier = identifier;}

int Text::watchFoodPerTick(){return world.getFoodPerTick();}

void Text::updateText(){
    render.updateOneText(identifier, getText());
}
