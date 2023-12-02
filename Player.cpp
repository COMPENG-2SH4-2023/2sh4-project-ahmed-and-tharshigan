#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    //Initializing data members with passed parameters/default values
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
    
    //Case statements to set player direction based on key entered
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

    //COL_SIZE is the max number of columns in gameboard
    //ROW_SIZE is max number of rows in gameboard
    int col_size = mainGameMechsRef->getBoardSizeY();
    int row_size = mainGameMechsRef->getBoardSizeX();
    
    //Creating currentHead object to store position info of the current head
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);

    //Creating tempFoodPos to temporarily store position info of current food item on the board
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
            //Incrementing y position by 1 to player down by 1 row
            currentHead.y++;

            //If statement to check if player reaches bottom of the game board
            if (currentHead.y == col_size-1){
                currentHead.y = 1;
            }

            break;

        case LEFT:

            //Decreasing x position of head element by one to the left
            currentHead.x--;

            //If statement to check if player reaches the left border of game board
            if (currentHead.x == 0){
                currentHead.x = row_size-2;
            }

            break;

        case RIGHT:

            //Incrementing x position of head element by one to the right
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
        //Regenerating food item
        foodRef->generateFood(playerPosList);
        //Increment score by 1 for every element added
        mainGameMechsRef->incrementScore();
    }

    //Else statement to remove tail only when there's no collision
    else{
        //Remove tail element
        playerPosList->removeTail();
    }

    //If statement to check collision status
    if(checkSelfCollision()){
        //Setting both exit and lose flag true when self collision is true
        mainGameMechsRef->setExitTrue();
        mainGameMechsRef->setLoseFlag();
    }
    
}

bool Player::checkSelfCollision(){
    
    //Local objects
    objPos headElement, bodyElement;

    //Passing new head element's position to local object
    playerPosList->getHeadElement(headElement);

    //For loop to iterate through every initialized element within playerPosList aside from head element
    for(int i=1; i<playerPosList->getSize(); i++){
        //Passing element's position to local object
        playerPosList->getElement(bodyElement, i);
        //Comparing if head element' is equal to other elements based on position, indicating self collision
        if(headElement.isPosEqual(&bodyElement)){
            //Returning true, indicating collision
            return true;
        }
    }

    //Returning false, indicating no collision
    return false;
}