#include "Food.h"

Food::Food(){
    //Initialising food object to be outside of game board
    foodPos.setObjPos(-1, -1, 'o');
    xRange = 30;
    yRange = 15;

    //Seeding random number generation function with current time
    srand(time(NULL));
}

Food::Food(int boardSizeX, int boardSizeY){
    //Initialising food object to be outside of game board
    foodPos.setObjPos(-1, -1, 'o');
    xRange = boardSizeX;
    yRange = boardSizeY;

    //Seeding random number generation function with current time
    srand(time(NULL));
}

Food::~Food(){

}

void Food::generateFood(objPos blockOff){

    //Local variables
    int regenerateStatus, rand_x, rand_y;

    //Do while loop to continuosly generate random coordinates for food
    do{
        //Resetting do while loop exit flag
        regenerateStatus = 0;
        
        //Generating random x and y values within ranges
        rand_x = (rand() % (xRange-2))+1;
        rand_y = (rand() % (yRange-2))+1;

        //Updating food position
        foodPos.setObjPos(rand_x, rand_y, 'o');

        //Setting regenerateStatus to 1 when food pos is equal to player pos, regenerating random coordinates again
        if (foodPos.isPosEqual(&blockOff)){
            regenerateStatus = 1;
        }

    }while(regenerateStatus);


}

void Food::getFoodPos(objPos &returnPos){
    //foodPos data members are passed to returnPos through setObjPos method
    returnPos.setObjPos(foodPos);
}