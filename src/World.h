#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>
#include <list>
#include <cstdlib>  //rand()
#include <ctime>

#include "Snake.h"
#include "Defines.h"

#define FILLRESETPTR(x,y) x.symbol = y; x.snake = NULL

enum TileType{
    none = ' ',
    snake = 's',
    food = 'f',
    wall = '0',
    egg = 'e',
    dead = 'd'
};

struct Tile{
    unsigned char symbol;
    Snake* snake;
};

class World{
    public:
        World(int worldSizeX, int worldSizeY);
        void setSize(int worldSizeX, int worldSizeY);
        XY getSize();
        void generate();    //generate walls
        void generateFood();
        void update();
        void flash();   //clear food and snakes on map
        void setChar(XY& xy, unsigned char symbol);
        void setChar(XY& xy, Snake* snake);
        unsigned char getChar(XY xy);   //if xy don't in bounds throw exception
        unsigned char getChar(int x, int y);
        unsigned char getCharNoThrow(XY xy);    //if xy don't in bounds return none (0)
        void addSnake();
        Snake* getSnake(XY xy);
        void setGuiWatch(XY xy);
        Snake** getGuiSnakePtr();
        int boundsCheck(XY xy); //return 1 when in xy in bounds
        void addEgg(XY xy, int generation, std::shared_ptr<Genes> genes);
        void changeFoodPerTick(int up);
        int getFoodPerTick();
    private:
        std::vector<std::string> test();
        XY size;
        std::vector<std::vector<Tile>> world;
        std::list<Snake> snakes;
        std::list<Snake> snakesSavedForGui;
        Snake* guiSnakePtr = nullptr;
        int foodPerTick = 1;
        int foodTicks = 0;
};

#endif // WORLD_H_INCLUDED
