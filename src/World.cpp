#include "World.h"
#include "Defines.h"

World::World(int worldSizeX, int worldSizeY){
    setSize(worldSizeX, worldSizeY);
    generate();
    #ifdef DEBUG
        auto errors = test();
        if (errors.size()){
            for (auto &it : errors){
                std::cout << it << std::endl;
            }
            std::cin.get();
        }
    #endif // DEBUG
    srand(time(NULL));

    int saturation = 10;
    int generation = 0;
    Sex sex = female;
    Genes genes;
    snakes.push_front(Snake(*this, XY(5,5), 5, saturation, generation, sex, genes));

    snakes.front().loadGenesFromFile("defaultGenes.txt");

    snakes.front().unloadGenesIntoFile("check.txt");
}

void World::setSize(int worldSizeX, int worldSizeY){
    size.x = worldSizeX, size.y = worldSizeY;
    world.resize(worldSizeY);
    for (auto &it : world){
        it.resize(worldSizeX);
    }
    for (auto &it1 : world){    //TODO: need move
        for (auto &it2 : it1){
            FILLRESETPTR(it2, none);
        }
    }

}

XY World::getSize(){return size;}

void World::generate(){
    for (int i = 0; i < size.y; i++){
        FILLRESETPTR(world[i][0], wall);
        FILLRESETPTR(world[i][size.x - 1], wall);
    }
    for (int i = 0; i < size.x; i++){
        FILLRESETPTR(world[0][i], wall);
        FILLRESETPTR(world[size.y - 1][i], wall);
    }
}

void World::generateFood(){
    if (foodPerTick < 0 && ++foodTicks == -foodPerTick){    //++foodTicks
        foodTicks = 0;
        XY xyFood;
        xyFood.x = rand() % size.x;
        xyFood.y = rand() % size.y;
        if (getChar(xyFood) == none || getChar(xyFood) == dead) setChar(xyFood, food);
    }
    else
    if (foodPerTick > 0){
        for (int i = 0; i < foodPerTick; i++){
            XY xyFood;
            xyFood.x = rand() % size.x;
            xyFood.y = rand() % size.y;
            if (getChar(xyFood) == none || getChar(xyFood) == dead) setChar(xyFood, food);
        }
    }
}

void World::update(){
    generateFood();
    int snakesSize = 0;
    for (auto &it : snakes){
        if (it.getLive()){
            it.update();
            snakesSize++;
        }
        else{

        }
    }
}

void World::flash(){
    for (auto &it1 : world){
        for (auto &it2 : it1){
            if (it2.symbol == snake){
                FILLRESETPTR(it2, none);
            }
        }
    }
}

void World::setChar(XY& xy, unsigned char symbol){
    FILLRESETPTR(world.at(xy.y).at(xy.x), symbol);
}

void World::setChar(XY& xy, Snake* snake){
    world.at(xy.y).at(xy.x).symbol = TileType::snake;
    world[xy.y][xy.x].snake = snake;
}

unsigned char World::getChar(XY xy){
    return world.at(xy.y).at(xy.x).symbol;
}

unsigned char World::getChar(int x, int y){
    return getChar(XY(x, y));
}

unsigned char World::getCharNoThrow(XY xy){
    if (xy.y >= 0 && xy.y < size.y && xy.x >= 0 && xy.x < size.x){
        return world[xy.y][xy.x].symbol;
    }
    else return none;
}

Snake* World::getSnake(XY xy){
    if (boundsCheck(xy)){
        return world[xy.y][xy.x].snake;
    }
    else return NULL;
}

int World::boundsCheck(XY xy){
    if (xy.y >= 0 && xy.x >= 0 && xy.y < (int)world.size() && xy.x < (int)world[0].size()){
        return 1;
    }
    else return 0;
}

void World::addEgg(XY xy, int snakeSize, int saturation, int generation, Genes genes){
    snakes.push_front(Snake(true, *this, xy, snakeSize, saturation, generation, (Sex)(rand() % 2), genes));
}

std::vector<std::string> World::test(){
    #ifdef __linux__
    #define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
    #endif // __linux__
    #ifdef _WIN32
        #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
    #endif // _WIN32

    std::vector<std::string> errors;
    std::string file = __FILENAME__;
    #define e(x) errors.push_back((std::string)__FILENAME__ + ' ' + x);
    generate();
    if (getChar(0,0) != wall) e("Error in generate walls");
    XY xy;
    xy.x = 2;
    xy.y = 2;
    #define check \
    setChar(xy, wall); \
    if (getChar(xy) != wall){err++;} \
    setChar(xy, none);
    int err = 0;

    check

    xy.x++;

    check

    xy.x--; xy.x--;

    check

    xy.x++; xy.y++;

    check

    xy.y--; xy.y--;

    check

    if (err) e("Error in set/getChar");

    return errors;
}
