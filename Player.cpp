#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    foodRef = thisFoodRef;
    myDir = STOP;

    // more actions to be included

    //Initial player starting position object
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '*'); //CHANGE INITIAL POSITION once board is set
    
    //Creating objPosArrayList on the heap
    playerPosList = new objPosArrayList();
    
    //Adding tempPos to head of array list
    playerPosList->insertHead(tempPos);

    // //FOR DEBUGGING - DELETE SEGMENT AFTER
    // //insert another 4 segments
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic

    //Receiving input through getInput() from GameMechs class    
    char input = mainGameMechsRef->getInput();
    
    switch(input){
        
        case 'w':
            if(myDir != UP && myDir != DOWN){
                myDir = UP;
            }
            break;
        
        case 'a':
            if(myDir != LEFT && myDir != RIGHT){
                myDir = LEFT;
            }
            break;

        case 's':
            if(myDir != UP && myDir != DOWN){
                myDir = DOWN;
            }
            break;

        case 'd':
            if(myDir != LEFT && myDir != RIGHT){
                myDir = RIGHT;
            }
            break;

    }        
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    //NOTE: COL_SIZE is the max number of columns in gameboard
    //      ROW_SIZE is max number of rows in gameboard
    int col_size = mainGameMechsRef->getBoardSizeY();
    int row_size = mainGameMechsRef->getBoardSizeX();
    
    //Creating currentHead object to store position info of the current head
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);

    objPos tempFoodPos;
    foodRef->getFoodPos(tempFoodPos);
    
    switch(myDir){
        case UP:
            //Subtracting y position by 1 to move player object up by one
            currentHead.y--;
            
            //If statement to check if player reaches top of the game board
            if(currentHead.y == 0){
                currentHead.y = col_size-2;
            }

            break;

        case DOWN:
            currentHead.y++;

            //If statement to check if player reaches bottom of the game board
            if (currentHead.y == col_size-1){
                currentHead.y = 1;
            }

            break;

        case LEFT:

            currentHead.x--;

            //If statement to check if player reaches the left border of game board
            if (currentHead.x == 0){
                currentHead.x = row_size-2;
            }

            break;

        case RIGHT:

            currentHead.x++;

            //If statement to check if player reaches the right border of game board
            if (currentHead.x == row_size-1){
                currentHead.x = 1;
            }

            break;
    }

    //New current head inserted to the head of the list
    playerPosList->insertHead(currentHead);
    

    //If to generate new food position if new snake head collides with food
    if(currentHead.isPosEqual(&tempFoodPos)){
        foodRef->generateFood(playerPosList);
    }

    //Else statement to remove tail only when there's no collision
    else{
        //Remove tail element
        playerPosList->removeTail();
    }
}

