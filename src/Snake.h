#ifndef SHAKE_H_INCLUDED
#define SHAKE_H_INCLUDED

#include <vector>
#include <list>
#include <string>
#include <fstream>

#include "XY.h"

class world;

enum Sex{
    female,
    male
};

struct Genes{
    int upSaturationWhenTailDecrease = 7;
    int downSaturationWhenTailIncrease = 7;
    int saturationUpTail = 15;
    int saturationDownTail = 6;
    int saturationStart = 10;
    int startSize = 3;
    int tailReproduction = 12;
    int tailDie = 3;
    int tailDecreaseWhenReproduction = 5;
    int movesForDecreaseSaturation = 5;
    int movesInEgg = 50;

    int viewCells = 0;
    std::vector<std::vector<std::vector<int>>> weights;
};

#define DIR(x) x##Up, x##Right, x##Down, x##Left,
enum Dir{
    DIR(food)
    DIR(wall)

    dirEnd
};

class World;

class Snake{
    public:
        Snake(World& world, XY xy, int snakeSize, int saturation, int generation, Sex sex, Genes& genes);
        Snake(bool isEgg, World& world, XY xy, int snakeSize, int saturation, int generation, Sex sex, Genes& genes);
        void loadGenesFromFile(std::string file);
        void unloadGenesIntoFile(std::string file);
        void update();
        void addOneTail();
        void removeOneTail();
        int getWeight(Dir dir, int x, int y);
        void setWeight(Genes& genes, Dir dir, int x, int y, int value);
        bool getLive();

    private:
        XY getWeightXY(Dir dir, int x, int y);
        void die(bool deleteHeadOnWorld);
        void reproduction();
        Genes makeMutation();
        bool isEgg = false;
        World& world;
        std::list<XY> xySnake;  //coordinates of head [0] and tail [1-...]
        int eggTicks = 0;
        bool live = true;
        int saturation;
        int saturationTimer = 0;
        int generation;
        bool readyForReproduction = false;
        int mutationWeightCount = 1;    //if mutationWeightCount == -5 mutation chance 20%; if == 5 mutation will be 5 times
        int mutationWeightNumber = 3;
        Sex sex;
        Genes genes;
};

#endif // SHAKE_H_INCLUDED
