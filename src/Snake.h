#ifndef SHAKE_H_INCLUDED
#define SHAKE_H_INCLUDED

#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <memory>   //shared_ptr

#include "XY.h"

class world;

enum Sex{
    female,
    male
};

struct Gene{
    Gene(){};
    Gene(bool first, bool second){isDominant[0] = first; isDominant[1] = second;}
    bool isDominant[2];
};

struct Genes{
    std::vector<Gene> vectorGenes;
    std::vector<std::vector<std::vector<int>>> weights;
};

#define DIR(x) x##Up, x##Right, x##Down, x##Left,
enum Dir{
    DIR(food)
    DIR(wall)

    dirEnd
};

class World;

class Gui;

class Snake{
    public:
        Snake(bool isEgg, World& world, XY xy, int generation, Sex sex, std::shared_ptr<Genes> genesFromParent, bool firstSnake = false);
        friend Gui;
        void loadGenesFromFile(std::string file);
        void unloadGenesIntoFile(std::string file);
        void update();
        void addOneTail();
        void removeOneTail();
        int getWeight(std::shared_ptr<Genes> genes, Dir dir, int x, int y);
        void setWeight(std::shared_ptr<Genes> genes, Dir dir, int x, int y, int value);
        bool getLive();
        Sex getSex();

    private:
        void setGenesPartner(std::shared_ptr<Genes> genesPartner);
        int makeShorten(int size);  //return 1 if ok
        void resizeWeights();
        XY getWeightXY(Dir dir, int x, int y);
        void die(bool deleteHeadOnWorld);
        void reproduction();
        std::shared_ptr<Genes> makeNewGenes();
        bool isEgg = false;
        World& world;
        std::list<XY> xySnake;  //coordinates of head [0] and tail [1-...]
        int eggTicks = 0;
        int reproductionTicks = 0;
        int eggsWithOnePartnerCounter = 0;
        bool live = true;
        int saturation;
        int saturationTimer = 0;
        int generation;
        bool readyForReproduction = false;

        int mutationWeightCount = 1;    //if mutationWeightCount == -5 mutation chance 20%; if == 5 mutation will be 5 times
        int mutationGenesCount = -4;    //see above
        int mutationWeightNumber = 3;
        int laidEggsWithOnePartner = 3;
        int upSaturationWhenTailDecrease;
        int downSaturationWhenTailIncrease;
        int saturationUpTail;
        int saturationDownTail;
        int saturationStart;
        int startSize;
        int tailReproduction;
        int tailDie;
        int tailDecreaseWhenReproduction;
        int movesForDecreaseSaturation;
        int movesInEgg;
        int viewCells;

        Sex sex;
        std::shared_ptr<Genes> genesPartner;
        std::shared_ptr<Genes> genes;
};

#endif // SHAKE_H_INCLUDED
