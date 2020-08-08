#include "Simulation.h"

Simulation::Simulation() : world(100, 65), render(window, world, gui), gui(*this, world, render){
    render.initButtonsName();
    gui.setSnake(world.getGuiSnakePtr());
}

void Simulation::start(){
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            switch (event.type){
                case sf::Event::Closed:
                    window.close();
                break;
                case sf::Event::MouseWheelMoved:
                    if (event.mouseWheel.delta == 1){
                        render.changeZoom(render::Up);
                    }
                    else{
                        render.changeZoom(render::Down);
                    }
                break;
                case sf::Event::GainedFocus:
                    focusOnWindow = true;
                break;
                case sf::Event::LostFocus:
                    focusOnWindow = false;
                break;
                case sf::Event::Resized:
                    window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                    render.updateSizeWindow();
                break;
                case sf::Event::MouseButtonPressed:{
                    bool leftClick;
                    if (event.mouseButton.button == sf::Mouse::Left){
                        leftClick = true;
                    }
                    else{
                        leftClick = false;
                    }
                    sf::Vector2i cursorClick = sf::Mouse::getPosition(window);
                    XY xy = render.getXYSquare(static_cast<XY>(cursorClick));
                    gui.click((XY)cursorClick, leftClick);
                    world.setGuiWatch(xy);
                }
                break;
                default:;
            }
        }
        if (focusOnWindow){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                render.shiftDir(render::Up);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                render.shiftDir(render::Right);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                render.shiftDir(render::Down);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                render.shiftDir(render::Left);
            }
            static bool space = 0;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                if (space == false)
                    simulation = !simulation;
                space = true;
            }
            else{
                space = false;
            }
        }

        //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (simulation){
            world.update();
        }

        gui.update();

        sf::Vector2i cursor = sf::Mouse::getPosition(window);
        XY cursorSquare = render.getXYSquare(cursor);
        render.render(cursorSquare);

        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

void Simulation::stop(){
    simulation = false;
}

void Simulation::shutdown(){
    this->~Simulation();
}

void Simulation::invertSimulation(){
    simulation = !simulation;
}

XY Simulation::getWindowSize(){return window.getSize();}

int Simulation::getDelay(){return delay;};

void Simulation::changeDelay(int delayUp){
    if (delay + delayUp <= 0) delay = 0;
    else delay = delay + delayUp;
}

Simulation::~Simulation(){

}
