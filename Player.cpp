#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included

    //Initial player starting position
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '*'); //CHANGE INITIAL POSITION once board is set
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
    // return the reference to the playerPos arrray list
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

    switch(myDir){
        case UP:
            //Subtracting y position by 1 to move player object up by one
            playerPos.y--;
            
            //If statement to check if player reaches top of the game board
            if(playerPos.y == 0){
                playerPos.y = col_size-2;
            }

            break;

        case DOWN:
            playerPos.y++;

            //If statement to check if player reaches bottom of the game board
            if (playerPos.y == col_size-1){
                playerPos.y = 1;
            }

            break;

        case LEFT:

            playerPos.x--;

            //If statement to check if player reaches the left border of game board
            if (playerPos.x == 0){
                playerPos.x = row_size-2;
            }

            break;

        case RIGHT:

            playerPos.x++;

            //If statement to check if player reaches the right border of game board
            if (playerPos.x == row_size-1){
                playerPos.x = 1;
            }

            break;
    }
}

