#include "Gui.h"
#include "Simulation.h"
#include "Render.h"

Gui::Gui(Simulation& simulation, World& world, render::Render& render) : simulation(simulation), world(world), render(render){
    xyGui.x = 0;
    xyGui.y = simulation.getWindowSize().y - 60;
    nextPos = xyGui;
    #define lambda(code) [&simulation, &world] ([[maybe_unused]] bool leftClick) mutable{code;}
    #define lambdaText(code) [&simulation, &world] () mutable{code;}
    #define addTextAndTwoButtons(text, lambda1, lambda2, lamdaText1) \
        addText(lamdaText1, text); \
        addButton(small, lambda1, "+" + std::string(text),  &texts.back()); \
        addButton(small, lambda2, "-" + std::string(text),  &texts.back());

    // init buttons
    addButton(big, lambda(simulation.invertSimulation()), "Start");
    addTextAndTwoButtons(
        "food",
        lambda(if (leftClick) world.changeFoodPerTick(1); else world.changeFoodPerTick(20);),
        lambda(if (leftClick) world.changeFoodPerTick(-1); else world.changeFoodPerTick(-20);),
        lambdaText(return std::to_string(world.getFoodPerTick()))
    );
    addTextAndTwoButtons(
        "delay",
        lambda(if (leftClick) simulation.changeDelay(5); else simulation.changeDelay(10);),
        lambda(if (leftClick) simulation.changeDelay(-5); else simulation.changeDelay(-10);),
        lambdaText(return std::to_string(simulation.getDelay()))
    );

    #undef addTextAndTwoButtons
    #undef lambda
    #undef lambdaText

    //updateSize();
}

void Gui::setSnake(Snake** snakePtr2){this->snakePtr = snakePtr2;}

void Gui::update(){
    for (auto& it : texts){
        it.update();
    }
    if (snakePtr && *snakePtr){
        Snake& snake = **snakePtr;

    }

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

std::list<Text>& Gui::getTexts(){return texts;}

std::vector<Button>& Gui::getButtons(){return buttons;}

XY Gui::getSize(){return size;}

void Gui::addText(const std::function<std::string(void)> watch, std::string name){
    XY xy = xyGui;
    xy.x = nextPos.x + sizeBigButton / 10;
    xy.y += sizeBigButton / 4;
    texts.push_back(Text(simulation, world, render, watch, xy, size, name, xy, fontSize));
    nextPos.x += sizeBigButton;
}

void Gui::addButton(ButtonType buttonType, const std::function<void(bool)> action, std::string name, Text* text){
    XY sizeButton;
    XY positionText;
    //setting up size and position
    switch (buttonType){
        case big:
            if (smallButtonNubmer == 1){
                nextPos.y -= sizeButton.y + buttonsSpace;
                nextPos.x += widthOneSymbol * prevName.size();
            }
            sizeButton = {sizeBigButton, sizeBigButton};
            positionText = {nextPos.x + sizeButton.x / 10, nextPos.y + sizeButton.y / 3};
        break;
        case small:
            const int sizeSmallButton = (sizeBigButton) / 2;
            sizeButton = {sizeSmallButton, sizeSmallButton};
            positionText = {nextPos.x + sizeButton.x, nextPos.y};
        break;
    }
    buttons.push_back(Button(simulation, world, render, action, nextPos, sizeButton, name, positionText, fontSize, text));
    //setup position next button
    switch (buttonType){
        case big:
            nextPos.x += sizeButton.x + buttonsSpace;
            smallButtonNubmer = 0;
        break;
        case small:
            if (smallButtonNubmer == 1){
                smallButtonNubmer = 0;
                nextPos.x += widthOneSymbol * std::max(name.size(), prevName.size());
                nextPos.y -= sizeButton.y + buttonsSpace;
            }
            else{
                smallButtonNubmer++;
                nextPos.y += sizeButton.y + buttonsSpace;
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
