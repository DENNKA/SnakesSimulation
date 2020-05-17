#include "Snake.h"
#include "World.h"

Snake::Snake(bool isEgg, World& world, XY xy, int generation, Sex sex, Genes& genesFromParent, bool firstSnake)
    : isEgg(isEgg), world(world), generation(generation), sex(sex), genes(genesFromParent){

    upSaturationWhenTailDecrease = 0;
    downSaturationWhenTailIncrease = 13;
    saturationUpTail = 0;
    saturationDownTail = 0;
    saturationStart = 0;
    startSize = 0;
    tailReproduction = 0;
    tailDie = 6;
    tailDecreaseWhenReproduction = 8;
    movesForDecreaseSaturation = 3;
    movesInEgg = 150;
    viewCells = 0;

    if (firstSnake){
        loadGenesFromFile("defaultGenes.txt");
        unloadGenesIntoFile("check.txt");
    }

    /*for (auto &it : genes.vectorGenes){
        d(it.isDominant[0]); d(it.isDominant[1]);
    }*/

    #define START int i = 0; int vectorSize = genes.vectorGenes.size();
    #define NEXT i++;
    #define IFDOMINANT if (i < vectorSize && (genes.vectorGenes[i].isDominant[0] || genes.vectorGenes[i].isDominant[1]))    // CAUTION!!! if without {}
    #define IFNOTDOMINANT if (i < vectorSize && !genes.vectorGenes[i].isDominant[0] && !genes.vectorGenes[i].isDominant[1])
    #define BEGIN {
    #define END }
    START
    IFDOMINANT
    upSaturationWhenTailDecrease += 4;
    NEXT
    IFDOMINANT
    upSaturationWhenTailDecrease += 3;
    NEXT
    IFDOMINANT
    downSaturationWhenTailIncrease += -4;
    NEXT
    IFDOMINANT
    downSaturationWhenTailIncrease += -2;
    NEXT
    IFDOMINANT
    saturationUpTail += 10;
    NEXT
    IFDOMINANT
    saturationUpTail += 5;
    NEXT
    IFNOTDOMINANT
    saturationUpTail += 5;
    NEXT
    IFDOMINANT
    saturationDownTail += 3;
    NEXT
    IFDOMINANT
    saturationDownTail += 3;
    NEXT
    IFNOTDOMINANT
    saturationDownTail += 3;
    NEXT
    IFDOMINANT
    saturationStart += 5;
    NEXT
    IFDOMINANT
    saturationStart += 5;
    NEXT
    IFNOTDOMINANT  //12
    saturationStart += 5;
    NEXT
    IFDOMINANT
    startSize += 3;
    NEXT
    IFNOTDOMINANT  //14
    startSize += 3;
    NEXT
    IFDOMINANT
    tailReproduction += 6;
    NEXT
    IFDOMINANT
    tailReproduction += 6;
    NEXT
    IFNOTDOMINANT //17
    tailReproduction -= 3;
    NEXT
    IFDOMINANT
    tailDie -= 3;
    NEXT
    IFNOTDOMINANT
    tailDie += 2;
    NEXT
    IFNOTDOMINANT
    tailDie += 2;
    NEXT
    IFDOMINANT
    tailDecreaseWhenReproduction -= 3;
    NEXT
    IFNOTDOMINANT
    tailDecreaseWhenReproduction += 3;
    NEXT
    IFNOTDOMINANT
    tailDecreaseWhenReproduction -= 3;
    NEXT
    IFDOMINANT
    movesForDecreaseSaturation += 1;
    NEXT
    IFDOMINANT
    movesForDecreaseSaturation += 1;
    NEXT
    IFNOTDOMINANT
    movesForDecreaseSaturation += 2;
    NEXT
    IFDOMINANT
    movesInEgg -= 50;
    NEXT
    IFDOMINANT
    movesInEgg -= 25;
    NEXT
    IFNOTDOMINANT
    movesInEgg -= 25;
    NEXT
    IFDOMINANT
    viewCells = 5;
    NEXT  //this next is required
    #undef START
    #undef NEXT
    #undef IFDOMINANT
    #undef IFNOTDOMINANT
    #undef BEGIN
    #undef END
    for (;i < genes.vectorGenes.size(); i++){   //if vector bigger
        genes.vectorGenes[i].isDominant[0] = true;
        genes.vectorGenes[i].isDominant[1] = true;
    }

    saturation = saturationStart;
    if (startSize == 0){    //configurate head and tail (or die)
        die(true);
    }
    else{
        for (int i = 0; i < startSize; i++){
            xySnake.push_back(xy);
        }
    }

    /*d(upSaturationWhenTailDecrease)
    d(downSaturationWhenTailIncrease)
    d(saturationUpTail)
    d(saturationDownTail)
    d(saturationStart)
    d(startSize)
    d(tailReproduction)
    d(tailDie)
    d(tailDecreaseWhenReproduction)
    d(movesForDecreaseSaturation)
    d(movesInEgg)
    d(viewCells)*/
}

