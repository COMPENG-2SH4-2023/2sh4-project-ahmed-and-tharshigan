#ifndef FOOD_H
#define FOOD_H

//Including cstdlib and time library for random number generation
#include <cstdlib>
#include <time.h>

#include "objPos.h"

class Food{
    private:
        objPos foodPos;
        int xRange;
        int yRange;

    public:
        Food();
        Food(int boardSizeX, int boardSizeY);
        ~Food();

        void generateFood(objPos blockOff);
        void getFoodPos(objPos &returnPos);

};

#endif