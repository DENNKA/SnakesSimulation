#include "Snake.h"
#include "World.h"

Snake::Snake(World& world, XY xy, int snakeSize, int saturation, int generation, Sex sex, Genes genes)
    : world(world), saturation(saturation), generation(generation), sex(sex), genes(genes){
    for (int i = 0; i < snakeSize; i++){
        xySnake.push_back(xy);
    }
}

Snake::Snake(bool isEgg, World& world, XY xy, int snakeSize, int saturation, int generation, Sex sex, Genes genes)
    : isEgg(isEgg), world(world), saturation(saturation), generation(generation), sex(sex), genes(genes){
    for (int i = 0; i < snakeSize; i++){
        xySnake.push_back(xy);
    }
}

void Snake::loadGenesFromFile(std::string file){
    std::ifstream fin(file);
    if (!fin.is_open()){
        std::cout << "file " + file + " not exist";
        std::cin.get();
        return;
    }

    fin >> genes.viewCells;
    genes.weights.resize(8);
    int i = 0;
    for (auto &it1 : genes.weights){
        if (i % 2 == 1) {
            it1.resize(genes.viewCells + 1);
            for (auto &it2 : it1){
                it2.resize(genes.viewCells * 2 + 1);
            }
        }
        else{
            it1.resize(genes.viewCells * 2 + 1);
            for (auto &it2 : it1){
                it2.resize(genes.viewCells + 1);
            }
        }
        i++;
    }

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

    fout << genes.viewCells << std::endl;
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
        if (eggTicks > genes.movesInEgg){
            isEgg = false;
        }
        eggTicks++;
        world.setChar(xySnake.front(), egg);
    }
    else{
        XY& xy = xySnake.front();
        int dirs[4] = {0};
        const int view = genes.viewCells * 2 + 1;

        for (int y = xy.y - genes.viewCells, i = 0; i < view; y++, i++){
            for (int x = xy.x - genes.viewCells, j = 0; j < view; x++, j++){
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

        if (++saturationTimer >= genes.movesForDecreaseSaturation){
            saturation--;
            saturationTimer = 0;
        }

        if (saturation > genes.saturationUpTail){
            saturation -= genes.downSaturationWhenTailIncrease;
            addOneTail();
        }

        if (saturation < genes.saturationDownTail){
            if ((int)xySnake.size() - 1 <= genes.tailDie){
                die(true);
            }
            else{
                saturation += genes.upSaturationWhenTailDecrease;
                removeOneTail();
            }
        }

        if ((int)xySnake.size() >= genes.tailReproduction){
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
    y = (genes.viewCells * 2 + 1) - y - 1;
    if (dir % 2 == 1){
        if (y > genes.viewCells){
            y = -(y - genes.viewCells * 2);
        }
    }
    else{
        if (x > genes.viewCells){
            x = -(x - genes.viewCells * 2);
        }
    }
    return genes.weights.at(dir).at(y).at(x);
}

bool Snake::getLive(){return live;}

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
        auto it = xySnake.end();
        for (int i = 0; i <= 3; i++){
            --it;
            world.setChar(*it, none);
        }
        xySnake.erase(it, --xySnake.end());
        world.addEgg(xySnake.back(), genes.startSize, genes.saturationStart, generation + 1, genes);
    }
}