void Snake::loadGenesFromFile(std::string file){

    std::ifstream fin(file);
    if (!fin.is_open()){
        std::cout << "file " + file + " not exist";
        std::cin.get();
        return;
    }

    int vectorGenesSize;
    fin >> vectorGenesSize;
    genes.vectorGenes.reserve(vectorGenesSize);
    for (int i = 0; i < vectorGenesSize; i++){
        int temp0, temp1;
        fin >> temp0;
        fin >> temp1;
        genes.vectorGenes.push_back(Gene(temp0, temp1));
    }

    fin >> viewCells;
    resizeWeights();

    for (auto &it1 : genes.weights){
        for (auto &it2 : it1){
            for (auto &it3 : it2){
                fin >> it3;
            }
        }
    }

    fin.close();
}

void Snake::unloadGenesIntoFile(std::string file){
    std::ofstream fout(file);
    if (!fout.is_open()){
        std::cout << "file" + file + "not exist";
        std::cin.get();
        return;
    }

    fout << viewCells << std::endl;
    for (auto &it1 : genes.weights){
        for (auto &it2 : it1){
            for (auto &it3 : it2){
                fout << it3 << ' ';
            }
            fout << std::endl;
        }
        fout << std::endl;
    }

    fout.close();
}

void Snake::update(){
    if (isEgg == true){
        if (eggTicks > movesInEgg){
            isEgg = false;
        }
        eggTicks++;
        world.setChar(xySnake.front(), egg);
    }
    else{
        XY& xy = xySnake.front();
        int dirs[4] = {0};
        const int view = viewCells * 2 + 1;

        for (int y = xy.y - viewCells, i = 0; i < view; y++, i++){
            for (int x = xy.x - viewCells, j = 0; j < view; x++, j++){
                switch (world.getCharNoThrow(XY(x, y))){
                    case snake:
                    case wall:
                        for (int dir = 0, dirWeight = wallUp; dirWeight <= wallLeft; dirWeight++, dir++){
                            dirs[dir] -= getWeight((Dir)dirWeight, j, i);
                        }
                    break;
                    case food:
                        for (int dir = 0, dirWeight = foodUp; dirWeight <= foodLeft; dirWeight++, dir++){
                            dirs[dir] += getWeight((Dir)dirWeight, j, i);
                        }
                    break;
                }
            }
        }

        xySnake.insert(xySnake.begin(), XY(xy));

        if (dirs[0] >= dirs[1] && dirs[0] >= dirs[2] && dirs[0] >= dirs[3]){
            //up
            xySnake.front().y++;
        }
        else{
            if (dirs[1] >= dirs[2] && dirs[1] >= dirs[3]){
                //right
                xySnake.front().x++;
            }
            else{
                if (dirs[2] >= dirs[3]){
                    //down
                    xySnake.front().y--;
                }
                else{
                    //left
                    xySnake.front().x--;
                }
            }
        }

        switch (world.getChar(xySnake.front())){
            case wall:
            case snake:
                die(false);
            return; // !
            case food:
                saturation += 1;
            break;
            case none:
            break;
        }
        world.setChar(xySnake.back(), none);
        xySnake.pop_back();
        world.setChar(xySnake.front(), this);

        if (++saturationTimer >= movesForDecreaseSaturation){
            saturation--;
            saturationTimer = 0;
        }

        if (saturation > saturationUpTail){
            saturation -= downSaturationWhenTailIncrease;
            addOneTail();
        }

        if (saturation < saturationDownTail){
            if ((int)xySnake.size() - 1 <= tailDie){
                die(true);
            }
            else{
                saturation += upSaturationWhenTailDecrease;
                removeOneTail();
            }
        }

        if ((int)xySnake.size() >= tailReproduction){
            reproduction();
        }


    }
}

void Snake::addOneTail(){
    xySnake.insert(xySnake.end(), xySnake.back());
}

void Snake::removeOneTail(){
    world.setChar(xySnake.back(), none);
    xySnake.erase(--xySnake.end());
}

int Snake::getWeight(Dir dir, int x, int y){
    XY xy = getWeightXY(dir, x, y);
    return genes.weights[dir][xy.y][xy.x];
}

void Snake::setWeight(Genes& genes, Dir dir, int x, int y, int value){
    XY xy = getWeightXY(dir, x, y);
    genes.weights[dir][xy.y][xy.x] = value;
}

bool Snake::getLive(){return live;}

void Snake::resizeWeights(){
    genes.weights.resize(8);
    int i = 0;
    for (auto &it1 : genes.weights){
        if (i % 2 == 1) {
            it1.resize(viewCells + 1);
            for (auto &it2 : it1){
                it2.resize(viewCells * 2 + 1);
            }
        }
        else{
            it1.resize(viewCells * 2 + 1);
            for (auto &it2 : it1){
                it2.resize(viewCells + 1);
            }
        }
        i++;
    }
}

XY Snake::getWeightXY(Dir dir, int x, int y){
    y = (viewCells * 2 + 1) - y - 1;
    if (dir % 2 == 1){
        if (y > viewCells){
            y = -(y - viewCells * 2);
        }
    }
    else{
        if (x > viewCells){
            x = -(x - viewCells * 2);
        }
    }
    return XY(x, y);
}

void Snake::die(bool deleteHeadOnWorld){
    if (!deleteHeadOnWorld){
        xySnake.pop_front();
    }
    for (auto &it : xySnake){
        world.setChar(it, dead);
    }
    live = false;
}

void Snake::reproduction(){
    readyForReproduction = true;
    if (sex == male){

    }
    else{
        if ((int)xySnake.size() - tailDecreaseWhenReproduction <= tailDie){
            die(true);
        }
        else{
            auto it = xySnake.end();
            for (int i = 0; i < tailDecreaseWhenReproduction; i++){
                --it;
                world.setChar(*it, none);
            }
            xySnake.resize(xySnake.size() - tailDecreaseWhenReproduction);
        }
        world.addEgg(xySnake.back(), generation + 1, makeMutation());
    }
}

Genes Snake::makeMutation(){
    Genes newGenes = genes;
    if (mutationWeightCount < 0) mutationWeightCount = ((rand() % mutationWeightCount) == 0);
    for (int i = 0; i < mutationWeightCount; i++){
        Dir dir = (Dir)(rand() % dirEnd);
        const int view = viewCells * 2 + 1;
        int x = rand() % view;
        int y = rand() % view;
        int value = rand() % mutationWeightNumber - mutationWeightNumber / 2;
        setWeight(newGenes, dir, x, y, getWeight(dir, x, y) + value);
    }
    return newGenes;
}
